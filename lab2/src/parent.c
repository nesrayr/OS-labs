#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <parent.h>

void HandleError(bool expr, char* msg) {
    if (expr) {
        write(fileno(stdout), msg, strlen(msg) * sizeof(char));
        exit(-1);
    }
}

void Print(char* str, char* msg){
    char* full_msg = malloc((strlen(str) + strlen(msg)) * sizeof(char));
    strcat(full_msg, str); strcat(full_msg, msg);
    write(fileno(stdout), full_msg, strlen(full_msg) * sizeof(char));
}

void Clean(char* str){
    for (int i = 0 ; i < strlen(str); ++i){
        if (str[i] == '\n'){ str[i] = '\0'; }
    }
}

int ParentRoutine(FILE* stream){

    int src_fd[2];
    int pipe_response = pipe(src_fd);
    HandleError(pipe_response == -1, "pipe error");

    int err_fd[2];
    pipe_response = pipe(err_fd);
    HandleError(pipe_response == -1, "pipe error");

    pid_t id = fork();
    HandleError(id == -1, "fork error");

    if (id == 0){

        char name[64];
        read(src_fd[0], &name, sizeof(name));

        char *src_fd_0, *src_fd_1, *err_fd_0, *err_fd_1;
        asprintf(&src_fd_0, "%d", src_fd[0]);
        asprintf(&src_fd_1, "%d", src_fd[1]);
        asprintf(&err_fd_0, "%d", err_fd[0]);
        asprintf(&err_fd_1, "%d", err_fd[1]);

        execl("child.out", name, src_fd_0, src_fd_1, err_fd_0, err_fd_1, NULL);

    } else {

        char* parent; int parent_pid = getpid();
        asprintf(&parent, "[%d] PARENT. ", parent_pid);

        Print(parent, "Enter the name of file to write: ");
        char name[256];
        read(fileno(stdin), name, 256); Clean(name);
        write(src_fd[1], &name, sizeof(name));
        bool file_error; read(err_fd[0], &file_error, sizeof(bool));
        if (file_error){
            close(src_fd[0]); close(src_fd[1]);
            close(err_fd[0]); close(err_fd[1]);
            HandleError(true, "file error\n");
        }

        char str[256];
        Print(parent, "Enter string: ");
        while (read(fileno(stdin), str, 256) != 0){
            Clean(str);
            write(src_fd[1], &str, sizeof(str));
            bool err;
            read(err_fd[0], &err, sizeof(bool));
            if (err){
                char* err_msg;
                asprintf(&err_msg, "Error: \"%s\" is not valid.\n", str);
                Print(parent, err_msg);
            }
            Print(parent, "Enter string: ");
        }
        write(src_fd[1], "_quit", sizeof(str));

    }
    write(fileno(stdout), "\n", sizeof "\n");
    close(src_fd[0]); close(src_fd[1]);
    close(err_fd[0]); close(err_fd[1]);
    return 0;

}

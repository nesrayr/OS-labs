#include <iostream>
#include <string>
#include <unistd.h>
#include "zmq_functions.h"

const std::string ADRESS_C = "tcp://127.0.0.1:4040";
const std::string ADRESS_B = "tcp://127.0.0.1:4041";

int main(){
	zmq::context_t context;
	std::string str;
	zmq::socket_t B(context, ZMQ_REQ);
	zmq::socket_t C(context, ZMQ_REQ);

	B.connect(ADRESS_B);
	C.connect(ADRESS_C);

	std::string answer;

	pid_t pid1 = fork();
    pid_t pid2 = 1;

    if (pid1 > 0){
        pid2 = fork();
    }

    if (pid1 < 0 || pid2 < 0)
    {
        perror("process error )");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
    {
        execl("./B", "./B", NULL);

    }
    else if (pid2 == 0)
    {
        execl("./C", "./C", NULL);

    }
	while(std::getline(std::cin, str))
	{
		int size = str.size();
		send_message(C, str);
		answer = receive_message(C);

		while(answer != "String recieved"){
			std::cout << "Error: string not recieved" << std::endl;
		}

		send_message(B, std::to_string(size));

		answer = receive_message(B);

		if(answer != "OK"){
			std::cout << "Error: string not recieved" << std::endl;
		}
	}	

	send_message(C, "exit");
	
	if (receive_message(C) == "OK")
	{
		C.disconnect(ADRESS_C);
		C.close();

		send_message(B, "exit");

		if (receive_message(B) == "OK")
		{
			B.disconnect(ADRESS_B);
			B.close();
		}
	}
	return 0;
}
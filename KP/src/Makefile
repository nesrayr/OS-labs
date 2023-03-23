all: A B C

A:
	g++ A.cpp -lzmq -o A --std=c++17 -L /usr/local/include 

B:
	g++ B.cpp -lzmq -o B --std=c++17 -L /usr/local/include
C:
	g++ C.cpp -lzmq -o C --std=c++17 -L /usr/local/include 

clean:
	rm -rf A B C
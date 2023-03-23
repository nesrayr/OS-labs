#include <iostream>
#include <string>
#include "zmq_functions.h"

const std::string ADRESS_A = "tcp://127.0.0.1:4041";
const std::string ADRESS_C = "tcp://127.0.0.1:4042";

int main(){
	zmq::context_t context;
	zmq::socket_t A(context, ZMQ_REP);
	zmq::socket_t C(context, ZMQ_REP);

	A.bind(ADRESS_A);
	C.bind(ADRESS_C);

	std::string answerA, answerC;
	while(1)
	{
		answerA = receive_message(A);
		send_message(A, "OK");

		if (answerA == "exit"){
			break;
		}

		std::cout << "A: " << answerA << std::endl;

		answerC = receive_message(C);
		send_message(C, "OK");

		std::cout << "C: " << answerC << std::endl;
		
	}
	A.unbind(ADRESS_A);
	C.unbind(ADRESS_C);
	A.close();
	C.close();
	
	return 0;
}
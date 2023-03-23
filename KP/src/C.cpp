#include <iostream>
#include <string>
#include "zmq_functions.h"

const std::string ADRESS_A = "tcp://127.0.0.1:4040";
const std::string ADRESS_B = "tcp://127.0.0.1:4042";

int main(){
	zmq::context_t context;
	zmq::socket_t A(context, ZMQ_REP);
	zmq::socket_t B(context, ZMQ_REQ);

	A.bind(ADRESS_A);
	B.connect(ADRESS_B);

	std::string answer;
	while(1)
	{
		answer = receive_message(A);

		if (answer == "exit"){
			send_message(A, "OK");
			break;
		}

		std::cout << answer << std::endl;

		send_message(A, "String recieved");

		int size = answer.size();
		send_message(B, std::to_string(size));
		answer = receive_message(B);

		if (answer != "OK"){
			std::cout << "Error: string not recieved" << std::endl;
		}


	}
	A.unbind(ADRESS_A);
	B.disconnect(ADRESS_B);
	A.close();
	B.close();

	return 0;
}
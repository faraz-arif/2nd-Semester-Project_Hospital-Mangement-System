#ifndef INVALID_INPUT_EXCEPTION_H
#define INVALID_INPUT_EXCEPTION_H
#include"HospitalException.h"

class InvalidInputException : public  HospitalException {
public:
	InvalidInputException() {
		const char* msg = "Error: Invalid User Input.";
		int i = 0;
		for (i; msg[i] != '\0' && i < 199; i++) {
			this->message[i] = msg[i];
		}
		message[i] = '\0';

	}
};
#endif
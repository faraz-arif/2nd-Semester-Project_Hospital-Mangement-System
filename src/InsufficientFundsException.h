#ifndef INSUFFICIENT_FUNDS_EXCEPTION_H
#define INSUFFICIENT_FUNDS_EXCEPTION_H
#include"HospitalException.h"
class InsufficientFundsException : public  HospitalException {
public:
	InsufficientFundsException() {
		const char* msg = "Error: Insufficient funds in patient balance.";
		int i = 0;
		for (i; msg[i] != '\0' && i < 199; i++) {
			message[i] = msg[i];
		}
		message[i] = '\0';

	}
};
#endif
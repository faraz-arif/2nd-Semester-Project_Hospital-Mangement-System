#pragma once
#ifndef SLOTS_UNAVAILABLE_EXCEPTION_H
#define SLOTS_UNAVAILABLE_EXCEPTION_H
#include"HospitalException.h"

class SlotsUnavailableException : public  HospitalException {
public:
	SlotsUnavailableException() {
		const char* msg = "Error: Selected Slot is currently unavailable.";
		int i = 0;
		for (i; msg[i] != '\0' && i < 199; i++) {
			message[i] = msg[i];
		}
		message[i] = '\0';
	}
};
#endif
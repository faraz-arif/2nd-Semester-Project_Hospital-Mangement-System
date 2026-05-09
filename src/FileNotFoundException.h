#pragma once
#ifndef FILE_NOT_FOUND_EXCEPTION_H
#define FILE_NOT_FOUND_EXCEPTION_H
#include"HospitalException.h"
class FileNotFoundException : public HospitalException {
public:
	FileNotFoundException() {
		const char* msg = "Error: File Not Found! Check your file paths.";
		int i = 0;
		for (i; msg[i] != '\0' && i < 199; i++) {
			message[i] = msg[i];
		}
		message[i] = '\0';

	}
};
#endif
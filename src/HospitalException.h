#ifndef HOSPITAL_EXCEPTION_H
#define HOSPITAL_EXCEPTION_H

class HospitalException {
protected:
	char message[200];
	HospitalException() { message[0] = '\0'; }

public:
	virtual ~HospitalException() = default;
	virtual const char* what() const { 
		return message;
	}
};

#endif

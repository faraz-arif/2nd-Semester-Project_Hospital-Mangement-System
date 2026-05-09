#ifndef BILL_H
#define BILL_H

#include<iostream>
using namespace std;

class Bill {
private:
	int billID;
	int appointmentID;
	int patientID;
	float amount;
	char description[50];
public:
	Bill() : billID(0), appointmentID(0), patientID(0), amount(0.0) {
		description[0] = '\0';
	}
	Bill(int id, int aID, int pID, float am, const char* des) {
		this->billID = id;
		this->amount = am;
		this->appointmentID = aID;
		this->patientID = pID;
		int i;
		for (i = 0; des[i] != '\0' && i < 49; i++) {
			this->description[i] = des[i];
		}
		this->description[i] = '\0';
	}
	Bill(int pID, float am, const char *des) {
		this->billID = 0;
		this->appointmentID = 0;
		this->patientID = pID;
		this->amount = am;
		int i;
		for (i = 0; des[i] != '\0' && i < 49; i++) {
			this->description[i] = des[i];
		}
		this->description[i] = '\0';
	}
	int getID() const {
		return billID;
	}
	int getPatientID() const {
		return patientID;
	}
	float getAmount() const {
		return amount;
	}
	const char* getDescription() const {
		return this->description;
	}
	friend ostream& operator<<(ostream& out, const Bill& other);
};
ostream& operator<<(ostream& out, const Bill& other) {
	out << "Bill Info:\n";
	out << "Bill ID:\t" << other.billID << endl;
	out << "Appointment ID:\t" << other.appointmentID << endl;
	out << "Patient ID:\t" << other.patientID << endl;
	out << "Amount:\t" << other.amount << endl;
	return out;
}
#endif 

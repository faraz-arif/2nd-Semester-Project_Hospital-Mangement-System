#ifndef DOCTOR_H
#define DOCTOR_H

#include"Person.h"
class Doctor : public Person {
private:
	char specialization[50];
	float consultationFee;
public:
	Doctor() : Person() , consultationFee(0.0) {
		specialization[0] = '\0';
	}
	Doctor(int id, const char* name, const char* spec, float fee, const char* pass) : Person(id, name) {
		int i = 0;
		for (i = 0; spec[i] != '\0'; i++) {
			specialization[i] = spec[i];
		}
		specialization[i] = '\0';
		consultationFee = fee;
		for (i = 0; pass[i] != '\0'; i++) {
			password[i] = pass[i];
		}
		password[i] = '\0';
	}
	const char* getPassword() const {
		return password;
	}
	bool operator==(const Doctor& other) const {
		return this->id == other.id;
	}
	friend ostream& operator<<(ostream& out, const Doctor& other);
	const char* getSpecialization() const {
		return specialization;
	}
	void display() override {
		cout << "Doctor Info" << endl;
		cout << "Name:\t" << name << endl;
		cout << "ID:\t" << id << endl;
		cout << "Specialization:\t" << specialization << endl;
		cout << "Consultation Fee:\t" << consultationFee << endl;
	}
	float getFee() const {
		return consultationFee;
	}
	const char* getRole() override {
		return "Doctor";
	}
};
ostream& operator<<(ostream& out, const Doctor& other) {
	out << "Doctor Info" << endl;
	out << "Name:\t" << other.name << endl;
	out << "ID:\t" << other.id << endl;
	out << "Specialization:\t" << other.specialization << endl;
	out << "Consultation Fee:\t" << other.consultationFee << endl;
	return out;
}

#endif
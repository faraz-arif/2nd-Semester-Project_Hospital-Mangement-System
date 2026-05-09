#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include "InsufficientFundsException.h"
#include <cstring>

class Patient : public Person {
private:
	float balance;
	char gender;
	char contact[12];
	int age;
public:
	Patient() : balance(0.0f), gender('U'), age(0) {
		id = 0;
		name[0] = '\0';
		password[0] = '\0';
		contact[0] = '\0';
	}
	Patient(int id_, const char* name_, int age_, char gender_, const char* contact_, const char* password_, float balance_) {
		id = id_;
		balance = balance_;
		int i = 0;
		if (name_) {
			for (i = 0; name_[i] != '\0'; i++) {
				name[i] = name_[i];
			}
			name[i] = '\0';
		}
		else {
			name[0] = '\0';
		}
		age = age_;
		gender = gender_;
		if (contact_) {
			for (i = 0; contact_[i] != '\0'; i++) {
				contact[i] = contact_[i];
			}
			contact[i] = '\0';
		}
		else {
			contact[0] = '\0';
		}
		if (password_) {
			int i;
			for (i = 0; password_[i] != '\0'; i++) {
				password[i] = password_[i];
			}
			password[i] = '\0';
		}
		else {
			password[0] = '\0';
		}
	}
	float getBalance() const {
		return balance;
	}
	char getGender() const {
		return gender;
	}
	int getAge() const {
		return age;
	}
	const char* getContact() const {
		return contact;
	}
	const char* getPassword() const {
		return password;
	}
	const char* getRole() override {
		return "Patient";
	}

	void display() override {
		cout << "Patient Info" << endl;
		cout << "Name:\t" << name << endl;
		cout << "ID:\t" << id << endl;
	}

	void operator-=(float amount) {
		if (balance >= amount) {
			balance -= amount;
		}
		else {
			throw InsufficientFundsException();
		}			
	}
	void operator+=(float amount) {
		if (amount > 0) {
			balance += amount;
		}
	}
	bool operator==(const Patient& other) const {
		return this->id == other.id;
	}
	friend ostream& operator<<(ostream& out, const Patient& other);
};
ostream& operator<<(ostream& out, const Patient& other) {
	out << "Patient Info" << endl;
	out << "Name:\t" << other.name << endl;
	out << "ID:\t" << other.id << endl;
	return out;
}

#endif
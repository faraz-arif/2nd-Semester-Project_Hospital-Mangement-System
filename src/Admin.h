#ifndef ADMIN_H
#define ADMIN_H

#include"Person.h"
class Admin : public Person {
public:
	Admin() : Person() {}
	Admin(int id, const char* name, const char* pass) : Person(id, name) {
		int i = 0;
		for (i = 0; pass[i] != '\0'; i++) {
			password[i] = pass[i];
		}
		password[i] = '\0';
	}
	const char* getPassword() const {
		return password;
	}
	void display() override {
		cout << "Admin Info" << endl;
		cout << "Name:\t" << name << endl;
		cout << "ID:\t" << id << endl;
	}
	const char* getRole() override {
		return "Administrator";
	}
	friend ostream& operator<<(ostream& out, const Admin& a);
};
ostream& operator<<(ostream& out, const Admin& a) {
	out << "Admin Info" << endl;
	out << "Name:\t" << a.name << endl;
	out << "ID:\t" << a.id << endl;
	return out;
}	
#endif
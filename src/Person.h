#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Person {
protected:
	int id;
	char name[50];
	char password[50];
public:
	Person(int id = 0, const char* name = "") {
		this->id = id;
		if (name) {
			int i = 0; 
			for (i = 0; name[i] != '\0'; i++) {
				this->name[i] = name[i];
			}
			this->name[i] = name[i];
		} else {
			this->name[0] = '\0';
		}
		this->name[sizeof(this->name) - 1] = '\0';
		this->password[0] = '\0';
	}
	virtual ~Person() {}
	virtual void display() = 0;
	int getID() const {
		return id;
	}
	virtual const char* getRole() = 0;
	const char* getName() const {
		return name;
	}
};
#endif
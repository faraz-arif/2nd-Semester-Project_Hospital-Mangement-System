#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include"Storage.h"
#include"Patient.h"
#include"FileNotFoundException.h"
#include"Doctor.h"
#include"Utils.h"
#include"Admin.h"
#include "Appointment.h"  
#include "Prescription.h" 
#include "Bill.h"         
class FileHandler {
public:
	static void loadPatients(Storage<Patient>& storage) {
		ifstream file("Patient.txt");
		if (!file.is_open()) {
			throw FileNotFoundException();
		}
		char buffer[300];
		while (file.getline(buffer, 300)) {
			int pos = 0;
			char idStr[10], nameStr[50], ageStr[5], genderStr[2], contactStr[15], passStr[30], balStr[20];
			getField(buffer, idStr, pos);
			getField(buffer, nameStr, pos);
			getField(buffer, ageStr, pos);
			getField(buffer, genderStr, pos);
			getField(buffer, contactStr, pos);
			getField(buffer, passStr, pos);
			getField(buffer, balStr, pos);

			int id = Atoi(idStr);
			int age = Atoi(ageStr);
			char gender = genderStr[0];
			float balance = charToFloat(balStr);

			Patient p(id, nameStr, age, gender, contactStr, passStr, balance);
			storage.add(p);
		}
		file.close();
	}
	static void saveAppointment(const Appointment & app) {
		ofstream file("Appointment.txt", ios::app);
		if (file.is_open()) {
			file << app.getPatientID() << "," << app.getDoctorID() << "," << app.getDate() << endl;
			file.close();
		}
	}
	static void loadPrescriptions(Storage<Prescription>& storage) {
		ifstream file("Prescription.txt");
		if (!file.is_open()) {
			throw FileNotFoundException();
		}
		char buffer[300];
		while (file.getline(buffer, 300)) {
			int pos = 0;
			char idStr[10], dIDStr[10], med[20], pres[30];
			getField(buffer, idStr, pos);
			getField(buffer, dIDStr, pos);
			getField(buffer, med, pos);
			getField(buffer, pres, pos);
			

			int pID = Atoi(idStr);
			int dID = Atoi(dIDStr);

			Prescription p(pID, dID, med, pres);
			storage.add(p);
		}
		file.close();
	}
	static void savePrescription(const Prescription& p) {
		ofstream file("Prescription.txt", ios::app);
		if (file.is_open()) {
			file << p.getDoctorID() << "," << p.getPatientID() << "," << p.getDetails() << endl;
			file.close();
		}
	}
	static void saveBill(const Bill& b) {
		ofstream file("Bill.txt", ios::app);
		if (file.is_open()) {
			file << b.getPatientID() << "," << b.getAmount() << "," << b.getDescription() << endl;
			file.close();
		}
	}
	static void displaySecurityLog() {
		ifstream file("SecurityLog.txt");
		if(!file.is_open()) {
			cout << "No security incidents recorded yet." << endl;
		}
		char buffer[200];
		cout << "###### Security Logs ######" << endl;
		cout << "ID\tIncident Description" << endl;

		while (file.getline(buffer, 200)) {
			cout << buffer << endl;
		}
		file.close();
	}
	static void loadDoctors(Storage<Doctor>& storage) {
		ifstream file("Doctor.txt");
		if (!file.is_open()) {
			throw FileNotFoundException();
		}
		char buffer[300];
		while (file.getline(buffer, 300)) {
			int pos = 0;
			char idStr[10], nameStr[50], specStr[50], feeStr[50], passStr[30];
			getField(buffer, idStr, pos);
			getField(buffer, nameStr, pos);
			getField(buffer, specStr, pos);
			getField(buffer, feeStr, pos);
			getField(buffer, passStr, pos);

			int id = Atoi(idStr);
			
			float fee = charToFloat(feeStr);

			Doctor doc(id, nameStr, specStr, fee, passStr);
			storage.add(doc);
		}
		file.close();
	}
	static void loadAppointments(Storage<Appointment>& storage) {
		ifstream file("Appointment.txt");
		if (!file.is_open()) {
			return;
		}
		char buffer[300];
		while (file.getline(buffer, 300)) {
			int pos = 0;
			char pIDStr[10], dIDStr[10], date[20];

			getField(buffer, pIDStr, pos);
			getField(buffer, dIDStr, pos);
			getField(buffer, date, pos);
			int pid = Atoi(pIDStr);
			int did = Atoi(dIDStr);
			Appointment app(pid, did, date);
			storage.add(app);
		}
		file.close();
	}
	static void loadBills(Storage<Bill>& storage) {
		ifstream file("Bill.txt");
		if (!file.is_open()) {
			return;
		}
		char buffer[300];
		while (file.getline(buffer, 300)) {
			int pos = 0;
			char pIDStr[10], amtStr[10], desc[20];

			getField(buffer, pIDStr, pos);
			getField(buffer, amtStr, pos);
			getField(buffer, desc, pos);
			int pid = Atoi(pIDStr);
			float amount = Atoi(amtStr);
			Bill b(pid, amount, desc);
			storage.add(b);
		}
		file.close();
	}
	static void loadAdmins(Storage<Admin>& storage) {
		ifstream file("Admin.txt");
		if (!file.is_open()) {
			throw FileNotFoundException();
		}
		char buffer[300];
		while (file.getline(buffer, 300)) {
			int pos = 0;
			char idStr[10], nameStr[50], passStr[30];
			getField(buffer, idStr, pos);
			getField(buffer, nameStr, pos);
			getField(buffer, passStr, pos);

			int id = Atoi(idStr);
			Admin ad(id, nameStr,passStr);
			storage.add(ad);
		}
		file.close();
	}
	static void savePatient(const Patient& p) {
		ofstream file("Patient.txt", ios::app);
		if (file.is_open()) {
			file << p.getID() << "," << p.getName() << "," << p.getAge() << ","
				<< p.getGender() << "," << p.getContact() << "," << p.getPassword()
				<< "," << p.getBalance() << endl;
			file.close();
		}
	}
	static void saveAdmin(const Admin& a) {
		ofstream file("Admin.txt", ios::app);
		if (file.is_open()) {
			file << a.getID() << "," << a.getName() << "," << a.getPassword() << endl;
			file.close();
		}
	}
	static void logSecurityIncident(int id, const char* reason) {
		ofstream file("SecurityLog.txt", ios::app);
		if (file.is_open()) {
			file << id << "," << reason << endl;
			file.close();
		}
	}
	static void saveNewDoctor(const Doctor& d) {
		ofstream file("Doctor.txt", ios::app);
		file << d.getID() << "," << d.getName() << "," << d.getSpecialization() << "," << d.getFee() << "," << d.getPassword() << endl;
		file.close();
	}
};
#endif
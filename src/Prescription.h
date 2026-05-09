#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <iostream>
#include <cstring>
using namespace std;

class Prescription {
private:
	int prescriptionID;
	int appointmentID;
	int patientID;
	int doctorID;
	char medicines[200];
	char notes[300];
public:
	Prescription() : prescriptionID(0), appointmentID(0), patientID(0), doctorID(0) {
		medicines[0] = '\0';
		notes[0] = '\0';
	}
	Prescription(int docID, int pID, const char* meds) : prescriptionID(0), appointmentID(0), patientID(pID), doctorID(docID) {
		if (meds) {
			int i = 0;
			while (i < sizeof(medicines) - 1 && meds[i] != '\0') {
				medicines[i] = meds[i];
				i++;
			}
			medicines[i] = '\0';
		}
		else {
			medicines[0] = '\0';
		}
		notes[0] = '\0';
	}
	Prescription(int pID, int docID, const char* meds, const char* notes_) : prescriptionID(0), appointmentID(0), patientID(pID), doctorID(docID) {
		if (meds) {
			int i = 0;
			while (i < sizeof(medicines) - 1 && meds[i] != '\0') {
				medicines[i] = meds[i];
				i++;
			}
			medicines[i] = '\0';
		}
		else {
			medicines[0] = '\0';
		}

		if (notes_) {
			int i = 0;
			while (i < sizeof(notes) - 1 && notes_[i] != '\0') {
				notes[i] = notes_[i];
				i++;
			}
			notes[i] = '\0';
		}
		else {
			notes[0] = '\0';
		}
	}

	int getID() const {
		return prescriptionID;
	}

	int getPatientID() const {
		return patientID;
	}
	const char* getDetails() const {
		return medicines;
	}
	const char* getMedicines() const {
		return medicines;
	}
	const char* getNotes() const {
		return notes;
	}
	int getDoctorID() const {
		return doctorID;
	}

	friend ostream& operator<<(ostream& out, const Prescription& p);
};
ostream& operator<<(ostream& out, const Prescription& p) {
	out << "Prescription\n";
	out << "Prescription ID:\t" << p.prescriptionID << endl;
	out << "Appointment ID:\t" << p.appointmentID << endl;
	out << "Doctor ID:\t" << p.doctorID << endl;
	out << "Patient ID:\t" << p.patientID << endl;
	out << "Medicines:\t" << p.medicines << endl;
	out << "Notes:\t" << p.notes << endl;
	return out;
}

#endif
#ifndef APPOINTMENT_H
#define APPOINTMENT_H
class Appointment {
private:
	int appointmentID;
	int patientID;
	int doctorID;
	char date[11];
	char timeSlot[6];
	char status[15];
public:
	Appointment() : patientID(0), doctorID(0) {
		date[0] = '\0';
	}
	Appointment(int id, int pID, int dID, const char* date, const char* time, const char* status) {
		appointmentID = id;
		patientID = pID;
		doctorID = dID;
		int i;
		for (i = 0; date[i] != '\0' && i < 11; i++) {
			this->date[i] = date[i];
		}
		this->date[i] = '\0';
		for (i = 0; time[i] != '\0' && i < 6; i++) {
			this->timeSlot[i] = time[i];
		}
		this->timeSlot[i] = '\0';

		for (i = 0; status[i] != '\0' && i < 15; i++) {
			this->status[i] = status[i];
		}
		this->status[i] = '\0';
	}
	Appointment(int pID, int dID, const char* date) {
		appointmentID = 0;
		patientID = pID;
		doctorID = dID;
		int i;
		for (i = 0; date[i] != '\0' && i < 11; i++) {
			this->date[i] = date[i];
		}
		this->date[i] = '\0';
		const char* defTime = "09:00";
		for (i = 0; defTime[i] != '\0' && i < 6; i++) {
			this->timeSlot[i] = defTime[i];
		}
		this->timeSlot[i] = '\0';
		const char* defStatus = "Scheduled";
		for (i = 0; defStatus[i] != '\0' && i < 15; i++) {
			this->status[i] = defStatus[i];
		}
		this->status[i] = '\0';
	}
	void display() const {
		cout << "Appointment Detailes" << endl;
		cout << "Appointment ID:\t" << appointmentID << endl;
		cout << "Patient ID:\t" << patientID << endl;
		cout << "Doctor ID:\t" << doctorID << endl;
		cout << "Date:\t" << date << endl;
		cout << "Time Slot:\t" << timeSlot << endl;
		cout << "Status:\t" << status << endl;
	}
	int getPatientID() const {
		return patientID;
	}
	int getAppointmentID() const {
		return appointmentID;
	}
	int getDoctorID() const {
		return patientID;
	}
	const char* getDate() const {
		return date;
	}
	bool isSameChar(const char* ch1, const char* ch2) {
		int i = 0;
		while (ch1[i] != '\0' && ch2[i] != '\0') {
			if (ch1[i] != ch2[i]) {
				return false;
			}
			i++;
		}
		return true;
	}
	bool operator==(const Appointment& other) {
		if (isSameChar(this->date, other.date) && isSameChar(this->timeSlot, other.timeSlot) && this->doctorID == other.doctorID) {
			return true;
		}
		return false;
	}
};
#endif
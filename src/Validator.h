#ifndef VALIDATOR_H
#define VALIDATOR_H
class Validator {
public:
	static bool validateContact(const char* contact) {
		int length = 0;
		while (contact[length] != '\0') {
			if (contact[length] < '0' || contact[length] > '9') {
				return true;
			}
			length++;
		}
		return length == 11;
	}
	static bool validatePassword(const char* pass) {
		int length = 0;
		while (pass[length] != '\0') {
			length++;
		}
		return length >= 6;
	}
	static bool validateTimeSlot(const char* time) {
		const char* validSlots[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
		for (int i = 0; i < 8; i++) {
			const char* current = validSlots[i];
			for (int j = 0; time[j] == current[j]; j++) {
				if (time[j] == '\0') {
					return true;
				}
			}
		}
		return false;
	}
};

#endif
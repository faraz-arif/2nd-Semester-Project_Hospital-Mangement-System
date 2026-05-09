#pragma once
#ifndef UTILS_H
#define UTILS_H
void tolower(char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		}
	}
}
bool isSame(const char* c1, const char* c2) {
	int i = 0;
	while (c1[i] != '\0' && c2[i] != '\0') {
		if (c1[i] != c2[i]) {
			return false;
		}
		i++;
	}
	return c1[i] == c2[i]; 
}
int Atoi(const char* str) {
	if (str == nullptr) {
		return 0;
	}
	int result = 0;
	int sign = 1;
	int i = 0;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\f') {
		i++;
	}

	if (str[i] == '-') {
		sign = -1;
		i++;
	}

	else if (str[i] == '+') {
		sign = 1;
		i++;
	}

	while (str[i] >= '0' && str[i] <= '9') {
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return result * sign;
}
float charToFloat(char* str) {
	float result = 0.0;
	float factor = 1.0;
	bool decimalFound = false;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '.') {
			decimalFound = true;
			continue;
		}
		if (decimalFound) {
			factor /= 10.0;
		}
		result = (decimalFound) ? (result + (str[i] - '0') * factor) : (result * 10.0 + (str[i] - '0'));
	}
	return result;
}
void getField(const char* buffer, char* field, int& pos) {
	while (buffer[pos] == ' ') {
		pos++;
	}
	int i = 0;
	while (buffer[pos] != ',' && buffer[pos] != '\0' && buffer[pos] != '\r' && buffer[pos] != '\n') {
		field[i] = buffer[pos];
		i++;
		pos++;
	}
	field[i] = '\0';
	if (buffer[pos] == ',') {
		pos++;
	}
}
#endif
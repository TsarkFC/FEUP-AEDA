/*
 * Doctor.cpp
 */

#include <iostream>
#include "Doctor.h"


Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
    /*que, por necessidade urgente de um doente de código codP1, coloca este doente no início da fila
patients. Os restantes doentes presentes na fila mantêm a sua posição relativa. Se não existir nenhum
doente de código codP1 na fila patients, esta mantém-se inalterada.*/
    vector<Patient> pat;
    vector<Patient> urgent;

    if (patients.empty()) return;

    while(!patients.empty()){
        if (patients.front().getCode() == codP1) {
            urgent.push_back(patients.front());
            patients.pop();
        }
        else {
            pat.push_back(patients.front());
            patients.pop();
        }
    }
    //Insert urgent patient
    if (urgent.size() > 0) patients.push(urgent[0]);

    //Insert remaining patients
    for (auto i = pat.begin(); i != pat.end(); i++){
        patients.push(*i);
    }
}


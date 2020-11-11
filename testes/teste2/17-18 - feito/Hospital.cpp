/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    /*Esta função retorna o número de doentes que aguardam consulta da especialidade medicalSpecialty
no Hospital, isto é, que estão presentes na lista doctors. Note que pode existir mais do que um médico
da mesma especialidade.*/
    int counter = 0;

    for (auto i = doctors.begin(); i != doctors.end(); i++){
        if (i->getMedicalSpecialty() == medicalSpecialty){
            counter += i->getPatients().size();
        }
    }
	return counter;

}
bool sort_doc_method(Doctor d1, Doctor d2){
    if (d1.getPatients().size() < d2.getPatients().size()) return true;
    else if (d1.getPatients().size() == d2.getPatients().size()){
        if (d1.getMedicalSpecialty() < d2.getMedicalSpecialty()) return true;
        else if (d1.getMedicalSpecialty() == d2.getMedicalSpecialty()) return d1.getCode() < d2.getCode();
        else return false;
    }
    else return false;
}
void Hospital::sortDoctors() {
    doctors.sort(sort_doc_method);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	/*que insere um novo médico de código codM1 e especialidade medicalSpecialty1 no final da lista
doctors, se o número de médicos dessa especialidade existente no hospital for menor que 3, caso em
que a função retorna true. Se o número de médicos da especialidade for maior ou igual a 3, o médico
não é adicionado à lista e a função retorna false.*/
	Doctor *d = new Doctor(codM1, medicalSpecialty1);

	int counter = 0;
	for (auto i = doctors.begin(); i != doctors.end(); i++){
	    if (i->getMedicalSpecialty() == medicalSpecialty1) counter ++;
	}
	if (counter < 3) doctors.push_back(*d);
	else return false;

	return true;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
    /*Esta função elimina da lista doctors o médico de código codM1 e retorna a fila de doentes desse
médico. Se o médico não existir, deve ser lançada a exceção DoctorInexistent (esta exceção já está
definida na classe Hospital).*/
    queue<Patient> q;

    //Find doctor with codM1
    for (auto i = doctors.begin(); i != doctors.end(); i++){
        if (codM1 == i->getCode()){
            q = i->getPatients();
            doctors.erase(i);
            return q;
        }
    }

    throw DoctorInexistent();

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    /*Esta função aceita o doente de código codP1 e consulta de especialidade medicalSpecialty1 para
consulta no hospital. O doente deve ser adicionado à fila menos ocupada (com menor número de
elementos) dos médicos da especialidade medicalSpecialty1.
Se não existir nenhum médico com a especialidade pretendida, a função retorna false. Caso contrário,
retorna true.
Nota: Na classe Doctor, já está implementado o membro-função void addPatient(const Patient
&p1), que adiciona o doente p1 no final da lista de doentes do médico.*/
    Patient *p = new Patient(cod1, medicalSpecialty1);

    int min = 1000;
    bool foundDoc = false;

    for (auto i = doctors.begin(); i != doctors.end(); i++){
        if (i->getMedicalSpecialty() == medicalSpecialty1){
            foundDoc = true;
            if (i->getPatients().size() < min) {
                min = i->getPatients().size();
            }
        }
    }
    for (auto i = doctors.begin(); i != doctors.end(); i++){
        if (i->getMedicalSpecialty() == medicalSpecialty1 && min == i->getPatients().size()) i->addPatient(*p);
    }
	return foundDoc;
}



void Hospital::processPatient(unsigned codM1) {
    /*Esta função termina a consulta do próximo doente na fila do médico com o código codM1 da lista
doctors. O doente é retirado da fila e colocado na primeira bandeja disponível na lista letterTray.
As bandejas possuem uma capacidade limitada, pelo que só pode colocar o doente na bandeja que ainda
tiver espaço livre. Se não existir nenhuma bandeja com espaço livre, deve criar uma bandeja nova
(pilha) e colocá-la no final da lista letterTray.
Se não existir o médico de código codM1 ou a sua fila de doentes estiver vazia, nada é alterado.
Nota: Na classe Doctor, já está implementado o membro-função Patient removeNextPatient(),
que retira o próximo doente da fila de doentes do médico e retorna esse doente (lança uma exceção se
a fila está vazia).*/

    bool foundDoc = false;
    int counter = 0;

    for (auto i = doctors.begin(); i != doctors.end(); i++){
        if (codM1 == i->getCode()){
            if (i->getPatients().empty()) continue;

            for (auto j = letterTray.begin(); j != letterTray.end(); j++){
                counter ++;
                if (trayCapacity != j->size()) {
                    //Adds to tray
                    j->push(i->removeNextPatient());
                    return;
                }

                else if (counter == letterTray.size()){
                    //Creates new tray
                    stack<Patient> s;
                    s.push(i->removeNextPatient());
                    letterTray.push_back(s);
                    return;
                }
                else continue;
            }
        }
    }
}


unsigned Hospital::removePatients(unsigned codP1) {
	/*Esta função retira os doentes de código codP1 existentes no topo (e apenas no topo) das bandejas da
lista letterTray. Se alguma bandeja ficar vazia, esta deve ser eliminada da lista. Retorna o número
de doentes que retirou.*/

	int counter = 0;
    list<stack<Patient> >::iterator it;

	for (auto i = letterTray.begin(); i != letterTray.end(); i++){
	    if (letterTray.empty()) break;

        //if (i->empty()) {
        //    letterTray.erase(i);
        //    continue;
        //}
	    if (i->top().getCode() == codP1) {
            i->pop();
            counter++;
            if (i->empty()) {
                it = i;
                i--;
                letterTray.erase(it);


            }
        }
	}
	return counter;

}




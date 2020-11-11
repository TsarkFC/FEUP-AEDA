/*
 * Postman.cpp
 */
#include "Postman.h"
#include "PostOffice.h"
#include <iostream>
using namespace std;
int Postman::counter = 1;

Postman::Postman() : id(0) {}

Postman::Postman(string name){
    /*Este construtor recebe como argumento o nome (name) do carteiro. Atribui a cada objeto carteiro
criado um novo identificador (id), sequencial e incremental. O primeiro carteiro a ser criado terá id
igual a 1, o segundo id igual a 2 e assim sucessivamente. O vetor da correspondência a ser distribuída
pelo carteiro (myMail) está vazio.*/
    this->name = name;
    myMail = {};
    id = counter;
    counter++;
}
void Postman::setName(string nm) {
    name = nm;
}
string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &rhs) {
    /*Um carteiro p1 é menor que outro carteiro
p2, se o número de locais distintos a que tem de se deslocar para distribuir a sua correspondência
(myMail) é inferior. A identificação de um local é dada pelo código postal (zipCode) da
correspondência. Considere que o vector myMail se encontra ordenado por código postal da
correspondência.
Sugestão: se realizou a alínea a), utilize a função template aí implementada.*/

    vector<string> codes1;
    vector<string> codes2;
    vector<Mail*>::const_iterator it;
    for (it = myMail.begin(); it != myMail.end(); it++){
        codes1.push_back((*it)->getZipCode());
    }
    for (it = rhs.myMail.begin(); it != rhs.myMail.end(); it++){
        codes2.push_back((*it)->getZipCode());
    }

    if (numberDifferent(codes1) < numberDifferent(codes2)) return true;
    else return false;
}





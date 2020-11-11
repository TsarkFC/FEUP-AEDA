/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>
#include <iostream>
using namespace std;

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {
    /*Esta função remove do vetor postmen o carteiro de nome name, retornando a correspondência que
estava a cargo desse carteiro (myMail). Se não existe nenhum carteiro de nome name, a função
retorna um vetor vazio.*/
    vector<Mail*> temp = {};
    vector<Postman>::const_iterator it;

    for(it = postmen.begin(); it != postmen.end(); it++){
        if (it->getName() == name) {
            temp = it->getMail();
            postmen.erase(it);
            break;
        }
    }
    return temp;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
    /*verificar se o valor em caixa está correto. Esta função calcula o preço total relativo a toda a
correspondência entregue na estação de correios (vetor mailToSend) e coloca esse valor no
argumento balance*/
    /*tratar a correspondência entregue na estação de correios (esvaziar o vetor mailToSend), sendo: a
correspondência a entregar pelos carteiros adicionada ao vetor mailToDeliver (se zipCode está na
gama dos códigos postais da estação ([firstZipCode, lastZipCode]) ; a correspondência a enviar para
outras estações colocada num vetor que é o retorno da função endOfDay. Nota: A classe PostOffice já
possui o membro-função void addMailToDeliver(Mail *m)*/
    vector<Mail*>::iterator it;
    vector<Mail *> res;
    balance = 0;

    for (it = mailToSend.begin(); it != mailToSend.end(); it++){
        balance += (*it)->getPrice();
        if ((*it)->getZipCode() <= lastZipCode && (*it)->getZipCode() >= firstZipCode){
            addMailToDeliver(*it);
        }
        else res.push_back(*it);
    }
    mailToSend.erase(mailToSend.begin(), mailToSend.end());
    return res;
}

Postman PostOffice::addMailToPostman(Mail *m, string name) {
    /*Esta função adiciona a correspondência m ao vetor de correspondências que o carteiro de nome name
é responsável por distribuir (myMail) e retorna esse carteiro. Se não existir um carteiro de nome
name, a função deve lançar a exceção NoPostmanException. Esta classe exceção deve incluir o
membro-função getName() que retorna o nome do carteiro não existente.*/
    vector<Postman>::iterator it;

    for (it = postmen.begin(); it != postmen.end(); it++){
        if (it->getName() == name){
            (*it).addMail(m);
            return *it;
        }
    }
    throw NoPostmanException(name);
}



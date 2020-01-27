/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"
#include "Bank.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------
int inc_id = 1;
// a alterar
BankOfficer::BankOfficer(string name) {
    /*Este construtor recebe como argumento o nome (name) do bancário. Atribui a cada objeto bancário
criado um novo identificador (id), sequencial e incremental. O primeiro bancário a ser criado terá id
igual a 1, o segundo id igual a 2 e assim sucessivamente. O vetor das contas geridas pelo bancário
(myAccounts) está vazio.*/
    this->name = name;
    myAccounts = {};
    id = inc_id;
    inc_id++;
}
bool BankOfficer::operator>(const BankOfficer& b2) const{
    /*Um bancário b1 é maior que outro
bancário b2, se o número de contas que titula (myAccounts) é superior. Se o número de contas que os
dois bancários titulam for igual, b1 é maior que b2 se o seu nome for superior alfabeticamente.*/
    if (myAccounts.size() > b2.getAccounts().size()) return true;
    else if (myAccounts.size() == b2.getAccounts().size()){
        if (name > b2.getName()) return true;
        return false;
    }
    else return false;
}



/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    /*Esta função retorna o montante disponível para levantamento em todas as contas do cliente de código
cod1.*/
    vector<Account*>::const_iterator it;
    double amount = 0;
    for (it = accounts.begin(); it != accounts.end(); it++){
        if ((*it)->getCodH() == cod1) amount += (*it)->getWithdraw();
    }
	return amount;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	/*Esta função remove do vetor bankOfficers o bancário de nome name, retornando as contas geridas
por esse bancário (myAccounts). Se não existe nenhum bancário de nome name, a função retorna um
vetor vazio*/
	vector<BankOfficer>::const_iterator it = bankOfficers.begin();

	for (it; it != bankOfficers.end(); it++){
        if (it->getName() == name){
	        res = it->getAccounts();
	        bankOfficers.erase(it);
	        break;
	    }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    /*Esta função adiciona a conta ac ao vetor de contas bancárias que o bancário de nome name é
responsável por gerir (myAccounts) e retorna uma referência para esse bancário. Se não existir um
bancário de nome name, a função deve lançar a exceção NoBankOfficerException. Esta classe exceção
deve incluir o membro-função getName() que retorna o nome do bancário não existente.
*/

    vector<BankOfficer>::iterator it;

    for (it = bankOfficers.begin(); it != bankOfficers.end(); it++){
        if ((*it).getName() == name){
            (*it).addAccount(ac);
            return *it;
        }
    }
    throw NoBankOfficerException(name);
}

bool cmp_ac(Account* a1, Account* a2){
    if (a1->getBalance() < a2->getBalance()) return true;
    else if (a1->getBalance() == a2->getBalance()){
        if (a1->getCodIBAN() < a2->getCodIBAN()) return true;
    }
    else return false;
}

// a alterar
void Bank::sortAccounts() {
    /*Esta função ordena os elementos do vector accounts. As contas devem ficar ordenadas por ordem
crescente de saldo (balance) e, para o mesmo saldo, por ordem crescente de código (codeIBAN).*/
    sort(accounts.begin(), accounts.end(), cmp_ac);
}


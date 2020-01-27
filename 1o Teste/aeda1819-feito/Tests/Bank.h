/*
 * Bank.h
 */

#ifndef SRC_BANK_H_
#define SRC_BANK_H_

#include "Account.h"
#include <vector>

#include "BankOfficer.h"
#include <set>
template<class T>
unsigned int numberDifferent (const vector<T> & v1){

    typename vector<T>::const_iterator it;
    set<T> s;
    for (it = v1.begin(); it != v1.end(); it++){
        s.insert(*it);
    }
    return s.size();
}

class Bank {
	vector<Account *> accounts;
	vector<BankOfficer> bankOfficers;
public:
	Bank();
	void addAccount(Account *a);
	void addBankOfficer(BankOfficer b);
	vector<BankOfficer> getBankOfficers() const;
	vector<Account *> getAccounts() const;

	//-------
	double getWithdraw(string cod1) const;
	vector<Account *> removeBankOfficer(string name);
	const BankOfficer& addAccountToBankOfficer(Account *ac, string name);
	void sortAccounts();
};

class NoBankOfficerException{
    string name;
public:
    string getName() const{
        return name;
    }
    NoBankOfficerException(string nome){
        name = nome;
    }
};

bool cmp_ac(Account* a1, Account* a2);



#endif /* SRC_BANK_H_ */

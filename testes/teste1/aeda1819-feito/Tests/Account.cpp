/*
 * Account.cpp
 */
#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(string hold, string codeH, string codeA, double bal): holder(hold), codeHolder(codeH), codeIBAN(codeA), balance(bal) {}

Account::~Account(){ }

string Account::getCodH() const {
	return codeHolder;
}

string Account::getCodIBAN() const {
	return codeIBAN;
}

double Account::getBalance() const {
	return balance;
}

SavingsAccount::SavingsAccount (string hold, string codeH, string codeA, double bal, double pct):
		Account(hold, codeH, codeA, bal), rate(pct/100)
{ }


CheckingAccount::CheckingAccount(string hold, string codeH, string codeA, double bal,double lim):
			Account(hold, codeH, codeA, bal) {
	limit = lim;
}


TimeAccount::TimeAccount(string hold, string codeH, string codeA, double bal, double pct):
			SavingsAccount(hold, codeH, codeA, bal, pct) {
	funds_avail = balance*rate;
}

double CheckingAccount::getCharge() const {
    /*Para as contas de depósito (CheckingAccount) este valor depende do limite (limit) definido na
criação da conta:
0.50€, se limit <= 500€; 0.25€, se 500 < limit <= 1000€ ; 0€, se limit > 1000€*/
    if (limit <= 500) return 0.5;
    else if (limit > 1000) return 0;
    else return 0.25;
}

double SavingsAccount::getCharge() const {
    /*Para todas as contas poupança (SavingsAccount) depende da taxa de juro:
0.80€, se a percentagem da taxa de juro (rate*100) > 2.0; 0€ caso contrário*/
    if (rate*100 > 2) return 0.8;
    else return 0;
}

double Account::getWithdraw() const {
    return balance;
}

double TimeAccount::getWithdraw() const {
    return balance*rate;
}





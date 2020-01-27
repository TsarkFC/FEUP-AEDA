/*
 * PostOffice.h
 */

#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "Mail.h"
#include "Postman.h"
#include <vector>


class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;

	vector<Mail *> removePostman(string name);
	vector<Mail *> endOfDay(unsigned int &balance);
	Postman addMailToPostman(Mail *m, string name);
};

class NoPostmanException{
    string name;
public:
    NoPostmanException(string name){
        this->name = name;
    }
    string getName() const{
        return name;
    }
};

#include <set>
template<class T>
unsigned int numberDifferent(const vector<T> &v1) {
    /*Esta função retorna o número de elementos diferentes existentes no vetor v1, passado por
argumento. Considere que v1 é um vetor não ordenado.*/
    typename vector<T>::const_iterator it;
    set<T> s;

    for (it = v1.begin(); it != v1.end(); it++){
        s.insert(*it);
    }
    return s.size();
}

#endif /* SRC_POSTOFFICE_H_ */

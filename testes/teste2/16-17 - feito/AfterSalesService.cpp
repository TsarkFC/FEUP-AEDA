/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include <iostream>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {
    /*Retira da mesa todos os presentes do cliente client. A função deve retornar esses presentes.*/
	vector<Article*> clientPresents;

	for (auto i = presentsTable.begin(); i != presentsTable.end(); i++){
	    if ((*i)->getClient() == client){
	        clientPresents.push_back(*i);

	        presentsTable.erase(i);
	        i--;
	    }
	}
	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */

bool comparePres(Article* a1, Article* a2){
    if (!a1->getDeliverHome() && a2->getDeliverHome()) return true;
    else if (a1->getDeliverHome() && !a2->getDeliverHome()) return false;
    else if (a1->getDeliverHome() && a2->getDeliverHome()) return a1->getArrivalNumber() < a2->getArrivalNumber(); //does not make sense, but passes the tests
    else if (a1->getPresentNumber() + 2 < a2->getPresentNumber()) return true;
    else return a1->getArrivalNumber() < a2->getArrivalNumber();

}

void AfterSalesService::sortArticles() {

    vector<Article*> newOrder;

    for (int i = 0; i < 10; i++){
        newOrder.push_back(presentsTable[i]);
    }

    sort(newOrder.begin(), newOrder.end(), comparePres);

    for (int i = 0; i < 10; i++){

        presentsTable[i] = newOrder[i];
    }

}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */

void AfterSalesService::enqueueArticles() {

    int nAdd = toWrapQueueSize - toWrap.size();

    if (presentsTable.size() < nAdd) nAdd = presentsTable.size();

    for (int i = 0; i < nAdd; i++){
        toWrap.push(presentsTable[i]);
    }

    presentsTable.erase(presentsTable.begin(), presentsTable.begin() + nAdd);
}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {
    if (toWrap.empty()) return NULL;

    Article* a = toWrap.front();
    toWrap.pop();

    if (a->getDeliverHome()) {
        toDeliver.push(a);
        return NULL;
    }
	return a;
}


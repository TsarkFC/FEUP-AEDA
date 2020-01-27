
#include "HashTable.h"


HashTable::HashTable(){

    for(int i = 0; i < tableSize; i++){
        hashTable[i] = new item;
        hashTable[i]->person = NULL;
        hashTable[i]->currentlyWorking = false;
        hashTable[i]->next = NULL;
    }
}

HashTable::~HashTable() {
    item* Ptr;
    for(int i=0; i<tableSize; i++)
    {
        while(hashTable[i] != NULL)
        {
            Ptr = hashTable[i];
            hashTable[i] = hashTable[i]->next;
            delete Ptr;
        }
    }
}

int HashTable::hash(Person * key){
    int hashValue = 0, index;

    for(int i = 0; i < (key->getName()).length(); i++){
        hashValue = (int)(key->getName())[i];
    }

    index = hashValue % tableSize;

    return index;
}

void HashTable::addItem(Person * person){
    int index = hash(person);

    if(hashTable[index]->person == NULL){
        hashTable[index]->person = person;
        hashTable[index]->currentlyWorking = person->getIsWorking();
        hashTable[index]->next = NULL;
    }
    else{
        item * Ptr = hashTable[index];
        item * newItem = new item;
        newItem->person = person;
        newItem->currentlyWorking = person->getIsWorking();
        newItem->next = NULL;

        while(Ptr->next != NULL){
            Ptr = Ptr->next;
        }

        Ptr->next = newItem;

    }
}

int HashTable::numberOfItemsInIndex(int index) {

    int nr_items = 0;

    if(hashTable[index]->person == NULL){
        return nr_items;
    }
    else {
        item * Ptr = hashTable[index];
        nr_items++;

        while(Ptr->next != NULL){
            nr_items++;
            Ptr = Ptr->next;
        }
    }

    return nr_items;
}

void HashTable::removeItem(Person *person) {
    int index = hash(person);

    item* delete_Ptr;
    item* P1;
    item* P2;

    if(hashTable[index]->person == NULL){
        cout << "The person you are trying to delete doens't exist.\n";
    }
    else if(hashTable[index]->person = person){

        if(hashTable[index]->next == NULL){
            hashTable[index]->person = NULL;
            hashTable[index]->currentlyWorking = false;

            cout << "The person was remove with success.\n";

        }
        else{
            delete_Ptr = hashTable[index];
            hashTable[index] = hashTable[index]->next;
            delete delete_Ptr;

            cout << "The person was remove with success.\n";
        }
    }
    else {
        P1 = hashTable[index]->next;
        P2 = hashTable[index];

        //As long as we are finding an item but it isn't equal to the person we want to find then we advance
        while(P1 != NULL & P1->person != person){
            P2 = P1;
            P1 = P1->next;
        }

        if(P1 == NULL){
            cout << "The person you are trying to delete doens't exist.\n";
        }
        else {
            delete_Ptr = P1;
            P1 = P1->next;
            P2->next = P1;

            delete delete_Ptr;

            cout << "The person was remove with success.\n";
        }

    }

}

void HashTable::printAll() {
    item item_to_print;
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i]->person == NULL){continue;}

        item_to_print = *hashTable[i];
        item_to_print.person->print(cout);

        while(item_to_print.next != NULL){
            item_to_print = *item_to_print.next;

            item_to_print.person->print(cout);
        }
    }
}

void HashTable::printCurrent() {
    item item_to_print;

    for(int i = 0; i < tableSize; i++){
        if(hashTable[i]->person == NULL){continue;}

        item_to_print = *hashTable[i];

        if(item_to_print.currentlyWorking){
            item_to_print.person->print(cout);
        }


        while(item_to_print.next != NULL){
            item_to_print = *item_to_print.next;

            if(item_to_print.currentlyWorking){
                item_to_print.person->print(cout);
            }
        }
    }

}

void HashTable::printOld() {
    item item_to_print;

    for(int i = 0; i < tableSize; i++){
        if(hashTable[i]->person == NULL){continue;}

        item_to_print = *hashTable[i];

        if(!item_to_print.currentlyWorking){
            item_to_print.person->print(cout);
        }


        while(item_to_print.next != NULL){
            item_to_print = *item_to_print.next;

            if(!item_to_print.currentlyWorking){
                item_to_print.person->print(cout);
            }
        }
    }
}

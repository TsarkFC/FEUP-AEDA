//
// Created by berna on 23/12/2019.
//

#include <cstdlib>
#include <iostream>
#include "People/Person.h"

using namespace std;

#ifndef AEDA_TEAM_MANAGER_HASHTABLE_H
#define AEDA_TEAM_MANAGER_HASHTABLE_H


class HashTable {

    /**
     * Size of the Hash Table
     */
    static const int tableSize = 40;

    /**
     * Items that will be saved in the Hash Table
     */
    struct item{
        Person * person;
        bool currentlyWorking;
        item * next;
    };

    /**
     * Array of items that makes up the Hash Table
     */
    item* hashTable[tableSize];

public:
    /**
     * Constructor of the HashTable.
     * It initializes the hashTable with default values
     */
    HashTable();

    /**
     * Destructor of the HashTable
     */
    virtual ~HashTable();

    /**
     * Generates an hash value for the given key.
     * That hash value its used to get the position
     * of the array in which to store that key
     * @param key - person pointer to use to generate the hash value
     * @return int representing the index of the table where you store the key
     */
    int hash(Person * key);

    /**
     * Gets the index value for the person given in the param.
     * Uses that index to insert the person in the table.
     * @param person - Pointer to the person to be added
     */
    void addItem(Person * person);

    /**
     * Tells the number of items in a certain index
     * @param index - index to count the number of items
     * @return an int representing the number of items in the given index
     */
    int numberOfItemsInIndex(int index);

    /**
     * Removes the item containing the given person
     * @param person - key to the item to be deleted
     */
    void removeItem(Person * person);

    /**
     * Prints all the technicians information in a table
     */
    void printAll();

    /**
     * Prints all the old technicians information in a table
     */
    void printOld();

    /**
     * Prints all the current technicians information in a table
     */
    void printCurrent();
};


#endif //AEDA_TEAM_MANAGER_HASHTABLE_H

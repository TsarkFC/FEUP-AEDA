
#ifndef AEDA_TEAM_MANAGER_PERSON_H
#define AEDA_TEAM_MANAGER_PERSON_H
#pragma once
#include "..//Date.h"
#include <string>
#include <fstream>
#include <ostream>
#include <iomanip>
#include "..//Utilities.h"



class Person {

protected:
    /**
     * ID of the Person
     * Everyone has an ID so it easy to identify each person
     */
    int id;

    /**
     * Person's Name
     */
    string name;

    /**
     * Represents the Person's Birthday Date
     */
    Date birthdayDate;

    /**
     * Represents the current Salary of a person
     */
    float salary;

    /**
     * Static variable to keep ID always updated and orderd
     */
    static int lastId;

    /**
     * Tells if the person is currenly working
     */
     bool isWorking;


public:
    /**
     * @brief Construct a new Person object given his name, birthday and salary
     * @param name Represent person's name
     * @param birthdayDate  Represent person's birthday date
     * @param salary  - Represent person's salary
     */
    Person(string name, Date birthdayDate, float salary);


    /**
     * @brief Construct a default Person object with no paramters
     */
    Person();



    /*****************************
     **********GETTERS************
     *****************************/

    /** Gets the person's id.
     * @return A Int representing the person’s id
    */
    int getId() const;

    /**
     * Gets the person's name
     * @return  string - Representing person's name
     */
    string getName() const;

    /**
     * Gets Person's Birthday date
     * @return Date - Represents person's birthday Date
     */
    Date getBirthday() const;

    /**
     * Gets Person's Salary
     * @return float - Represents person's current salary
     */
    float getSalary() const;

    /**
     * Gets if the Person is workingy
     * @return float - Represents if the person is working
     */
    bool getIsWorking() const;



    /*****************************
     **********SETTERS************
     *****************************/

    /** Sets the person’s  name.
     * @param name - A String containing the person’s
     *   name.
    */
    void setName(string name);

    /** Sets the person’s  birthday date.
     * @param birthdayDate - A Date containing the person’s birthday
     *   date.
    */
    void setBirthday(Date birthdayDate);

    /** Sets the person’s  salary.
     * @param salary - A float containing the person’s
     *   salary.
    */
    void setSalary(float salary);

    /** Sets if the person is working.
     * @param isWorking - A bool telling if the person is working
     * or not.
    */
    void setIsWorking(bool isWorking);


    /***************************************
     **********VIRTUAL FUNCTIONS************
     ***************************************/

    /**
     * @brief virtual function that modifies the caller, given a new Person pointer
     * @param - *newPerson - a pointer to a Person with all the information
     * @return void
    */
    virtual void modify(Person *newPerson);

    /**
     * @brief virtual function that prints the caller in a table format, given an ostream variable
     * @param - ostream os - Tells where to print the content
     * @return void
    */
    virtual void print(ostream& out) const;

    /**
     * @brief virtual function that prints the caller in the file format, given an ostream variable
     * @param - ostream os - Tells where to print the content
     * @return void
     */
    virtual void printToFile(ostream &os) const;

    /**
     * @brief virtual function that reads a specific Person , given an ifstream variable
     * @param - ifstream file - Tells where to output the Person information
     * @return void
    */
    virtual void read(ifstream *file);

    /**
     * @brief constant virtual function that returns the type of the Caller, if it is
     * either a Person, Football Player or Technician
     * @param -
     * @return string - Type of the Person*
     */
    virtual string type() const ;

    /***************************************
     **************OPERATORS****************
     ***************************************/


    /**
     *@brief Operator to see if the person's caller id is smaller than person.id
     * @param person
     * @return bool - True if caller id is smaller than person.id
     */
    bool operator<(const Person &person) const;


    /**
     *@brief Operator to see if the person's caller id is smaller than person->id
     * @param person
     * @return bool - True if caller id is smaller than person->id
     */
    bool operator<(const Person* &person) const;

    /**
     * @brief Operator to see if the person's caller id is bigger than person.id
     * @param person
     * @return bool - True if caller id is bigger than person.id
     */
    bool operator>(const Person &person) const;

    /**
     * @brief Operator to see if the person's caller id is equal to person.id
     * @param person
     * @return bool - True if caller id is equal to person.id
     */
    bool operator==(const Person &rhs) const;

    /**
     * @brief Operator to see if the person's caller id is equal to person.id
     * @param person
     * @return bool - True if caller id is different than person.id
     */
    bool operator!=(const Person &rhs) const;

    /**
     * @brief Output operator calls printId function so it outputs a formatted Person
     * @param ostream os - Ostream variable that tells where to output the Person
     * @param Person* - Pointer to the Person we want to print
     * @return Ostream - Returns formatted Data
     */
    friend ostream &operator<<(ostream &os, const Person *person);

    friend ostream &operator<<(ostream &os, const Person person);





};



#endif //AEDA_TEAM_MANAGER_PERSON_H

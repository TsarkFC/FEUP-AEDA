#pragma once
#ifndef AEDA_TEAM_MANAGER_TECHINICALTEAM_H
#define AEDA_TEAM_MANAGER_TECHINICALTEAM_H

#include "Person.h"


class Technician: public Person{
    /**
     * Technician's Role
     * A string that represents what the Technician does for the team
     */
    string role;
public:



    /**
     * @brief Construct a default Technician object with no paramters
     */
    Technician();

    /**
     * @brief Construct a Technician
     * @param name - string that represents person's first and last name
     * @param birthday -Date that represents person's birthday
     * @param salary - float that represents what is the salary of this person
     * @param role - string that tells what the person does in the team
     */
    Technician(string name, Date birthday, float salary, string role);

    /**
     * Gets the technician's role
     * @return string representing the role
     */
    const string getRole() const;

    /** Sets the person’s  role.
     * @param name - A String containing the person’s
     *   role.
    */
    void setRole(const string &role);

    /**
     * @brief constant virtual function that returns the type of the Caller,
     * In this case, "Technician"
     * @return string - "Technician"
     */
    virtual string type() const ;

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
    virtual void printToFile(ostream &out) const;

    /**
     * @brief virtual function that reads a specific Technician , given an ifstream variable
     * @param - ifstream file - Tells where to output the Person information
     * @return void
    */
    virtual void read(ifstream *file);

};


#endif //AEDA_TEAM_MANAGER_TECHINICALTEAM_H

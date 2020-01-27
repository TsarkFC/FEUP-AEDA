//
// Created by tiago on 22/12/2019.
//

#ifndef AEDA_TEAM_MANAGER_COACH_H
#define AEDA_TEAM_MANAGER_COACH_H

#include "Person.h"
#include <vector>


class Coach : public Person {
private:
    /**
     * Titles won by the coach
     */
    int titlesWon;

    /**
     * Vector containing all the teams the coaches has been at
     */
    vector<string> coachedTeams;

    /**
     * Boolean flag to check if he is the current coach
     */
    bool isCurrentCoach;
public:

    /**
     * Construct new coach object with the given parameters
     * @param name
     * @param birthdayDate
     * @param salary
     * @param titlesWon
     * @param coachedTeams
     * @param isCurrentCoach
     */
    Coach(const string &name, const Date &birthdayDate, float salary, int titlesWon,
          const vector<string> &coachedTeams, const bool &isCurrentCoach);

    /**
     * Default constructor
     */
    Coach();

    /**
     * Gets the numbers of titles coach has won
     * @return integer variable that represents the number of titles
     */
    int getTitlesWon() const;

    /**
     * Sets titlesWon has the number of titles a coach has won
     * @param titlesWon
     */
    void setTitlesWon(int titlesWon);

    /**
     * Checks if a coach is at National Team for the moment
     * @return
     */
    int isActualCoach() const;

    /**
     * Sets the coach as the National Team coach
     * @param isCurrentCoach
     */
    void setIfCurrentCoach(const bool &isCurrentCoach);

    /**
     * Gets the coached teams by the coach
     * @return vector of string names of the teams the coach has been at
     */
    const vector<string> &getCoachedTeams() const;

    /**
     * Sets coachedTeams has the list of teams the coach has been at
     * @param coachedTeams
     */
    void setCoachedTeams(const vector<string> &coachedTeams);

    /**
     * Modifies coach with an existing person values
     * @param newPerson
     */
    virtual void modify(Person *newPerson);

    /**
     * Return a string "Coach", that remarks that this person is a coach
     * @return
     */
    virtual string type() const;

    /**
     * Reads coach information from text file
     * @param file
     */
    virtual void read(ifstream *file);

    /**
     * Displays coach information saying that he is or not the current coach on the screen
     * @param out
     */
    virtual void print(ostream &out) const;

    /**
     * Saves coach information into a text file
     * @param os
     */
    virtual void printToFile(ostream &os) const;

    /**
     * Displays coach information on the screen
     * @param out
     */
    void printCoach(ostream &out) const;

    /**
     * Defines the criteria of comparison between two coaches
     * @param coach
     * @return
     */
    bool operator<(const Coach* &coach) const;

    /**
     * Defines the criteria of comparison between two coaches
     * @param coach
     * @return
     */
    bool operator<(const Coach &coach) const;














};

#endif //AEDA_TEAM_MANAGER_COACH_H

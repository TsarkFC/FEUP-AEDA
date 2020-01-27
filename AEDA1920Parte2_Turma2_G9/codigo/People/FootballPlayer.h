#ifndef AEDA_TEAM_MANAGER_FootballPlayer_H
#define AEDA_TEAM_MANAGER_FootballPlayer_H
#pragma once

#include "Person.h"
#include <vector>

using namespace std;

class FootballPlayer : public Person {
private:
    /**
     * Position of the player in the team,
     * Attacking Midfield, Sweeper etc...
     */
    string position;

    /**
     * Club where the player came from
     */
    string club;

    /**
     * Player's Weight
     */
    float weight;

    /**
     * Person's Height
     */
    float height;

    /**
     * How much is the player worth
     */
    float pass_value;

    /**
     * True if the Player is injured, false if he is healthy
     */
    bool injury;

public:

    /**
     * @brief Construct a new Football Player object given his name, birthday, salary,
     * position, club, weight, height, pass value and if he is injured
     * @param name Represent person's name
     * @param birthdayDate  Represent person's birthday date
     * @param salary  - Represent person's salary
     */
    FootballPlayer(string name, Date birthDay, float salary, string position, string club, const float weight,
                   const float height, float pass_value, bool injury);

    /**
     * @brief Construct a default Football Player object with no paramters
     * position = "";
     * club = "";
     * weight= 0;
     * height = 0;
     * pass_value = 0.0;
     * injury= false;
     */
    FootballPlayer();

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
    virtual void print(ostream &out) const;

    /**
     * @brief virtual function that prints the caller in the file format, given an ostream variable
     * @param - ostream os - Tells where to print the content
     * @return void
     */
    virtual void printToFile(ostream &os) const;

    /**
     * @brief virtual function that reads a specific Football Player , given an ifstream variable
     * @param - ifstream file - Tells where to output the Player's information
     * @return void
    */
    virtual void read(ifstream *file);

    /**
     * @brief constant virtual function that returns the type of the Caller, if it is
     * either a Person, Football Player or Technician
     * @param -
     * @return string - "Football Player"
     */
    virtual string type() const;


    /*****************************
     **********GETTERS************
     *****************************/

    /**
     * Gets player position
     * @return position of the player in the team
     */
    const string &getPosition() const;

    /**
     * Gets the club where the player came from
     * @return string - Represents the club
     */
    const string &getClub() const;

    /**
     * Gets the person's weight
     * @return float with person's weight
     */
    float getWeight() const;

    /**
     * Gets person's height
     * @return float representing the weight
     */
    float getHeight() const;

    /**
     * Gets Person's pass value
     * @return float representing how much the player is worth
     */
    float getPassValue() const;

    /**
     * Tells if the player is ijured or not
     * @return true if the player is injured, false otherwise
     */
    bool isInjury() const;


    /**
     * Sets the player's club
     * @param club - constant string representing player's club
     */
    void setClub(const string &club);


    /**
     * Sets the player's weight
     * @param weight - float representing player's weight
     */
    void setWeight(float weight);


    /**
     * Sets the player's height
     * @param height - float representing player's height
     */
    void setHeight(float height);


    /**
     * Sets the player's pass value
     * @param passValue - float representing player's pass value
     */
    void setPassValue(float passValue);


    /**
     * Sets if the player is injured or not
     * @param injury - bool representing player's club
     * true if the player is injred
     */
    void setInjury(bool injury);


    /**
     * Sets player's position
     * @param const string &position - represent payer's position
     */
    void setPosition(const string &position);
};


#endif //AEDA_TEAM_MANAGER_FootballPlayer_H

//
// Created by tiago on 19/10/2019.
//

#ifndef AEDA_TEAM_MANAGER_CALLUPPLAYER_H
#define AEDA_TEAM_MANAGER_CALLUPPLAYER_H
#pragma once

#include "People//FootballPlayer.h"


using namespace std;


class PlayerGameStatistics {
private:

    /**
     * ID of the Statistic
     * Every statistic has an ID so it easy to identify each statistics
    */
    int id;

    /**
     * ID of the Player that the statistic belongs to
     * Every player has an ID so it easy to identify each player
    */
    int playerID;

    /**
     * Number of Goals Score by the Player
    */
    int numberOfGoals;

    /**
     * Minutes Played but the Player
     */
    int minutesPlayed;

    /**
     * Kilometers the Player ran
     */
    int kilometers;

    /**
     * Number of Passes the Player made
     */
    int numberOfPasses;

    /**
     * Number of Yellow Cards the Player received
     */
    int numberOfYellowCards;

    /**
     * Number of Red Cards the Player received
     */
    int numberOfRedCards;

    /**
     * Static variable to keep ID always updated and ordered
     */
    static int lastId;

public:

    /**
     * @brief Constructor of the Statistics of a player given all its attributes
     * @param playerID - Represents the ID of the player
     * @param numberOfGoals - Represents the number of goals by the player
     * @param minutesPlayed - Represents the minutes played by the player
     * @param kilometers - Represents the kilometers ran by the player
     * @param numberOfPasses - Represents the number of passes made by the player
     * @param numberOfYellowCards - Represents the number of Yellow Cards given to the player
     * @param numberOfRedCards - Represents the number of Red Cards given ot the player
     */
    PlayerGameStatistics(int playerID, int numberOfGoals, int minutesPlayed, int kilometers, int numberOfPasses, int numberOfYellowCards, int numberOfRedCards);

    /**
     * Contructor of the Statistics of a player given his playerID
     * @param playerID - Represents the ID of the player
     */
    PlayerGameStatistics(int playerID);

    /**
     * Default Constructor of PlayerGameStatistics
     */
    PlayerGameStatistics();







    /*****************************
     **********GETTERS************
     *****************************/

    /**
     * Return the Statistics's id
     * @return - An Int representing the statistics's
     * id.
     */
    int getId() const;

    /** Returns the player's id
     * @return A Int representing the player’s id
    */
    int getPlayerID() const;

    /**
     * Returns the number of goals scored by the player
     * @return - An Int representing the number of goals
     */
    int getNumberOfGoals() const;

    /**
     * Returns the minutes played by the player
     * @return - An Int representing the minutes
     */
    int getMinutesPlayed() const;

    /**
     * Returns the kilometers ran by the player
     * @return - An Int representing the kilometers
     */
    int getKilometers() const;

    /**
     * Returns the number of passes made by the player
     * @return - An Int representing the number of
     * passes
     */
    int getNumberOfPasses() const;

    /**
     * Returns the number of yellow cards given to the player
     * @return - An Int representing the number of
     * yellow cards.
     */
    int getNumberOfYellowCards() const;

    /**
     * Returns the number of red cards given to the player
     * @return - An Int representing the number of
     * red cards.
     */
    int getNumberOfRedCards() const;







    /*****************************
    ***********SETTERS************
    *****************************/

    /**
     * Changes the player's id
     * @param playerID - An integer representing the
     * new player's id.
     */
    void setPlayerID(int playerID);

    /**
     * Changes the number of goals scored by the player
     * @param numberOfGoals - An integer representing the
     * number of goals
     */
    void setNumberOfGoals(int numberOfGoals);

    /**
     * Changes the minutes played by the player
     * @param minutesPlayed - An integer representing
     * the minutes played.
     */
    void setMinutesPlayed(int minutesPlayed);

    /**
     * Changes the kilometers ran by the player
     * @param kilometers - An integer representing
     * the new kilometers
     */
    void setKilometers(int kilometers);

    /**
     * Changes the number of passes
     * @param numberOfPasses - An integer representing
     * the number of passes
     */
    void setNumberOfPasses(int numberOfPasses);

    /**
     * Changes the number of Yellow Cards given to the player
     * @param numberOfYellowCards - An integer representing
     * the number of yellow cards.
     */
    void setNumberOfYellowCards(int numberOfYellowCards);

    /**
     * Changes the number of Red Cards given to the player
     * @param numberOfRedCards - An integer representing
     * the number of red cards.
     */
    void setNumberOfRedCards(int numberOfRedCards);






    /*****************************
    *************PRINT************
    *****************************/

    /**
     * @brief function that prints the caller in a table format, given an ostream variable
     * @param - ostream os - Tells where to print the content
    */
    void print(ostream &os);

    /**
     * Prints Statistics information to correspondent file
     * @param os
     */
    void printIntoFile(ostream &os) const;
};

//PLAYER STATISTCS EXCEPTIONS
class NegativeParameter{
public:
    /**
     * negative number inserted by user
     */
    int num;
    /**
     * Constructs object to be thrown when user inserts negative statistics for player
     * @param num
     */
    NegativeParameter(int num){
        this->num = num;
        cout << endl << endl << "Statistics cannot have negative value!" << endl;
    }
};

class InvalidMinutes{
public:
    /**
     * Invalid number of minutes inserted by user
     */
    int minutes;
    /**
     * Constructs object to be thrown when user inserts invalid playing minutes for player
     * @param minutes
     */
    InvalidMinutes(int minutes){
        this->minutes = minutes;
        cout << endl << endl << "Minutes value has to be between 1 and 90!" << endl;
    }
};

class InvalidYellowCard{
public:
    /**
     * Invalid number of yellows insertes by user
     */
    int yellows;
    /**
     * Constructs object to be thrown when user inserts invalid number of yellow cards
     * @param yellows
     */
    InvalidYellowCard(int yellows){
        this->yellows = yellows;
        cout << endl << endl << "Number of yellows has a max value of 2!" << endl;
    }
};

class InvalidRedCard{
public:
    /**
     * Invalid number of reds inserted by user
     */
    int reds;
    /**
     * Constructs object to be thrown when user inserts invalid number of red cards
     * @param reds
     */
    InvalidRedCard(int reds){
        this->reds = reds;
        cout << endl << endl << "Number of reds cannot be higher than 1 and depends on the number of yellows!" << endl;
    }
};

#endif //AEDA_TEAM_MANAGER_CALLUPPLAYER_H

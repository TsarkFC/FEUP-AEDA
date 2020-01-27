#pragma once
#ifndef AEDA_TEAM_MANAGER_GAME_H
#define AEDA_TEAM_MANAGER_GAME_H

#include <string>
#include <vector>
#include "PlayerGameStatistics.h"

using namespace std;

class Game {
private:


    /**
     * ID of the Game
     * Every game has an ID so it easy to identify each game
    */
    int id;

    /**
     * City where the game takes place
     */
    string city;

    /**
     * Country where the game takes place
     */
    string country;

    /**
     * Name of the stadium where the game takes place
     */
    string stadium;

    /**
     * Name of the teams that played in the game
     * Format: Portugal x <Name_of_the_other_City>
     */
    string game_title;

    /**
     * Vector that stores the statistics of each
     * player in the nationak team
     */
    vector<PlayerGameStatistics> playerStatistics;

    /**
     * Vector that stores a pointer to each of the
     * national players in the game
     */
    vector<FootballPlayer *> nationalPlayers;

    /**
     * Vector that stores the name of each of the
     * enemy team players (First and Last Name)
     */
    vector<string> enemyPlayers;

    /**
     * Vector that stores the name of each of the
     * referees in the game (First and Last Name)
     */
    vector<string> referees;

    /**
     * Static variable to keep ID always updated and orderd
     */
    static int lastID;


public:

    /**
     * @brief Constructor of a new game given the all its attributes
     * @param game_title - Represents the game_title
     * @param city - Represents the name of city
     * @param country - Represents the name of country
     * @param stadium - Represents the name of the stadium
     * @param playerStatistics - Represents the statistics
     * of all players in the national team
     * @param referees - Represents the names of the referees
     * @param nationalP - Represents the players of the national
     * team
     * @param enemyP - Represents the name of the players in the
     * enemy team
     */
    Game(string game_title, string city,string country,string stadium,vector<PlayerGameStatistics> playerStatistics,vector<string> referees, vector<FootballPlayer *> nationalP, vector<string> enemyP);


    /**
     * @brief Default constructor of a new game
     */
    Game();








    /*****************************
     **********GETTERS************
     *****************************/

    /** Returns the game's id.
     * @return A Int representing the game’s id
    */
    int getId() const;

    /** Returns the name of the city where the game takes place
     * @return A string representing the name of the city
    */
    string getCity() const;

    /** Returns the name of the country where the game takes place
     * @return A string representing the name of the country
    */
    string getCountry() const;

    /** Returns the name of the stadium where the game takes place
     * @return A string representing the name of the stadium
    */
    string getStadium() const;

    /**
     * Returns the Game Title
     * @return A string representing the game's title
     */
    string getGameTitle() const;

    /** Returns the vector containing a pointer to the National Team Players
     * @return A vector containing FootballPlayer * representing the National Team Players
    */
    vector<FootballPlayer *> getNationalPlayers() const;

    /** Returns the name of the enemy team players
     * @return A vector of string representing the name of all the enemy team players
    */
    vector<string> getEnemyPlayers() const;

    /** Returns the statistics of all the National Team Players in the game
     * @return A vector of PlayerGameStatistics representing all of the statistics
    */
    vector<PlayerGameStatistics> getPlayerStatistics() const;

    /** Returns the name of the referees in the game
     * @return A vector of string representing the name of all the referees
    */
    vector<string> getReferees();






    /*****************************
    ***********SETTERS************
    *****************************/

    /** Changes the Game Tile
     * @param game_title - A String containing the Game Title
     *   name.
    */
    void setGameTitle(string game_title);

    /** Changes the name of the City
     * @param city - A String containing the city's name
     *   name.
    */
    void setCity(string city);

    /** Changes the name of the Country
     * @param country - A String containing the name of the
     *   country.
    */
    void setCountry(string country);

    /** Changes the name of the Stadium
     * @param stadium - A String containing the name of the
     *   stadium.
    */
    void setStadium(string stadium);

    /** Changes the National Team Players
     * @param vec - A vector containing pointers to each of the
     *   National Team players.
    */
    void setNationalPlayers(vector<FootballPlayer *> vec);

    /** Changes the Enemy Team Players
     * @param vec - A vector containing string to each of the
     *   Enemy Team players's name.
    */
    void setEnemyPlayers(vector<string> vec);

    /** Changes the National Team Players's Statistics
     * @param statistics - A vector containing pointer to each of the
     *   National Team players.
    */
    void setPlayerStatistics(vector<PlayerGameStatistics> statistics);

    /** Changes the Referees
     * @param refs - A vector containing string to each of the
     *   Referees's name.
    */
    void setReferees(vector<string> refs);









    /*****************************
    ************ADDERS************
    *****************************/

    /**
     * Adds a players to the vector containing pointers to each of
     * the National Team players.
     * @param player - A pointer to the football players to be added
     * to the National Team.
     * @param stats - The statistics of the player to be added to the
     * National Team
     */
    void addNationalPlayer(FootballPlayer * player, PlayerGameStatistics stats);

    /**
     * Adds the name of an enemy player to the vector containing the names
     * of each of the enemy team player.
     * @param player - A string representing the name of the enemy to be
     * added to the enemy team.
     */
    void addEnemyPlayer(string player);

    /**
     * Adds the name of a referee to the vector containing the names
     * of each of the referees
     * @param referee
     * @return An integer representing if the fuction ran successfully.
     * 1 represents success and 0 represents unsuccess.
     */
    int addReferee(string referee);

    /*****************************
    ***********REMOVERS***********
    *****************************/

    /**
     * Removes a National Team Player from the vector containing pointers
     * to all the National Team Players.
     * @param player - A FootballPlayer pointer to the players to be removed
     * from the National Team.
     */
    void removeNationalPlayer(FootballPlayer * player);

    /**
     * Removes the name of an Enemy Team Player from the vector containing the
     * names of the Enemy Team Players.
     * @param player - A string containing the name of the enemy team player to
     * be removed from the Enemy Team.
     */
    void removeEnemyPlayer(string player);

    /**
     * Removes the name of the Referee from the vector containing the
     * names of all the referees.
     * @param referee - A string containing the name of the referee to be
     * removed from the referees.
     */
    void removeReferee(string referee);

    /**
     * Returns the Game Statistics for a specific player in the National
     * Team.
     * @param player - A FootballPlayer pointer to the specific player
     * that the user picked
     * @return -
     */
    PlayerGameStatistics getSpecificPlayerStatistics(FootballPlayer * player);








    /*****************************
    *************PRINT************
    *****************************/

    /**
     * @brief function that prints the caller in the file format, given an ostream variable
     * @param - ostream os - Tells where to print the content
     */
    void printIntoFile(ostream &os) const;

    /**
     * @brief function that prints the caller in a table format, given an ostream variable
     * @param - ostream os - Tells where to print the content
    */
    void print(ostream &os);







    /***************************************
     **************OPERATORS****************
     ***************************************/

    /**
     * @brief Outputs a formatted Game
     * @param ostream os - Ostream variable that tells where to output the Game
     * @param Person* - Reference to the Game we want to print
     * @return Ostream - Returns formatted Data
     */
    friend ostream& operator<< (ostream& out, const Game& game);
};


#endif //AEDA_TEAM_MANAGER_GAME_H

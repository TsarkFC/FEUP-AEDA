#ifndef AEDA_TEAM_MANAGER_CALLUP_H
#define AEDA_TEAM_MANAGER_CALLUP_H
#pragma once
#include <vector>
#include "Date.h"
#include "Game.h"
#include "CallUpPlayerStatistics.h"
#include "Exceptions.h"
using namespace std;

class CallUp {
private:
    /**
     * Call up id
     */
    int id;
    /**
     * Costs associated with insurance and accomodation in call up
     */
    float dailyCost;
    /**
     * Games that are part of the call up
     */
    vector<Game*> games;
    /**
     * Date that the call up started
     */
    Date begginingDate;
    /**
     * Date that the call up ended
     */
    Date endDate;
    /**
     * Contains dates each player in call up got in and out of it
     */
    vector<CallUpPlayerStatistics*> playerStatistics;

public:
    /**
     * Constructs a call up
     * @param id - Call up id
     * @param dailyCost - Costs associated with insurance and accomodation in call up
     * @param games - Games that are part of the call up
     * @param playerStatistics - Contains dates each player in call up got in and out of it
     * @param begginingDate - Date that the call up started
     * @param endDate - Date that the call up ended
     */
    CallUp(int id, float dailyCost, vector<Game*> games,vector<CallUpPlayerStatistics*> playerStatistics,Date begginingDate,Date endDate);

    //GET METHODS
    /**
     * @return - playerID
     */
    int getId() const;
    /**
     * @return - costs in call up
     */
    float getDailyCost() const;
    /**
     * @return - Games that are part of the call up
     */
    vector<Game*> getGames() const;
    /**
     * @return - Date call up started
     */
    Date getBegDate() const;
    /**
     * @return - Date call up ended
     */
    Date getEndDate() const;
    /**
     * @return - Vector that ontains dates each player in call up got in and out of it
     */
    vector<CallUpPlayerStatistics*> getPlayerStatistics() const;

    //SET METHODS
    /**
     * Sets call up id
     * @param id
     */
    void setId(const int &id);
    /**
     * Sets call up daily costs
     * @param dailyCost
     */
    void setDailyCost(const float &dailyCost);
    /**
     * Sets list of games that are part of the call up
     * @param games
     */
    void setGames(const vector<Game*> &games);
    /**
     * Sets date call up started
     * @param begginingDate
     */
    void setBegDate(const Date &begginingDate);
    /**
     * Sets date call up ended
     * @param endDate
     */
    void setEndDate(const Date &endDate);
    /**
     * Sets dates that each player got in and out of the call up
     * @param playerStatistics
     */
    void setPlayerStatistics(const vector<CallUpPlayerStatistics*> playerStatistics);


    //CHANGE CALLUP
    /**
     * Adds game address to vector of games' addresses that are part of the call up
     * @param game - address of the game
     */
    void addGame(Game *game);
    /**
     * Removes game address from vector of games' addresses that are part of the call up
     * @param game - address of the game
     */
    void removeGame(Game *game);

    //UTILITIES
    /**
     * Verifies if game exists in call up
     * @param game
     * @return
     */
    bool gameExists(Game *game);
    /**
     * Verifies if player existsin call up
     * @param playerID
     * @return
     */
    bool playerExists(int playerID);

    //SHOW CALLUP
    /**
     * Display call up information on screen
     * @param out
     */
    void showCallUp(ostream &out);

    //COMPARISON OPERATOR
    /**
     * Compares call ups by id
     * @param callUp1
     * @param callUp2
     * @return
     */
    friend bool operator< (const CallUp& callUp1, const CallUp& callUp2);

    /**
     * Prints Call Up information to correspondent file
     * @param os
     */
    void printIntoFile(ostream &os) const;
};

#endif //AEDA_TEAM_MANAGER_CALLUP_H

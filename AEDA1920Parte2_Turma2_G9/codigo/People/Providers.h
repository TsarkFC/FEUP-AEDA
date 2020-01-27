//
// Created by digas on 29/12/2019.
//

#ifndef AEDA_TEAM_MANAGER_PROVIDERS_H
#define AEDA_TEAM_MANAGER_PROVIDERS_H

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "..//Exceptions.h"
using namespace std;


class Providers {
    /**
     * Provider's name
     */
    string name;
    /**
     * Provider's reputation, has a minimum value of 0 and a maximum of 100
     */
    float reputation;
    /**
     * Vector contaning all the equipement the provider sells
     */
    vector<string> equipement;
public:
    //CONSTRUCTORS
    /**
     * Creates a new Provider
     * @param name
     * @param reputation
     * @param equipement
     */
    Providers(string name, float reputation, vector<string> equipement);

    //GET METHODS
    /**
     * Gets the name of the provider
     * @return - string -> name of the provider
     */
    string getName() const;
    /**
     * Gets the reputation of the provider
     * @return - float -> reputation of the provider
     */
    float getReputation() const;
    /**
     * Gets all the equipement a provider sells in a vector of strings
     * @return - vector<string> -> all the equipement the provider sells
     */
    vector<string> getEquipement() const;

    //SET METHODS
    /**
     * Sets a new name for the provider
     * @param name
     */
    void setName(string name);
    /**
     * Sets a new reputation value for the provider
     * @param reputation
     */
    void setReputation(float reputation);
    /**
     * Sets a new list of equipement that the provider sells
     * @param equipement
     */
    void setEquipement(vector<string> equipement);

    /**
     * Defines the criteria of comparison between two providers
     * One provider is "smaller" if has lower reputation
     * @param p1 - provider to be compared with
     * @return boolean variable indicating if provider has higher or lower precedence
     */
    bool operator< (Providers p1) const;
};


#endif //AEDA_TEAM_MANAGER_PROVIDERS_H

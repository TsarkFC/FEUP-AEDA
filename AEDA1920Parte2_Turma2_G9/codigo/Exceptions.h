//
// Created by tiago on 07/11/2019.
//

#ifndef AEDA_TEAM_MANAGER_EXCEPTIONS_H
#define AEDA_TEAM_MANAGER_EXCEPTIONS_H

#include <string>
#include "Game.h"

using namespace std;

class InexistentId {
public:
    /**
     * Inexistant ID
     */
    int id;
    /**
     * Constructs object to be thrown when user inserts inexistent id
     * @param i
     */
    InexistentId(int i) {id = i;}
};

class InvalidFloat{};

class InvalidMonth {
public:
    /**
     * Invalid month
     */
    int month;
    /**
     * Constructs object to be thrown when user inserts invalid number for month
     * @param month
     */
    InvalidMonth(int month) {this->month = month;}
};

class PlayerExistsCallUp{
public:
    /**
     * Id of the existant player
     */
    int id;
    /**
     * Constructs object to be thrown when user tries to add player to call up that already exists
     * @param id
     */
    PlayerExistsCallUp(int id) {this->id = id;}
};

class PlayerDontExistsCallUp{
public:
    /**
     * Id of the non existant player
     */
    int id;
    /**
     * Constructs object to be thrown when user tries to access a player that does not exist in call up
     * @param id
     */
    PlayerDontExistsCallUp(int id) {this->id = id;}
};

class GameExistsCallUp{
public:
    /**
     * Game address that exists in call up
     */
    Game *game;
    /**
     * Constructs object to be thrown when user tries to add a game that does already exist in call up
     * @param game
     */
    GameExistsCallUp(Game *game) {this->game = game;}
};

class GameDontExistsCallUp{
public:
    /**
     * Game address that does not exist in call up
     */
    Game *game;
    /**
     * Constructs object to be thrown when user tries to access a game that does not exist in call up
     * @param game
     */
    GameDontExistsCallUp(Game *game) {this->game = game;}
};

class EquipementDontExist{
public:
    /**
     * Equipement name that does not exist
     */
    string equipement;

    /**
     * Constructs object to be thrown when user tries to access equipement that no provider has
     * @param equipement
     */
    EquipementDontExist(string equipement) {this->equipement = equipement;}
};

#endif //AEDA_TEAM_MANAGER_EXCEPTIONS_H

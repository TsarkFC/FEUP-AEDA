//
// Created by tiago on 22/10/2019.
//

#include "CallUpPlayerStatistics.h"

CallUpPlayerStatistics::CallUpPlayerStatistics(int playerID, Date begginingDate, Date endDate) {
    this->playerID = playerID;
    this->begginingDate = begginingDate;
    this->endDate = endDate;
}

//GET METHODS
Date CallUpPlayerStatistics::getEndDate() const {
    return endDate;
}
Date CallUpPlayerStatistics::getBegDate() const {
    return begginingDate;
}
int CallUpPlayerStatistics::getPlayerID() const {
    return playerID;
}

//SET METHODS
void CallUpPlayerStatistics::setEndDate(const Date &endDate) {
    this->endDate = endDate;
}
void CallUpPlayerStatistics::setBegDate(const Date &begginingDate) {
    this->begginingDate = begginingDate;
}
void CallUpPlayerStatistics::setPlayerID(const int &playerID) {
    this->playerID = playerID;
}


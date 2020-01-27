//
// Created by tiago on 19/10/2019.
//

#include "PlayerGameStatistics.h"

PlayerGameStatistics::PlayerGameStatistics(int playerID, int numberOfGoals, int minutesPlayed, int kilometers, int numberOfPasses, int numberOfYellowCards, int numberOfRedCards):id(lastId++){
    this->numberOfGoals=numberOfGoals;
    this->minutesPlayed=minutesPlayed;
    this->kilometers=kilometers;
    this->playerID = playerID;
    this->numberOfRedCards = numberOfRedCards;
    this->numberOfYellowCards = numberOfYellowCards;
    this->numberOfPasses = numberOfPasses;
}

PlayerGameStatistics::PlayerGameStatistics(int playerID):id(lastId++) {

    this->playerID = playerID;
    this->numberOfGoals = 0;
    this->minutesPlayed = 0;
    this->kilometers = 0;
    this->numberOfPasses = 0;
    this->numberOfYellowCards = 0;
    this->numberOfRedCards = 0;
}
PlayerGameStatistics::PlayerGameStatistics():id(lastId++) {
    this->playerID = 0;
    this->numberOfGoals = 0;
    this->minutesPlayed = 0;
    this->kilometers = 0;
    this->numberOfPasses = 0;
    this->numberOfYellowCards = 0;
    this->numberOfRedCards = 0;
}

int PlayerGameStatistics::getPlayerID() const {
    return playerID;
}

int PlayerGameStatistics::getId() const {
    return id;
}
void PlayerGameStatistics::setPlayerID(int player) {
    this->playerID = player;
}

int PlayerGameStatistics::getNumberOfGoals() const {
    return numberOfGoals;
}

void PlayerGameStatistics::setNumberOfGoals(int numberOfGoals) {
    if (numberOfGoals < 0) throw NegativeParameter(numberOfGoals);
    PlayerGameStatistics::numberOfGoals = numberOfGoals;
}

int PlayerGameStatistics::getMinutesPlayed() const {
    return minutesPlayed;
}

void PlayerGameStatistics::setMinutesPlayed(int minutesPlayed) {
    if (minutesPlayed <= 0 || minutesPlayed > 90) throw InvalidMinutes(minutesPlayed);
    PlayerGameStatistics::minutesPlayed = minutesPlayed;
}

int PlayerGameStatistics::getKilometers() const {
    return kilometers;
}

void PlayerGameStatistics::setKilometers(int kilometers) {
    if (kilometers < 0) throw NegativeParameter(kilometers);
    PlayerGameStatistics::kilometers = kilometers;
}

int PlayerGameStatistics::getNumberOfPasses() const {
    return numberOfPasses;
}

void PlayerGameStatistics::setNumberOfPasses(int numberOfPasses) {
    if (numberOfPasses < 0) throw NegativeParameter(numberOfPasses);
    PlayerGameStatistics::numberOfPasses = numberOfPasses;
}

int PlayerGameStatistics::getNumberOfYellowCards() const {
    return numberOfYellowCards;
}

void PlayerGameStatistics::setNumberOfYellowCards(int numberOfYellowCards) {
    if (numberOfYellowCards > 2 || numberOfYellowCards < 0) throw InvalidYellowCard(numberOfYellowCards);
    PlayerGameStatistics::numberOfYellowCards = numberOfYellowCards;
}

int PlayerGameStatistics::getNumberOfRedCards() const {
    return numberOfRedCards;
}

void PlayerGameStatistics::setNumberOfRedCards(int numberOfRedCards) {
    if (numberOfYellowCards == 2 && numberOfRedCards != 1) throw InvalidRedCard(numberOfRedCards);
    else if (numberOfRedCards < 0 || numberOfRedCards > 1) throw InvalidRedCard(numberOfRedCards);
    PlayerGameStatistics::numberOfRedCards = numberOfRedCards;
}

void PlayerGameStatistics::print(ostream &os) {
    os <<  left << setw(11)  << setfill(' ') << playerID << "│ ";
    os <<  left << setw(15) << setfill(' ') << numberOfGoals << "│ ";
    os <<  left << setw(16) << setfill(' ') <<  minutesPlayed << "│ ";
    os <<  left << setw(12) << setfill(' ') << kilometers << "│ "  ;
    os <<  left << setw(18) << setfill(' ') << numberOfPasses << "│ "  ;
    os <<  left << setw(14) << setfill(' ') << numberOfYellowCards << "│ "  ;
    os <<  left << setw(11) << setfill(' ') << numberOfRedCards << "│ "  ;
    os << endl;
}

int PlayerGameStatistics::lastId = 1;

//PRINTS STATISTICS TO FILE
void PlayerGameStatistics::printIntoFile(ostream &os) const {
    os << playerID << endl;
    os << numberOfGoals << endl;
    os << minutesPlayed << endl;
    os << kilometers << endl;
    os << numberOfPasses << endl;
    os << numberOfYellowCards << endl;
    os << numberOfRedCards << endl;
}
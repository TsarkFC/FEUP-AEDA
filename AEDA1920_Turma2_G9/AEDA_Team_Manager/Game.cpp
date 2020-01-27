//
// Created by tiago on 09/10/2019.
//

#include "Game.h"

Game::Game(string game_title, string city, string country, string stadium, vector<PlayerGameStatistics> playerStatistics, vector<string> referees, vector<FootballPlayer *> nationalP, vector<string> enemyP):id(lastID++) {
    this->game_title = game_title;
    this->city =city;
    this->country = country;
    this->stadium=stadium;
    this->playerStatistics=playerStatistics;
    this->referees=referees;
    this->nationalPlayers = nationalP;
    this->enemyPlayers = enemyP;

}

Game::Game():id(lastID++){}


ostream& operator<<(ostream &out, const Game& game) {
    out << "Location: " << game.stadium << ", " << game.city << ", " << game.country << endl << endl;
    return out;
}

/*****************************************************
 *******************GET FUNCTIONS*********************
 *****************************************************/
string Game::getGameTitle() const {
    return game_title;
}
int Game::getId() const {
    return this->id;
}

string Game::getCountry() const {
    return country;
}
string Game::getCity() const {
    return city;
}
string Game::getStadium() const {
    return stadium;
}

vector<FootballPlayer *> Game::getNationalPlayers() const {
    return this->nationalPlayers;
}

vector<string> Game::getEnemyPlayers() const {
    return this->enemyPlayers;
}

vector<PlayerGameStatistics> Game::getPlayerStatistics() const {
    return this->playerStatistics;
}

vector<string> Game::getReferees() {
    return this->referees;
}

/*****************************************************
 *******************SET FUNCTIONS*********************
 *****************************************************/
void Game::setGameTitle(string game_title) {
    this->game_title = game_title;
}
void Game::setPlayerStatistics(vector<PlayerGameStatistics> statistics){
    this->playerStatistics = statistics;
}

void Game::setReferees(vector<string> refs) {
    this->referees = refs;
}

void Game::setCity(string city) {
    this->city = city;
}
void Game::setStadium(string stadium) {
    this->stadium = stadium;
}
void Game::setCountry(string country) {
    this->country = country;
}

void Game::setNationalPlayers(vector<FootballPlayer *> vec) {
    this->nationalPlayers = vec;
}
void Game::setEnemyPlayers(vector<string> vec){
    this->enemyPlayers = vec;
}


/*****************************************************
 ******************AUX FUNCTIONS*********************
 *****************************************************/

void Game::addNationalPlayer(FootballPlayer *player, PlayerGameStatistics stats) {
    this->nationalPlayers.push_back(player);
    this->playerStatistics.push_back(stats);
}

void Game::removeNationalPlayer(FootballPlayer *player) {

    vector<FootballPlayer *>::iterator it;

    for(it = nationalPlayers.begin(); it < nationalPlayers.end(); it++){
        if((*it)->getId() == (*player).getId()){ nationalPlayers.erase(it); }
        return;
    }
}

PlayerGameStatistics Game::getSpecificPlayerStatistics(FootballPlayer *player) {

    for(PlayerGameStatistics p : playerStatistics){
        if(p.getPlayerID() == player->getId()){
            return p;
        }
    }
    return playerStatistics[0];
}

void Game::printIntoFile(ostream &os) const{
    os << city << endl;
    os << country << endl;
    os << stadium << endl;
    os << game_title << endl;

    for(int i = 0; i < playerStatistics.size(); i++){
        if(i == playerStatistics.size() - 1){
            os << playerStatistics[i].getId() << endl;
        }
        else {
            os << playerStatistics[i].getId() << ", ";
        }
    }

    for(int i = 0; i < nationalPlayers.size(); i++){
        if(i == nationalPlayers.size() - 1){
            os << nationalPlayers[i]->getId() << endl;
        }
        else {
            os << nationalPlayers[i]->getId() << ", ";
        }
    }

    for(int i = 0; i < enemyPlayers.size(); i++){
        if(i == enemyPlayers.size() - 1){
            os << enemyPlayers[i] << endl;
        }
        else {
            os << enemyPlayers[i] << ", ";
        }
    }

    for(int i = 0; i < referees.size(); i++){
        if(i == referees.size() - 1){
            os << referees[i] << endl;
        }
        else {
            os << referees[i] << ", ";
        }
    }

}


void Game::print(ostream &out){
    out <<  left << setw(4)  << setfill(' ') << this->id << "│  ";
    out <<  left << setw(20) << setfill(' ') << this->city  << "│ ";
    out <<  left << setw(20) << setfill(' ') <<  this->country << "│ ";
    out <<  left << setw(30) << setfill(' ') << this->stadium << "│ "  ;
    out << left << setw(20) << setfill(' ') << this->game_title << "│ " ;
    out << endl;
}

int Game::lastID = 1;

/*****************************************************
 ******************ADD FUNCTIONS*********************
 *****************************************************/

void Game::addEnemyPlayer(string player)  {
    enemyPlayers.push_back(player);
}

int Game::addReferee(string referee) {
    if(referees.size() == 5){
        cout << "You can't add more referees. Please delete one before adding.";
        return 1;
    }
    else {
        referees.push_back(referee);
    }
    return 0;
}

/*****************************************************
 ****************REMOVE FUNCTIONS*********************
 *****************************************************/

void Game::removeEnemyPlayer(string player) {
    vector<string>::const_iterator it;

    for(it = enemyPlayers.begin(); it < enemyPlayers.end(); it++){
        if((*it) == player){
            enemyPlayers.erase(it);
            return;
        }
    }
}

void Game::removeReferee(string referee){
    vector<string>::const_iterator it;

    for(it = referees.begin(); it < referees.end(); it++){
        if((*it) == referee){
            referees.erase(it);
            return;
        }
    }
}
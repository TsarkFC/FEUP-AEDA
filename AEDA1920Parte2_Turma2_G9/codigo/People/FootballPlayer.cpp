//
// Created by tiago on 09/10/2019.
//


#include "FootballPlayer.h"

//Constructs a Football player given all the information
FootballPlayer::FootballPlayer(string name, Date birthdayDate,float salary, string position, string club, const float weight, const float height, float pass_value,bool injury):Person(name,birthdayDate, salary) {

    this->club = club;
    this->position = position;
    this->weight= weight;
    this->height = height;
    this->pass_value = pass_value;
    this->injury= injury;
}

//Constructs a default FootballPlayer
FootballPlayer::FootballPlayer():Person() {
    this->position = "";
    this->club = "";
    this->weight= 0;
    this->height = 0;
    this->pass_value = 0.0;
    this->injury= false;

}

//Returns the type of the player
string FootballPlayer::type() const {
    return "Football Player";
}

//Prints the Football player in a formatted table way
void FootballPlayer::print(ostream &out) const {

    Person::print(cout);
    out <<  left << setw(20)  << setfill(' ') << position << "│ ";
    out <<  left << setw(9) << setfill(' ') << club  << " │";
    out <<  left << setw(5) << setfill(' ')<< fixed  << setprecision(2)  <<  weight<< " │";
    out <<  left << setw(6) << setfill(' ') << fixed  << setprecision(2) <<  height<< " │";
    out <<  left << setw(5) << setfill(' ') << fixed  << setprecision(2) << pass_value<< " │";
    if(injury) out <<  left << setw(5) << setfill(' ') << "Injured"<< " │" << endl;
    else out <<  left << setw(5) << setfill(' ') << "Healthy"<< " │" << endl;
}

//Prints a person in the file format
void FootballPlayer::printToFile(ostream &os) const {
    Person::printToFile(os);
    os << position << endl;
    os << club << endl;
    os << fixed << setprecision(2) <<  weight << endl;
    os << fixed << setprecision(2) << height << endl;
    os << fixed << setprecision(2) << pass_value << endl;
    if (injury) os << "Injured";
    else os << "Healthy";
    os << endl << "::::::::::";
}

//Gets the position of the player
const string &FootballPlayer::getPosition() const {
    return position;
}

//Sets the position of the player
void FootballPlayer::setPosition(const string &position) {
    FootballPlayer::position = position;
}
//Gets the club of the player
const string &FootballPlayer::getClub() const {
    return club;
}

//Sets the club of the player
void FootballPlayer::setClub(const string &club) {
    FootballPlayer::club = club;
}

//Gets the weight of the player
float FootballPlayer::getWeight() const {
    return weight;
}

//Sets the weight of the player
void FootballPlayer::setWeight(float weight) {
    FootballPlayer::weight = weight;
}

//Gets the height of the player
float FootballPlayer::getHeight() const {
    return height;
}

//Sets the height of the player
void FootballPlayer::setHeight(float height) {
    FootballPlayer::height = height;
}

//Gets the pass value
float FootballPlayer::getPassValue() const {
    return pass_value;
}
//sets the pass value
void FootballPlayer::setPassValue(float passValue) {
    pass_value = passValue;
}

//Returns true if the player is injured
bool FootballPlayer::isInjury() const {
    return injury;
}

//sets injutry
void FootballPlayer::setInjury(bool injury) {
    FootballPlayer::injury = injury;
}



//Modifies a player given a new football player
void FootballPlayer::modify(Person *newPerson){
    FootballPlayer *player = (FootballPlayer*) newPerson;
    Person::modify(newPerson);
    position = player->getPosition();
    club = player->getClub();
    weight= player->getWeight();
    height = player->getHeight();
    pass_value = player->getPassValue();
    injury  = player->isInjury();
}

//Reads a football player form a ifstrem
void FootballPlayer::read(ifstream *file) {
    Person::read(file);
    string text;
    getline(*file,text);
    position = text;
    getline(*file,text);
    club = text;
    getline(*file,text);
    weight = stof(text);
    getline(*file,text);
    height = stof(text);
    getline(*file,text);
    pass_value = stof(text);
    getline(*file,text);
    if(text == "Healthy") injury= false;
    if(text == "Injured") injury= true;
}
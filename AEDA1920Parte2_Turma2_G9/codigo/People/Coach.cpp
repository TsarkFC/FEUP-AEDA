//
// Created by tiago on 22/12/2019.
//

#include "Coach.h"
#include <sstream>

Coach::Coach(const string &name, const Date &birthdayDate, float salary, int titlesWon,const vector<string> &coachedTeams, const bool &isCurrentCoach)
            : Person(name, birthdayDate, salary), titlesWon(titlesWon), coachedTeams(coachedTeams), isCurrentCoach(isCurrentCoach) {

}

Coach::Coach():Person() {
    this->titlesWon= 0;
    this->isCurrentCoach= false;
}

int Coach::getTitlesWon() const {
    return titlesWon;
}

int Coach::isActualCoach() const {
    return isCurrentCoach;
}

void Coach::setIfCurrentCoach(const bool &isCurrentCoach){
    this->isCurrentCoach = isCurrentCoach;
}

void Coach::setTitlesWon(int titlesWon) {
    Coach::titlesWon = titlesWon;
}

const vector<string> &Coach::getCoachedTeams() const {
    return coachedTeams;
}

void Coach::setCoachedTeams(const vector<string> &coachedTeams) {
    Coach::coachedTeams = coachedTeams;
}

string Coach::type() const {
    return "Coach";
}

void Coach::modify(Person *newPerson){
    Coach *coach = (Coach*) newPerson;
    Person::modify(newPerson);
    titlesWon = coach->getTitlesWon();
    coachedTeams = coach->getCoachedTeams();

}

void Coach::read(ifstream *file) {
    Person::read(file);
    string text;
    getline(*file,text);
    titlesWon = stoi(text);
    getline(*file,text);
    coachedTeams = separateCharacterStr(text,',');
}


void Coach::print(ostream &out) const {
    Person::print(cout);
    string cc;
    if (isWorking){
        cc = "Is Current Coach";
    }else{
        cc = "Old Coach";
    }

    out <<  left << setw(20) << cc << "│  ";
    out <<  left << setw(9) << to_string(titlesWon) << " │ " << endl;

}

void Coach::printCoach(ostream &out) const {

    out << "ID: " << id << endl;
    out << "Name " << name << endl;
    out << "Birthday Date: " << birthdayDate.toString() << endl;
    out << "Salary: " << salary << endl;
    out << "Titles won: " << titlesWon << endl;
    if(isWorking) out << "Position: Current Coach" << endl;
    if(!isWorking) out << "Position: Old Coach" << endl;
    out << "Teams Trained: " << endl;
    for (int i = 0; i < coachedTeams.size(); ++i) {
        out << "        " << coachedTeams[i] << endl;
    }

}


bool Coach::operator<(const Coach* &coach) const {
    if(titlesWon < coach->titlesWon) return true;
    if(titlesWon == coach->titlesWon){
        return name < coach->name;
    }
    return false;
}

bool Coach::operator<(const Coach &coach) const {
    if(titlesWon < coach.titlesWon) return true;
    if(titlesWon == coach.titlesWon){
        return name < coach.name;
    }
    return false;
}

void Coach::printToFile(ostream &os) const {
    Person::printToFile(os);
    os << titlesWon << endl;
    os << coachedTeams[0];
    for (int i = 1; i < coachedTeams.size() ; ++i) {
        os << "," << coachedTeams[i];
    }
    os << endl << "::::::::::";
}

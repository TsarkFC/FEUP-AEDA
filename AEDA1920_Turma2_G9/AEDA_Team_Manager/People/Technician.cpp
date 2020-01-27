//
// Created by tiago on 09/10/2019.
//

#include "Technician.h"


//Constructs a default technician
Technician::Technician(): Person(){
    this->name = "";
    this->birthdayDate = Date();

}

//Constructs a technician given all the informations
Technician::Technician(string name, Date birthday, float salary, string role):Person(name,birthday,salary){
    this->role = role;
}

//Gets the role of the tecbnician
const string Technician::getRole() const {
    return role;
}

//sets the role of the technician
void Technician::setRole(const string &role) {
    Technician::role = role;
}

//Prints the technician in a fornatted table way
void Technician::print(ostream &out) const {
    Person::print(cout);

    out <<  left << setw(20) << role << "│  ";
    out <<  left << setw(9) << setfill(' ') << "-------"  << "│ ";
    out <<  left << setw(5) << setfill(' ')<<  "---" << "│ ";
    out <<  left << setw(5) << setfill(' ') << "-----" << " │ ";
    out <<  left << setw(5) << setfill(' ') << "----"<< "│ ";
    out <<  left << setw(5) << setfill(' ') << "----"<< "  │" << endl;
}

//Outputs the technician to a ostream variable in the file format
void Technician::printToFile(ostream &out) const {
    Person::printToFile(out);
    out << role << endl;
    out <<  "::::::::::";
}
//Returns type of the person
string Technician::type() const {
    return "Technician";

}

//Reads a technician from a ifstream variable
void Technician::read(ifstream *file) {
    Person::read(file);
    string text;
    getline(*file,text);
    role = text;

}
//
// Created by tiago on 19/10/2019.
//


#include "Person.h"

using namespace std;

//Constructor of people given all the information, generates id automatically
Person::Person(string name, Date birthdayDate, float salary):id(lastId++){
    this->birthdayDate = birthdayDate;
    this->name = name;
    this->salary = salary;
}

//Generate a default person, and an id
Person::Person(): id(lastId++){
    this->name = "";
    this->birthdayDate = Date();
    this->salary = 0;

}

//Gets the id
int Person::getId() const{ return id;}

//Gets the name
string Person::getName() const{ return name;}

//Gets Person's birthday date
Date Person::getBirthday() const { return birthdayDate;}

//Gets salary
float Person::getSalary() const { return salary;}


//Sets Person's name
void Person::setName(string name) { this->name = name;}

//set person's birthday date'
void Person::setBirthday(Date birthday){ this->birthdayDate = birthday;}

//sets salary of the persion
void Person::setSalary(float salary) { Person::salary = salary;
}

//Makes a person with a smaller id smaller than the other person
bool Person::operator<(const Person &person) const {
    return id < person.id;
}

//Makes a pointer of a person smaller than another if its id is smaller
bool Person::operator<(const Person* &person) const {
    return id < person->id;
}


//Makes a person with a bigger id bigger than the other person
bool Person::operator>(const Person &person) const {
    return id > person.id;
}
//Makes two people equal if they share the same id
bool Person::operator==(const Person &person) const {
    return id == person.id;
}

//Makes two people different if thei share the same id
bool Person::operator!=(const Person &person) const {
    return !(person == *this);
}

//Returns the type of the person
string Person::type() const{
    return "Person";
}

//Prints person to the screen
void Person::print(ostream& out) const{

    out <<  left << setw(4)  << setfill(' ') << id << "│  ";
    out <<  left << setw(20) << setfill(' ') << name  << "│ ";
    out <<  left << setw(11) << setfill(' ') <<  birthdayDate.toString()<< "│ ";
    out <<  left << setw(9) << setfill(' ') << salary<< "│  "  ;
}

//Prints infotmation of the person in the file format
void Person::printToFile(ostream &os) const {
    os << type() << endl;
    os << id << endl;
    os << name << endl;
    os << birthdayDate <<endl;
    os  << fixed << setprecision(2) << salary << endl;
}

//Reads all the people from it's file and adds it to the database
void Person::read(ifstream *file) {
    string text;
    Date birthday = Date();

    getline(*file,text);
    try {id = stoi(text);}
    catch (std::invalid_argument ia){ cerr << "Invalid ID " << text << " for: " << name; throw;}

    getline(*file,text);
    name = text;

    getline(*file,text);
    try {birthdayDate = birthday.dateTextConverter(text);}
    catch (InvalidDate) {cerr << "Invalid date " << text << " for: " << name;}


    getline(*file,text);
    try {salary = stof(text);}
    catch (std::invalid_argument ia){ cerr << "Invalid salary " << text << " for: " << name; throw;}

}



//Modifies a Persion given a new person
void Person::modify(Person *newPerson){
    name = newPerson->getName();
    salary = newPerson->getSalary();
    birthdayDate= newPerson->getBirthday();
}

//Sets the first id to one
int Person::lastId = 1;


//Print a person in a formatted way
ostream &operator<<(ostream &os, const Person *person){
    person->print(os);
    return os;
}







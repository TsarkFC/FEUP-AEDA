#include "Date.h"
#include "Utilities.h"


Date::Date() {
}

Date::Date(unsigned short day, unsigned short month, unsigned year){
    this->day = day;
    this->month = month;
    this->year = year;
    if(!isValid()) throw InvalidDate(day,month,year);
}

Date::Date(string date){
    this->day = stoi(date.substr(0, 2));
    this->month = stoi(date.substr(3, 2));
    this->year = stoi(date.substr(6, 4));
    if(!isValid()) throw InvalidDate(day,month,year);
}

//GET methods

unsigned short Date::getDay() const {return day;}
unsigned short Date::getMonth() const{return month;}
unsigned Date::getYear() const{return year;}


//SET methods

void Date::setDay(unsigned short day){this -> day = day;}
void Date::setMonth(unsigned short month){this -> month = month;}
void Date::setYear(unsigned year){this -> year = year;}

//Other methods

//Converts a date to a string in the format "day/month/year"
string Date::toString() const {
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year) ;
}

//Verifies if Date is valid
bool Date::isValid() {
    if (!((day <= daysInMonth(month, year)) && (month >= 1) && (month <= 12) && (day > 0))) throw InvalidDate(day,month,year);
    return true;
}

//Alternative to the == operator, returns true if 2 dates are equal
bool Date::isEqualTo(const Date &d) {
    return (d.year == year && d.month == month && d.day == day);
}

//Verifies if a date comes after another
bool Date::isAfter(const Date &d) {
    if (d.year > year)
        return false;
    else if (d.year == year && d.month > month)
        return false;
    else if (d.year == year && d.month == month && d.day > day)
        return false;
    else
        return true;
}

//Prints date, alternative to << operator
void Date::showDate() const {
    cout << day << "/" << month << "/" << year << endl;
}


bool operator==(const Date& date1, const Date& date2) {
    return date1.day == date2.day && date1.month == date2.month && date1.year == date2.year;
}

bool operator<=(const Date& date1, const Date& date2){
    if (date1.dateToDays() <= date2.dateToDays()) return true;
    else return false;
}
bool operator>=(const Date& date1, const Date& date2){
    if (date1.dateToDays() >= date2.dateToDays()) return true;
    else return false;
}


ostream& operator<<(ostream	&out, const Date &date){
    out << to_string(date.day) << "/" << to_string(date.month) << "/" << to_string(date.year);
    return out;
}


//STATIC METHODS

// Returns the days in a given month of a given year
int Date::daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if (isLeapYear(year)) return 29;
            else return 28;
        default:
            return -1;
    }
}

//Returns true if the given year is a leap year
bool Date::isLeapYear(int year) {
    // Divisible by 4 but not by 100, or divisible by 400

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
    else
        return false;
}

//Copies a date to another date object
void Date::copyDate(Date &copy, Date date) {
    copy.year = date.year;
    copy.month = date.month;
    copy.day = date.day;
}

//Converts a date in a string to a date of Date Class
Date Date::dateTextConverter(string dateText) {
    Date date;
    vector<int> dateVector;
    dateVector = separateCharacterInt(dateText, '/');
    date.day = dateVector[0];
    date.month = dateVector[1];
    date.year = dateVector[2];

    if(!date.isValid()) throw ExceptionDate(dateText);

    return date;
}

//Converts a date in a string to a date of Date Class from the file
Date Date::dateTextConverterFile(string dateText) {
    Date date;
    vector<int> dateVector;
    dateVector = separateCharacterInt(dateText, '/');
    date.year = dateVector[0];
    date.month = dateVector[1];
    date.day = dateVector[2];
    return date;
}

//Verifies if a date in a string is valid
bool Date::validDateText(string dateText)
{
    vector<string> dateVector;
    dateVector = separateCharacterStr(dateText, '/');
    if (dateVector.size() != 3) { return false; }
    for (int i = 0; i < dateVector.size(); i++) {
        if (!stringIsNumber(dateVector[i])) { return false; }
    }
    if (stoi(dateVector[0]) < 1 || stoi(dateVector[0]) > 31) { return false; }
    if (stoi(dateVector[1]) < 1 || stoi(dateVector[1]) > 12) { return false; }
    if (stoi(dateVector[2]) < 1000 || dateVector[2].size() != 4) { return false; }
    if (stoi(dateVector[1]) == 2) {
        if (Date::isLeapYear(stoi(dateVector[2])))
        {
            if (stoi(dateVector[0]) > 29) { return false; }
        }
        else if (stoi(dateVector[0]) >= 29) { return false; }
    }
    return true;
}

//Converts date to days
int Date::dateToDays() const{
    return day + daysInMonth(month, year)*month + year*365;
}
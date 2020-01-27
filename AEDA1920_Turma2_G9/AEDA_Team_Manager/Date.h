//
// Created by digas on 17/10/2019.
//


#pragma once

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Date{
private:
    /**
     * Date's day
     */
    unsigned short day;
    /**
     * Date's month
     */
    unsigned short month;
    /**
     * Date's year
     */
    unsigned year;

public:
    /**
     * Empty class constructor
     */
    Date();
    /**
     * Creates date object from string variable
     * @param date - string variable
     */
    Date(string  date); // Assuming "dd/mm/yyyy"
    /**
     * Creates date object
     * @param day
     * @param month
     * @param year
     */
    Date(unsigned short day, unsigned short month, unsigned year);


    // GET methods
    /**
     * Gets date's day
     * @return date day
     */
    unsigned short getDay() const;
    /**
     * Gets date's month
     * @return date month
     */
    unsigned short getMonth() const;
    /**
     * Gets date's year
     * @return date year
     */
    unsigned getYear() const;


    // SET methods
    /**
     * Sets date's day equal to parameter value
     * @param day
     */
    void setDay(unsigned short day);
    /**
     * Sets date's month equal to parameter value
     * @param day
     */
    void setMonth(unsigned short month);
    /**
     * Sets date's year equal to parameter value
     * @param day
     */
    void setYear(unsigned year);

    // Other methods

    /**Converts a Date to a string
    @param - /
    @return string - the date in a string
    */
    string toString() const;

    /**Verifies if a Date is valid (months have 1 - 31 days, etc.)
    @param - /
    @return bool - true if date is valid
    */
    bool isValid();

    /**Verifies if a Date is equal to another, alternative to == operator
    @param - date of Date Class
    @return bool - true if dates are equal
    */
    bool isEqualTo(const Date &d);

    /**Verifies if a Date comes after another
    @param - date of Date Class
    @return bool - true if date is after the date specified in parenthesis
    */
    bool isAfter(const Date &d);

    /**Prints date to the screen, formatted, as an alternative to the << operator
    @param - date of Date Class
    @return bool - true if date is after the date specified in parenthesis
    */
    void showDate() const;

    /**
     * Checks if two dates are equal
     * @param date1 - first date
     * @param date2 - second date
     * @return true if dates are equal, false otherwise
     */
    friend bool operator==(const Date& date1, const Date& date2);
    /**
     * Prints date on screen
     * @param out
     * @param date - date to be printed
     * @return reference to ostream variable
     */
    friend ostream& operator<<(ostream& out, const Date& date);
    /**
     * Checks if first date is smaller or equal to second
     * @param date1 - first date
     * @param date2 - second date
     * @return bool - true if first date is smaller or equal, false otherwise
     */
    friend bool operator<=(const Date& date1, const Date& date2);
    /**
     * Checks if first date is bigger or equal to second
     * @param date1 - first date
     * @param date2 - second date
     * @return bool - true if first date is bigger or equal, false otherwise
     */
    friend bool operator>=(const Date& date1, const Date& date2);

    //Static Methods

    /**Returns an integer that represents the number of days in a given month of a given year
    @param - month - a month represented by it's numerical value
    @param - year - a year
    @return int - number of days in the given date
    */
    static int daysInMonth(int month, int year);

    /**Returns true if the given year is a leap year
    @param - year - a year to be verified
    @return bool - true if leap year, false otherwise
    */
    static bool isLeapYear(int year);

    /**Copies a date to another date object, alternative to the = operator
    @param - copy - date of Date Class to be copied
    @param - date - date of Date Class to copy
    @return void
    */
    static void copyDate(Date &copy, Date date);

    /**Converts date in a string to a date of a Date Class
    @param - dateText - date as a string to be converted
    @return Date - Date Class
    */
    static Date dateTextConverter(string dateText);

    /**Converts date in a string to a date of a Date Class from a file
    @param - dateText - date as a string to be converted
    @return Date - Date Class
    */
    static Date dateTextConverterFile(string dateText);

    /**Verifies if a date in a string is valid
    @param - dateText - date as a string to be verified
    @return bool - true if date is valid (ex. days go from 1-31, year > 1000 not accepted, etc.)
    */
    static bool validDateText(string dateText);

    /**
     * Converts date value to days
     * @return int - date value in days
     */
    int dateToDays() const;

};

class ExceptionDate{
public:
    /**
     * Invalid string date
     */
    string date;
    /**
     * Constructs object to be thrown when date represented by a string is invalid
     * @param date - invalid string date
     */
    ExceptionDate(string date){this->date = date;};
};

class InvalidDate{
public:
    /**
     * Ivalid parameters of date
     */
    int day, month, year;
    /**
     * Constructs object to be thrown when date does not correspond to a possible value
     * @param day
     * @param month
     * @param year
     */
    InvalidDate(int day, int month, int year){
        this->day = day;
        this->month = month;
        this->year = year;
    }
};


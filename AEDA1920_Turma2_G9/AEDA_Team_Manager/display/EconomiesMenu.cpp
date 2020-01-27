//
// Created by digas on 09/11/2019.
//


#include <iomanip>
#include "Menu.h"


void Menu::runEconomiesMenu() {
    int option;

    while (true){

        menuSeparator();
        cout << "Welcome to the Economies Menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "Costs associated with one player.                                  [1]" << endl;
        cout << "Costs associated with full team.                                   [2]" << endl;
        cout << "Costs associated with team and staff.                              [3]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 3);
        menuSeparator();

        if (option == 0) break;
        if (option == 1) {playerMenu();}
        if (option == 2) {teamMenu();}
        if (option == 3) {staffMenu();}
    }
}

void Menu::playerMenu() {
    int option;

    while(true){
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "Costs associated with one player in a determined month.            [1]" << endl;
        cout << "Costs associated with one player between two dates.                [2]" << endl;
        cout << "Costs associated with one player in determined call up.            [3]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 3);
        menuSeparator();

        if (option == 0) { break; }
        else if (option == 1) {playerMonthMenu();}
        else if (option == 2) {playerTimeMenu();}
        else if (option == 3) {playerCallUp();}
    }
}

void Menu::playerMonthMenu(){

    int pID, option, month, year;
    menuSeparator();

    while (true){

        //GET ID OF PLAYER
        askForValidId(players);

        //GET MONTH NUMBER
        cout << "Insert the number of the month: ";
        cin >> month;

        try{
            if(month < 0 || month > 12) throw InvalidMonth(month);
        }
        catch(InvalidMonth) {
            cout << "Month number has to be between 1 and 12!" << endl;
            break;
        }

        if(cin.fail()){
            cout << "Invalid operation, MONTH is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        //GET YEAR NUMBER
        cout << "Insert the number of the year: ";
        cin >> year;

        if(cin.fail()){
            cout << "Invalid operation, MONTH is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        menuSeparator();

        //shows player so that user can confirm that it is checking the right player
        cout << "The following player has been selected:" << endl << endl;
        showSpecificPerson(cout,pID);

        cout << endl << endl;
        cout << "Go back.                                                               [0]" << endl;
        cout << "Confirm operation.                                                     [1]" << endl;
        cin >> option;

        validOption(option, 1);
        menuSeparator();

        if (option == 0) break;
        else if (option == 1) {

            cout << "The costs associated with the player with ID: " << pID << " in " << month << "/";
            cout << year << " were of " << playerCostCalculatorMonth(month, year, pID) << " euros." << endl;
            break;
        }

    }

}

void Menu::playerTimeMenu(){

    int playerID, option;
    string date1, date2;
    Date firstDate;
    Date endDate;
    menuSeparator();

    while (true){

        //GET ID OF PLAYER
        askForValidId(players);


        //GET FIRST DATE
        cout << "Insert the first date: ";
        cin >> date1;

        if (!firstDate.validDateText(date1)) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        firstDate = firstDate.dateTextConverter(date1);


        if (cin.fail()) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        //GET END DATE
        cout << "Insert the final date: ";
        cin >> date2;

        if (!endDate.validDateText(date2)) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        endDate = endDate.dateTextConverter(date2);

        if (!endDate.isAfter(firstDate)) {
            cout << "Invalid operation, final date cannot be before first date!" << endl;
            break;
        }

        if (cin.fail()) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');


        menuSeparator();

        //shows player so that user can confirm that it is checking the right player
        cout << "The following player has been selected:" << endl << endl;
        showSpecificPerson(cout,playerID);
        //players[playerID]->print(cout);
        cout << endl << endl;
        cout << "Go back.                                                               [0]" << endl;
        cout << "Confirm operation.                                                     [1]" << endl;
        cin >> option;

        validOption(option, 1);
        menuSeparator();

        if (option == 0) break;
        else if (option == 1) {

            cout << "The costs associated with the player with ID: " << playerID << " between " << date1 << " and ";
            cout << date2 << " were of " << playerCostCalculator(firstDate, endDate, playerID) << " euros." << endl;
            break;
        }

    }
}

void Menu::playerCallUp() {
    int playerID;
    int idc;
    float val = 0;
    int playerPos;
    float pass;
    int call_pos;

    while(true) {
        //GET ID OF PLAYER
        cout << "Insert the ID of the player information will be taken from: ";
        cin >> playerID;

        if (cin.fail()){
            cout << "Player ID is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        try{
            searchByID(players, playerID);
        }
        catch(InexistentId){
            cout << "There is no player with the given ID!";
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        if (cin.fail()){
            cout << "Invalid operation, ID is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');





        cout << "Insert the ID of the call up: ";
        cin >> idc;

        if (cin.fail()) {
            cout << "Invalid operation, ID is an integer number!" << endl;
            cin >> idc;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        try {
            searchCallUpByID(idc);
        }
        catch (...) {
            cout << "There are no call ups with such id (" << idc << ") !" << endl;
            menuSeparator();
            break;
        }

        playerPos = searchByID(players, playerID);
        pass = players[playerPos]->getPassValue() * 0.01;


        call_pos = searchCallStatsByID(getCallUpWithID(idc)->getPlayerStatistics(), playerID);
        Date beg = getCallUpWithID(idc)->getPlayerStatistics()[call_pos]->getBegDate();
        Date end = getCallUpWithID(idc)->getPlayerStatistics()[call_pos]->getEndDate();
        float cost = getCallUpWithID(idc)->getDailyCost();

        if (players[playerPos]->isInjury()) {
            val += pass * (end.dateToDays() - beg.dateToDays()) * 3 * cost;
        }
        else val += pass * (end.dateToDays() - beg.dateToDays()) * cost;

        cout << "Selected player: " << endl;
        tableHeaderPlayer(cout);
        players[playerPos]->print(cout);
        tableFooterPlayer(cout);
        menuSeparator();

        cout << "Selected call up: " << endl;
        headerCallUp(cout);
        getCallUpWithID(idc)->showCallUp(cout);
        cout << endl << endl;

        cout << "The costs associated with the player with ID: " << playerID << " in call up with ID: " << idc;
        cout << " were of " << val << " euros." << endl;
        break;
    }
}

void Menu::teamMenu() {
    int option;

    while(true){
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "Costs associated with full team in a determined month.             [1]" << endl;
        cout << "Costs associated with full team between two dates.                 [2]" << endl;
        cout << "Costs associated with full team in a call up                       [3]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 3);
        menuSeparator();

        if (option == 0) { break; }
        else if (option == 1) {teamMonthMenu();}
        else if (option == 2) {teamTimeMenu();}
        else if (option == 3) {teamCallUp();}
    }
}

void Menu::teamTimeMenu(){
    string date1, date2;
    Date firstDate;
    Date endDate;

    while(true) {
        menuSeparator();

        //GET FIRST DATE
        cout << "Insert the first date: ";
        cin >> date1;

        if (!firstDate.validDateText(date1)) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        firstDate = firstDate.dateTextConverter(date1);


        if (cin.fail()) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        //GET END DATE
        cout << "Insert the final date: ";
        cin >> date2;

        if (!endDate.validDateText(date2)) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        endDate = endDate.dateTextConverter(date2);

        if (!endDate.isAfter(firstDate)) {
            cout << "Invalid operation, final date cannot be before first date!" << endl;
        }

        if (cin.fail()) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        menuSeparator();

        cout << "The costs associated with the national team players between " << date1 << " and ";
        cout << date2 << " were of " << teamCostCalculator(firstDate, endDate) << " euros." << endl;
        break;
    }
}

void Menu::teamMonthMenu(){
    int option, month, year;
    menuSeparator();

    while (true) {

        //GET MONTH NUMBER
        cout << "Insert the number of the month: ";
        cin >> month;

        try {
            if (month < 0 || month > 12) throw InvalidMonth(month);
        }
        catch (InvalidMonth) {
            cout << "Month number has to be between 1 and 12!" << endl;
            break;
        }

        if (cin.fail()) {
            cout << "Invalid operation, MONTH is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        //GET YEAR NUMBER
        cout << "Insert the number of the year: ";
        cin >> year;

        if (cin.fail()) {
            cout << "Invalid operation, YEAR is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        menuSeparator();

        cout << "The costs associated with the national team players in the month " << month << ", year ";
        cout << year << " were of " << teamCostCalculatorMonth(month, year) << " euros." << endl;
        break;
    }
}

void Menu::teamCallUp() {
    float val = 0;
    int idc, playerPos;
    Date end, beg;
    float cost, pass;

    while(true) {
        cout << "Insert the ID of the call up: ";
        cin >> idc;

        if (cin.fail()) {
            cout << "Invalid operation, ID is an integer number!" << endl;
            cin >> idc;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        try {
            searchCallUpByID(idc);
        }
        catch (...) {
            cout << "There are no call ups with such id (" << idc << ") !" << endl;
            menuSeparator();
            break;
        }

        cost = getCallUpWithID(idc)->getDailyCost();
        for (auto i = 0; i < getCallUpWithID(idc)->getPlayerStatistics().size(); i++) {

            playerPos = searchByID(players, getCallUpWithID(idc)->getPlayerStatistics()[i]->getPlayerID());
            pass = players[playerPos]->getPassValue() * 0.01;

            beg = getCallUpWithID(idc)->getPlayerStatistics()[i]->getBegDate();
            end = getCallUpWithID(idc)->getPlayerStatistics()[i]->getEndDate();

            if (players[playerPos]->isInjury()) {
                val += pass * (end.dateToDays() - beg.dateToDays()) * 3 * cost;
            } else val += pass * (end.dateToDays() - beg.dateToDays()) * cost;
        }


        cout << "Selected call up: " << endl;
        headerCallUp(cout);
        getCallUpWithID(idc)->showCallUp(cout);
        cout << endl << endl;

        cout << "The costs associated with the all team in call up with ID: " << idc;
        cout << " were of " << val << " euros." << endl;
        break;
    }
}

void Menu::staffMenu() {
    int option;

    while(true){
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "Costs associated with team and staff in a determined month.        [1]" << endl;
        cout << "Costs associated with team and staff between two dates.            [2]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 2);
        menuSeparator();

        if (option == 0) { break; }
        else if (option == 1) {staffMonthMenu();}
        else if (option == 2) {staffTimeMenu();}
    }
}

void Menu::staffMonthMenu() {
    int option, month, year;
    menuSeparator();

    while (true) {

        //GET MONTH NUMBER
        cout << "Insert the number of the month: ";
        cin >> month;

        try {
            if (month < 0 || month > 12) throw InvalidMonth(month);
        }
        catch (InvalidMonth) {
            cout << "Month number has to be between 1 and 12!" << endl;
            break;
        }

        if (cin.fail()) {
            cout << "Invalid operation, MONTH is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        //GET YEAR NUMBER
        cout << "Insert the number of the year: ";
        cin >> year;

        if (cin.fail()) {
            cout << "Invalid operation, YEAR is an integer number!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        menuSeparator();

        cout << "The costs associated with the national team players and staff in the month " << month << ", year ";
        cout << year << " were of " << teamCostCalculatorMonth(month, year) + staffCostCalculatorMonth(month) << " euros." << endl;
        break;
    }
}

void Menu::staffTimeMenu() {
    string date1, date2;
    Date firstDate;
    Date endDate;

    while(true) {
        menuSeparator();

        //GET FIRST DATE
        cout << "Insert the first date: ";
        cin >> date1;

        if (!firstDate.validDateText(date1)) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        firstDate = firstDate.dateTextConverter(date1);


        if (cin.fail()) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        //GET END DATE
        cout << "Insert the final date: ";
        cin >> date2;

        if (!endDate.validDateText(date2)) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        endDate = endDate.dateTextConverter(date2);

        if (!endDate.isAfter(firstDate)) {
            cout << "Invalid operation, final date cannot be before first date!" << endl;
        }

        if (cin.fail()) {
            cout << "Invalid operation, DATE was not written properly (DD/MM/YYYY)!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        menuSeparator();

        cout << "The costs associated with the national team players and staff between " << date1 << " and ";
        cout << date2 << " were of " << teamCostCalculator(firstDate, endDate) + staffCostCalculator(firstDate, endDate)<< " euros." << endl;
        break;
    }
}
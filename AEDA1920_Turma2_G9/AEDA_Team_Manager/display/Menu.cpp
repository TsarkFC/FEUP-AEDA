//
// Created by tiago on 07/11/2019.
//


#include "Menu.h"
#include "../Exceptions.h"

using namespace std;

Menu::Menu(){
    readNationalTeam("NationalTeam.txt");
}

//Runs the main Menu
void Menu::runMenu() {
    int option;


    while(true) {
        menuSeparator();

        cout << "Welcome to the National Football Team Manager! What do you want to do?" << endl << endl;
        cout << "Please choose what your option:" << endl << endl;

        cout << "Exit                                                               [0]" << endl;
        cout << "People                                                             [1]" << endl;
        cout << "Games                                                              [2]" << endl;
        cout << "Call Ups                                                           [3]" << endl;
        cout << "Economies                                                          [4]" << endl;
        cout << "Save information and Exit                                          [5]" << endl << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;
        validOption(option, 5);

        menuSeparator();

        if (option == 0) { exit(0); }
        else if (option == 1) { runPeopleMenu(); }
        else if (option == 2) { runGameMenu(); }
        else if (option == 3) { runCallUpMenu(); }
        else if (option == 4) { runEconomiesMenu(); }
        else if (option == 5) {saveAndExit(peopleFile,callUpFile,gameFile,statisticsFile); }
    }
}

void Menu::validOption(int &option,int optionsNumber){
    while (cin.fail() || option < 0 || option > optionsNumber)
    {
        cout << "Invalid option, please insert the option again: ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> option;
    }
    cin.clear();
    cin.ignore(100, '\n');
}

//Outputs a separator made of *
void Menu::menuSeparator() {
    cout << endl << endl;
    for (int i = 0; i < 70; i++) { cout << "="; }
    cout << endl;
}

//Asks for a valid int until the user inputs it
void Menu::validCin(int &option) {

    while (cin.fail())
    {
        cout << "Invalid input, please insert your answer again: ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> option;
    }
}

int Menu::askForId(){
    int id;
    cout << "Please Insert an ID: ";
    cin >> id;
    validCin(id);
    cin.clear();
    cin.ignore(100, '\n');
    return id;
}


Date Menu::askForDate(string dateName,string &text){
    Date date = Date();
    cout << dateName << "(DD/MM/YYYY): ";
    cin.clear();
    getline(cin, text);

    while (!Date::validDateText(text))
    {
        cout << "Invalid date, please insert again: ";
        getline(cin, text);
    }
    return date.dateTextConverter(text);;
}

float Menu::askForFloat(string &text, const string &what, float lower, float higher){
    bool exceptionCatched = true;
    cout << what << ": ";
    cin >> text;
    while(exceptionCatched) {
        try {
            validFloat(text);
            if(stof(text) < lower  || stof(text) > higher) throw InvalidFloat();
            exceptionCatched = false;

        }
        catch (std::invalid_argument ia) {
            cout << "Invalid number, please insert your answer again: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> text;
        }
        catch (InvalidFloat) {
            cout << what << " can only be between " << lower << " and " << higher << ": ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> text;
        }

    }
    cin.clear();
    cin.ignore(100, '\n');
    return stof(text);
}

bool Menu::askYesNoQuestion() {
    int option;
    cout << endl << "Yes [1]" << endl;
    cout << "No  [2]" << endl;
    cout << "Please the number of your option: ";
    cin >> option;
    validOption(option,2);
    if(option == 1) return true;
    else if(option == 2) return false;
    return true;

}

int Menu::askForInt(const string &what) {
    bool exceptionCatched = true;
    string text;
    cout << what << ": ";
    cin >> text;

    while(exceptionCatched) {
        try {
            validInt(text);
            exceptionCatched = false;

        }
        catch (std::invalid_argument ia) {
            cout << "Invalid number, please insert your answer again: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> text;
        }

    }
    cin.clear();
    cin.ignore(100, '\n');
    return stoi(text);
}
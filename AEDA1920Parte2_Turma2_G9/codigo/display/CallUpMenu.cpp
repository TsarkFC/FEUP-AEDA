//
// Created by tiago on 08/11/2019.
//


#include "Menu.h"
#include <algorithm>

void Menu::runCallUpMenu() {
    int option;

    while(true) {
        cout << "Welcome to the Call Up menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "See information from all Call Ups.                                 [1]" << endl;
        cout << "See information from a specific call up.                           [2]" << endl;
        cout << "Create new Call up.                                                [3]" << endl;
        cout << "Remove Call Up.                                                    [4]" << endl;
        cout << "Modify Call Up.                                                    [5]" << endl;
        cout << "Create Game and add to Call Up.                                    [6]" << endl;
        cout << "Remove Game from Call Up.                                          [7]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 7);

        menuSeparator();

        if (option == 0) { break; }
        if (option == 1) { allCallUpMenu(); }
        if (option == 2) { callUpMenu(); }
        if (option == 3) { createCallUpMenu(); }
        if (option == 4) { removeCallUpMenu(); }
        if (option == 5) { modifyCallMenu(); }
        if (option == 6) { addGameCallUpMenu(createGameOption(cout)); }
        if (option == 7) { removeGameCallUpMenu(); }

        break;
    }
}

void Menu::headerCallUp(ostream &out) {
    out << endl << endl << endl;
    out << setw(55) << setfill('-') << "-" <<  endl;
    out <<  left << setw(5)  << setfill(' ') << "ID" << "│  ";
    out <<  left << setw(8)  << setfill(' ') << "Begin date" << "│  ";
    out <<  left << setw(10) << setfill(' ') << "End date"  << "│ ";
    out <<  left << setw(20) << setfill(' ') <<  "List of games"<< "│ ";
    out << endl;
}

void Menu::allCallUpMenu() {
    headerCallUp(cout);
    for (auto i = callUps.begin(); i != callUps.end(); i++) {
        (*i)->showCallUp(cout);
    }
}

void Menu::callUpMenu() {
    menuSeparator();
    int option;
    CallUp* call;

    while (true){
        cout << "Insert the ID of the call up you want to see: ";
        cin >> option;

        if (cin.fail()){
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        try{
            //DISPLAYS CALL UP GENERALL INFORMATION
            searchCallUpByID(option);
            headerCallUp(cout);

            call = getCallUpWithID(option);
            call->showCallUp(cout);
        }
        catch(...){
            cout << "There are no call ups with such id (" << option << ") !" << endl;
            menuSeparator();
            break;
        }

        //DISPLAYS PLAYERS IN CALL UP
        cout  << endl;
        tableHeaderPlayer(cout);

        for (auto i = 0; i < call->getPlayerStatistics().size(); i++){
            players[searchByID(players, call->getPlayerStatistics()[i]->getPlayerID())]->print(cout);
        }

        tableFooterPlayer(cout);


        menuSeparator();
        break;
    }
}

//IS NOT CREATING GAMES
void Menu::createCallUpMenu() {
    menuSeparator();
    int id;
    float cost;

    int numGames;
    vector<Game*> call_games;

    string date;
    Date begDate, endDate;

    Date begPlayerDate, endPlayerDate;
    vector<CallUpPlayerStatistics*> stats;

    while (true) {
        //DEFAULT ID
        id = callUps.back()->getId() + 1;

        //GET DAILY COST
        cout << "Accomodation daily cost: ";
        cin >> cost;

        while (cin.fail()) {
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> cost;
        }

        //CREATE NEW GAMES FOR NEW CALL UP AND ADD TO VECTOR
        cout << "Number of games to be added in call up: ";
        cin >> numGames;

        while (cin.fail()) {
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> cost;
        }

        cin.clear();
        cin.ignore(10000, '\n');

        for (int i = 0; i < numGames; i++){
            call_games.push_back(getGameWithID(createGameOption(cout)));
        }

        menuSeparator();

        //GET DATES
        askForDates(begDate, endDate);

        cout << endl << endl;
        allEqual(begDate, endDate, call_games, stats);

        menuSeparator();
        break;
    }

    //ADD NEW CALL UP DATA BASE
    callUps.push_back(new CallUp(id, cost, call_games, stats, begDate, endDate));
}

void Menu::askForDates(Date& begDate, Date& endDate) {
    //GET BEGINNING DATE
    string date;
    bool isAfter;

    while(true) {
        while (true) {
            cout << "Insert beggining date (DD/MM/YYYY): ";
            cin >> date;

            try {
                begDate = begDate.dateTextConverter(date);
                break;
            } catch (...) {
                cout << "The inserted date was not written properly!";
                menuSeparator();
            }
        }

        //GET END DATE

        while (true) {
            isAfter = true;

            cout << "Insert ending date (DD/MM/YYYY): ";
            cin >> date;

            try {
                endDate = endDate.dateTextConverter(date);
                break;
            } catch (...) {
                cout << "The inserted date was not written properly!";
                menuSeparator();
            }
        }

        //CHECK IF ENDING IS AFTER BEGINNING
        if (!endDate.isAfter(begDate)) {
            cout << "The ending date cannot come before the beginning date!";
            isAfter = false;
            menuSeparator();
        }

        if (isAfter) break;
    }
}

void Menu::removeCallUpMenu() {
    menuSeparator();
    int option;

    while (true) {
        cout << "Insert the ID of the call up you want to remove: ";
        cin >> option;

        if (cin.fail()) {
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        try {
            searchCallUpByID(option);
        }
        catch (...) {
            cout << "There are no call ups with such id (" << option << ") !" << endl;
            menuSeparator();
            break;
        }

        //ERASE ELEMENT
        deleteCallUp(option);

        menuSeparator();
        break;

    }
}

void Menu::modifyCallMenu() {
    menuSeparator();

    int option, id;

    while (true) {
        cout << "Insert the ID of the call up you want to modify: ";
        cin >> id;

        if (cin.fail()) {
            cout << "Invalid option, ID must be an integer!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            menuSeparator();
            break;
        }

        try {
            searchCallUpByID(id);
        }
        catch (...) {
            cout << "There are no call ups with such id (" << id << ") !" << endl;
            menuSeparator();
            break;
        }

        cout << "Go back.                                                           [0]" << endl;
        cout << "Change daily costs.                                                [1]" << endl;
        cout << "Reduce beggining date.                                             [2]" << endl;
        cout << "Extend end date.                                                   [3]" << endl;

        validOption(option, 3);

        menuSeparator();

        if (option == 0) break;
        if (option == 1){
            changeDailyCosts(id);
            menuSeparator();
            break;
        }
        if (option == 2){
            reduceBegDate(id);
            menuSeparator();
            break;
        }
        if (option == 3) {
            extendEndDate(id);
            menuSeparator();
            break;
        }
    }
}

void Menu::changeDailyCosts(int id) {
    float cost;
    cout << "New accomodation daily cost: ";
    cin >> cost;

    while (cin.fail()) {
        cout << "Invalid option, please insert the option again: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> cost;
    }

    getCallUpWithID(id)->setDailyCost(cost);
}

void Menu::reduceBegDate(int id) {
    string date;
    Date begDate;

    while (true) {

        cout << "Insert the new beggining date (DD/MM/YYYY): ";
        cin >> date;

        if (begDate.validDateText(date)) {
            begDate = begDate.dateTextConverter(date);
        }
        else {
            cout << "The inserted date was not written properly!";
            menuSeparator();
            break;
        }

        if (begDate.dateToDays() > getCallUpWithID(id)->getBegDate().dateToDays()){
            cout << "You can only reduce the date value!" << endl;
            menuSeparator();
            break;
        }

        getCallUpWithID(id)->setBegDate(begDate);

        break;
    }
}

void Menu::extendEndDate(int id){
    string date;
    Date endDate;

    while (true) {

        cout << "Insert the new beggining date (DD/MM/YYYY): ";
        cin >> date;

        if (endDate.validDateText(date)) {
            endDate = endDate.dateTextConverter(date);
        }
        else {
            cout << "The inserted date was not written properly!";
            menuSeparator();
            break;
        }

        if (endDate.dateToDays() < getCallUpWithID(id)->getEndDate().dateToDays()){
            cout << "You can only extend the date value!" << endl;
            menuSeparator();
            break;
        }

        getCallUpWithID(id)->setEndDate(endDate);

        menuSeparator();
        break;
    }
}

void Menu::addGameCallUpMenu(const int& id) {
    menuSeparator();

    int idc;
    bool error;

    while (true) {
        error = false;

        cout << "Insert the ID of the call up you want to add the game to: ";
        cin >> idc;

        while (cin.fail()) {
            cout << "Invalid option, please insert the option again: ";
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
            error = true;
        }

        if (!error) {
            vector<Game*> j = getCallUpWithID(idc)->getGames();
            j.push_back(getGameWithID(id));
            getCallUpWithID(idc)->setGames(j);

            menuSeparator();
            break;
        }
    }
}

void Menu::removeGameCallUpMenu() {
    menuSeparator();

    int idc;

    while (true) {
        cout << "Insert the ID of the call up you want to remove the game : ";
        cin >> idc;

        if (cin.fail()) {
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(10000, '\n');

            menuSeparator();
            break;
        }

        try {
            searchCallUpByID(idc);
        }
        catch (...) {
            cout << "There are no call ups with such id (" << idc << ") !" << endl;

            menuSeparator();
            break;
        }

        removeGameOption(cout, idc);
        menuSeparator();
        break;
    }
}

void Menu::allEqual(Date begDate, Date endDate, vector<Game*> call_games, vector<CallUpPlayerStatistics*> stats) {
    int option;

    while(true) {
        cout << "Did all the players stayed during all the call up time?" << endl << endl;
        cout << "YES.                                                           [0]" << endl;
        cout << "NO.                                                            [1]" << endl;
        cin >> option;

        validOption(option, 1);

        if (option == 0) { setAllEqual(begDate, endDate, call_games, stats);}
        if (option == 1) {
            menuSeparator();
            int option_sub;
            cout << endl << endl;
            cout << "Set information manually.                                      [0]" << endl;
            cout << "Select list of players that stayed during a different period.  [1]" << endl;
            cin >> option_sub;

            validOption(option_sub, 1);

            if (option_sub == 0) {infoManually(begDate, endDate, call_games, stats);}
            if (option_sub == 1) {
                listDifferent(begDate, endDate, call_games, stats);
            }
        }

        break;
    }
}

void Menu::setAllEqual(Date begDate, Date endDate, vector<Game*> call_games, vector<CallUpPlayerStatistics*> stats) {
    for (auto i = call_games.begin(); i != call_games.end(); i++) {
        for (auto j = 0; j < (*i)->getNationalPlayers().size(); j++) {
            stats.push_back(new CallUpPlayerStatistics((*i)->getNationalPlayers()[j]->getId(), begDate, endDate));
        }
    }
}

void Menu::infoManually(Date begDate, Date endDate, vector<Game*> call_games, vector<CallUpPlayerStatistics*> stats) {
    string date;
    Date begPlayerDate, endPlayerDate;
    bool error;

    for (auto i = call_games.begin(); i != call_games.end(); i++) {
        for (auto j = 0; j < (*i)->getNationalPlayers().size(); j++) {

            //GET BEGINNING DATE
            while (true) {
                error = false;

                cout << "Insert player's with id " << (*i)->getNationalPlayers()[j]->getId()
                     << " beggining date (DD/MM/YYYY): ";
                cin >> date;

                try {
                    begPlayerDate = begPlayerDate.dateTextConverter(date);
                }
                catch (...) {
                    cout << "The inserted date was not written properly!";
                    menuSeparator();
                    error = true;
                }

                //CHECK IF BEGGININNG PLAYER DATE IS AFTER OR EQUAL TO CALL UP'S
                if (begPlayerDate.dateToDays() < begDate.dateToDays() && !error) {
                    cout << "Player date is not included in call up time!";
                    menuSeparator();
                    error = true;
                }
                else break;
            }

            //GET END DATE
            while(true){
                error = false;

                cout << "Insert player's with id " << (*i)->getNationalPlayers()[j]->getId()
                     << " ending date (DD/MM/YYYY): ";
                cin >> date;

                try {
                    endPlayerDate = endPlayerDate.dateTextConverter(date);
                }
                catch(...){
                    cout << "The inserted date was not written properly!";
                    menuSeparator();
                    error = true;
                }

                //CHECK IF ENDING IS AFTER BEGINNING
                if (!endPlayerDate.isAfter(begPlayerDate) && !error) {
                    cout << "The ending date cannot come before the beginning date!";
                    menuSeparator();
                    error = true;
                }

                //CHECK IF ENDING PLAYER DATE IS BEFORE OR EQUAL TO CALL UP'S
                if (endPlayerDate.dateToDays() > endDate.dateToDays() && !error) {
                    cout << "Player date is not included in call up time!";
                    menuSeparator();
                    error = true;
                }

                if (!error) break;
            }

            stats.push_back(new CallUpPlayerStatistics((*i)->getNationalPlayers()[j]->getId(), begPlayerDate, endPlayerDate));
        }
    }
}

void Menu::listDifferent(Date begDate, Date endDate, vector<Game *> call_games,
                                 vector<CallUpPlayerStatistics *> stats) {
    string indexes, date;
    vector<int> vec_indexes;
    Date begPlayerDate, endPlayerDate;
    bool error;

    //GET INDEX OF GAMES
    cout << "Insert a list of the game's indexes separated by commas: ";
    cin >> indexes;

    vec_indexes = separateCharacterInt(indexes, ',');
    insertionSort(vec_indexes);


    //ITERATE INDEXES
    for (auto i = call_games.begin(); i != call_games.end(); i++) {
        for (auto j = 0; j < (*i)->getNationalPlayers().size(); j++) {
            if (find(vec_indexes.begin(), vec_indexes.end(), (*i)->getNationalPlayers()[j]->getId()) == vec_indexes.end()){
                stats.push_back(new CallUpPlayerStatistics((*i)->getNationalPlayers()[j]->getId(), begDate, endDate));
            }
            else{
                //GET BEGINNING DATE
                while (true) {
                    error = false;

                    cout << "Insert player's with id " << (*i)->getNationalPlayers()[j]->getId() << " beggining date (DD/MM/YYYY): ";
                    cin >> date;

                    try {
                        begPlayerDate = begPlayerDate.dateTextConverter(date);
                    }
                    catch (...) {
                        cout << "The inserted date was not written properly!";
                        menuSeparator();
                        error = true;
                    }

                    //CHECK IF BEGGININNG PLAYER DATE IS AFTER OR EQUAL TO CALL UP'S
                    if (begPlayerDate.dateToDays() < begDate.dateToDays() && !error) {
                        cout << "Player date is not included in call up time!";
                        menuSeparator();
                        error = true;
                    }
                    else break;
                }

                //GET END DATE
                while(true){
                    error = false;

                    cout << "Insert player's with id " << (*i)->getNationalPlayers()[j]->getId()
                         << " ending date (DD/MM/YYYY): ";
                    cin >> date;

                    try {
                        endPlayerDate = endPlayerDate.dateTextConverter(date);
                    }
                    catch(...){
                        cout << "The inserted date was not written properly!";
                        menuSeparator();
                        error = true;
                    }

                    //CHECK IF ENDING IS AFTER BEGINNING
                    if (!endPlayerDate.isAfter(begPlayerDate) && !error) {
                        cout << "The ending date cannot come before the beginning date!";
                        menuSeparator();
                        error = true;
                    }

                    //CHECK IF ENDING PLAYER DATE IS BEFORE OR EQUAL TO CALL UP'S
                    if (endPlayerDate.dateToDays() > endDate.dateToDays() && !error) {
                        cout << "Player date is not included in call up time!";
                        menuSeparator();
                        error = true;
                    }

                    if (!error) break;
                }
                stats.push_back(new CallUpPlayerStatistics((*i)->getNationalPlayers()[j]->getId(), begPlayerDate, endPlayerDate));
            }
        }
    }
}

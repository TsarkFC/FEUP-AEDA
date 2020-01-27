#include "Menu.h"
#include "../Exceptions.h"


//Main Menu with operations to all kinds of people
void Menu::runPeopleMenu() {

    int option;

    while(true){
        menuSeparator();

        cout << "Welcome to the People Menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "Go back                                                            [0]" << endl;
        cout << "See information from everyone                                      [1]" << endl;
        cout << "See information from everyone ordered by name                      [2]" << endl;
        cout << "See information from a specific person                             [3]" << endl;
        cout << "Search Person by name                                              [4]" << endl;
        cout << "Football Players                                                   [5]" << endl;
        cout << "Technicians                                                        [6]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 6);

        menuSeparator();

        if (option == 0) { break; }
        if (option == 1) { showEveryone(cout); }
        if (option == 2) { showEveryoneName(cout); }
        if (option == 3) { showSpecificPersonOption(); }
        if (option == 4) { showPersonByName(); }
        if (option == 5) { runPlayersMenu(); }
        if (option == 6) { runTechnicianMenu(); }


    }
}

//Asks for the id of a person and shows the person in the screen
void Menu::showSpecificPersonOption() {
    int i = askForValidId(people);
    menuSeparator();
    showSpecificPerson(cout,i);
}

//asks for the name of a person and shows everyone with that name
void Menu::showPersonByName() {

    string text;
    cout << "Please Insert Name of the Person: " << endl;
    getline(cin,text);
    vector<Person*> peepz = searchByName(people,text);
    menuSeparator();

    tableHeaderPlayer(cout);
    for (int i = 0; i < peepz.size(); ++i) {
        cout << peepz[i];
    }
    tableFooterPlayer(cout);

}

//Prints to to out a person with a certain id
void Menu::showSpecificPerson(ostream &out,int i){

    tableHeaderPlayer(out);
    out << people[searchByID(people,i)];
    tableFooterPlayer(out);
}

//Shows everyone in the Database
void Menu::showEveryone(ostream &out) {

    tableHeaderPlayer(out);

    for (int i = 0; i < people.size(); ++i) {
        out << people[i];
    }
    tableFooterPlayer(out);
}

//Shows everyone in the Database
void Menu::showEveryoneName(ostream &out) {

    sortByName(people);
    tableHeaderPlayer(out);

    for (int i = 0; i < people.size(); ++i) {
        out << people[i];
    }
    tableFooterPlayer(out);
    sortByID(people);
}

//Header of the People table
void Menu::tableHeaderPlayer(ostream &out){
    out << endl << endl << endl;
    out << setw(117) << setfill('-') << "-" <<  endl;
    out <<  left << setw(4)  << setfill(' ') << "id" << "│  ";
    out <<  left << setw(20) << setfill(' ') << "Name"  << "│ ";
    out <<  left << setw(11) << setfill(' ') <<  "Birthday"<< "│ ";
    out <<  left << setw(9) << setfill(' ') << "Salary"<< "│  "  ;
    out <<  left << setw(20)  << setfill(' ') << "Position" << "│ ";
    out <<  left << setw(9) << setfill(' ') << "Club"  << " │";
    out <<  left << setw(4) << setfill(' ')<<   "Weight"<< " │";
    out <<  left << setw(5) << setfill(' ') << "Height"<< " │";
    out <<  left << setw(5) << setfill(' ') << fixed  << setprecision(2) << "Pass"<< " │";
    out <<  left << setw(5) << setfill(' ') << "Health"<< " │" << endl;
    out << setw(117) << setfill('-') << "-" << "│" <<  endl;
}

//Footer of the people table
void Menu::tableFooterPlayer(ostream &out){
    out << setw(117) << setfill('-') << "-" << endl;
}

//Asks for all the information about a person
void Menu::askPersonInformation(string &name, float &salary, Date &birthday){
    string text;

    name = askForString("Name");
    birthday = askForDate("Birthday",text);
    salary = askForFloat(text,"Salary",0,999999);
}

//Asks the user to insert a string of type what
string Menu::askForString(const string &what){
    string name;
    cout << what << ": ";
    getline(cin,name);
    return name;
}



/*****************************************
 ***********PLAYERS MENU******************
 *****************************************/

//Runs Player's menu with all specific players operations
void Menu::runPlayersMenu() {
    int option;

    while(true) {
        cout << "Welcome to the players Menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "Create a new Football Player.                                      [1]" << endl;
        cout << "Change a player's information.                                     [2]" << endl;
        cout << "Remove a player.                                                   [3]" << endl;
        cout << "See a specific player statistics.                                  [4]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 4);

        menuSeparator();

        if (option == 0) { break; }
        if (option == 1) { createPlayerOption(); }
        if (option == 2) { modifyPlayerOption(); }
        if (option == 3) { removePlayerOption(); }
        if (option == 4) { playerMenuTransition();}

        break;
    }
}

//Asks the user for information of new player and adds it to the databas
void Menu::createPlayerOption(){
    FootballPlayer *player = new FootballPlayer();
    askPlayerInformation(player);
    addtoVector(people,player);
    addtoVector(players,player);

    menuSeparator();
    cout << "Player Added Successfully!";
}

//Asks for an id of a player and removes it from the database
void Menu::removePlayerOption(){
    int id;
    vector<FootballPlayer*> played;
    bool error = false;
    int remove;

    //CHECK IF PLAYER HAS PLAYED ANY GAME
    while (true){
        error = false;

        id = askForValidId(players);

        for (int i = 0; i < games.size(); i++){
            played = games[i]->getNationalPlayers();
            try{
                remove = searchByID(played, id);
                error = true;
            }
            catch(...) {
                continue;
            }
        }
        if (!error) break;
        else{
            cout << endl << "The selected ID corresponds to a player that has played in some games. Impossible to remove..." << endl << endl;
        }
    }

    removeById(people,id);
    removeById(players,id);
    menuSeparator();
    cout << "Player Removed Successfully!" << endl;
}


//Asks the user wich player it wats to modify and the new information of the palyer
//then it modifies it
void Menu::modifyPlayerOption(){
    int id = askForValidId(players);
    FootballPlayer *player = new FootballPlayer();
    cin.clear();
    askPlayerInformation(player);
    int index = searchByID(people,id);
    people[index]->modify(player);
    menuSeparator();
    cout << "Player Modified Successfully!";

}

//Function to ask the user all the informations it wants to attribute to the player
void Menu::askPlayerInformation(FootballPlayer *player){
    string name,position,club,input;
    float salary,weight,height,pass_value;
    Date birthday = Date();
    bool injury;

    askPersonInformation(name,salary,birthday);
    player->setName(name);
    player->setSalary(salary);
    player->setBirthday(birthday);
    player->setPosition(askForString("Position"));
    player->setClub(askForString("Club"));
    player->setWeight(askForFloat(input,"Weight",40,250));
    player->setHeight(askForFloat(input, "Height",100,300));
    player->setPassValue(askForFloat(input,"Pass Value",0, 100000));

    cout << "Is the player Injured? : ";
    player->setInjury(askYesNoQuestion());


}


//Runs Menu with all operations specifc to technicians
void Menu::runTechnicianMenu() {
    int option;

    while(true) {
        cout << "Welcome to the players Menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "0. Go back" << endl;
        cout << "1. Create a new Technician." << endl;
        cout << "2. Change a technician information." << endl;
        cout << "3. Remove a technician" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 3);


        menuSeparator();

        if (option == 0) { break; }
        if (option == 1) { createTechOption(); }
        if (option == 2) { modifyTechOption(); }
        if (option == 3) { removeTechOption(); }
    }
}

//Aks the user for information about a technician and adds it to the database
void Menu::createTechOption(){
    Technician *technician = new Technician();
    askTechInformation(technician);
    addtoVector(people,technician);
    addtoVector(technicians,technician);
    menuSeparator();
    cout << "Technician Added Successfully!";
    menuSeparator();
}

//Asks the id of the technician it wants to remove and removes it from the database
void Menu::removeTechOption(){
    int id = askForValidId(technicians);
    removeById(people,id);
    removeById(technicians,id);
    menuSeparator();
    cout << "Technician Removed Successfully!";
}

//Asks the user for information about a Technician and the id of the technician it wants to change
//Then it setts all the information of the technician
void Menu::modifyTechOption(){
    int id = askForValidId(technicians);
    Technician *technician = new Technician();
    cin.clear();
    cin.ignore(100, '\n');
    askTechInformation(technician);
    int index = searchByID(people,id);
    people[index]->modify(technician);
    menuSeparator();
    cout << "Technician Modified Successfully!";
}

//Asks the user for all the nformation of a technician
void Menu::askTechInformation(Technician *technician){
    string name,role;
    float salary;
    Date birthday = Date();

    askPersonInformation(name,salary,birthday);
    technician->setName(name);
    technician->setSalary(salary);
    technician->setBirthday(birthday);

    technician->setRole(askForString("Role"));
}



void Menu::showPlayerGames(int id) {
    tableHeaderAllGames(cout);
    for (auto i = games.begin(); i != games.end(); i++){
        for (auto j = 0; j < (*i)->getPlayerStatistics().size(); j++){
            if (id == (*i)->getPlayerStatistics()[j].getPlayerID()){
                (*i)->print(cout);
            }
        }
    }
    tableFooterAllGames(cout);
}

void Menu::showPlayerCallUps(int id) {
    headerCallUp(cout);
    for (auto i = callUps.begin(); i != callUps.end(); i++){
        for (auto j = 0; j < (*i)->getPlayerStatistics().size(); j++){
            if (id == (*i)->getPlayerStatistics()[j]->getPlayerID()){
                (*i)->showCallUp(cout);
            }
        }
    }
}

void Menu::showGameStats(int id) {
    int option, pos, pos_stat;

    while (true) {
        cout << "Insert the ID of the pretended game: ";
        cin >> option;

        if (cin.fail()) {
            cout << "Invalid option, ID must be an integer!" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            menuSeparator();
            break;
        }

        try{
            pos = searchGameByID(games, option);
        }
        catch (InexistentId){
            cout << "There is no game with th given ID!" << endl;
            menuSeparator();
            break;
        }

        try {
            pos_stat = searchStatsByID(games[pos]->getPlayerStatistics(), id);
        }
        catch(InexistentId){
            cout << "Player did not take part of the selected game!" << endl;
            menuSeparator();
            break;
        }

        tableHeaderStatistics(cout);
        games[pos]->getPlayerStatistics()[pos_stat].print(cout);
        tableFooterStatistics(cout);
        menuSeparator();
        break;
    }
}

void Menu::showCallUpStats(int id) {
    int option, pos, pos_stat;
    CallUp* call;
    int numberOfGoals = 0;
    int minutesPlayed = 0;
    int kilometers = 0;
    int numberOfPasses = 0;
    int numberOfYellowCards = 0;
    int numberOfRedCards = 0;

    while (true) {
        cout << "Insert the ID of the pretended call up: ";
        cin >> option;

        if (cin.fail()) {
            cout << "Invalid option, ID must be an integer!" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            menuSeparator();
            break;
        }

        try {
            call = getCallUpWithID(option);
        }
        catch (...) {
            cout << "There is no call up with th given ID!" << endl;
            menuSeparator();
            break;
        }

        try {
            for (auto i = 0; i < (call->getGames()).size(); i++) {
                pos_stat = searchStatsByID(call->getGames()[i]->getPlayerStatistics(), id);

                numberOfGoals += (call->getGames()[i]->getPlayerStatistics()[pos_stat]).getNumberOfGoals();
                minutesPlayed += (call->getGames()[i]->getPlayerStatistics()[pos_stat]).getMinutesPlayed();
                kilometers += (call->getGames()[i]->getPlayerStatistics()[pos_stat]).getKilometers();
                numberOfPasses += (call->getGames()[i]->getPlayerStatistics()[pos_stat]).getNumberOfPasses();
                numberOfYellowCards += (call->getGames()[i]->getPlayerStatistics()[pos_stat]).getNumberOfYellowCards();
                numberOfRedCards += (call->getGames()[i]->getPlayerStatistics()[pos_stat]).getNumberOfRedCards();
            }

            tableHeaderStatistics(cout);
            PlayerGameStatistics p(id, numberOfGoals, minutesPlayed, kilometers, numberOfPasses, numberOfYellowCards,
                                   numberOfRedCards);
            p.print(cout);
            tableFooterStatistics(cout);
            menuSeparator();
            break;
        }
        catch(...){
            cout << endl << endl << "Player does not exist in call up!" << endl;
            menuSeparator();
            break;
        }
    }

}

void Menu::playerMenuTransition() {
    int id, option;

    while (true) {
        cout << "Insert the ID of the player you want to see information from: ";
        cin >> id;

        if (cin.fail()) {
            cout << "Invalid option, ID must be an integer!";
            cin.clear();
            cin.ignore(100, '\n');
            break;
        }

        try {
            searchByID(players, id);
        }
        catch (InexistentId) {
            cout << "There are no players with such id (" << id << ") !" << endl;
            menuSeparator();
            break;
        }
        menuSeparator();

        cout << endl << endl;

        cout << "Go back.                                                           [0]" << endl;
        cout << "See all games played by a specific player.                         [1]" << endl;
        cout << "See all call-ups that a player participated.                       [2]" << endl;
        cout << "See player statistics from a game.                                 [3]" << endl;
        cout << "See player statistics from call up.                                [4]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        validOption(option, 4);

        menuSeparator();

        if (option == 0) break;
        if (option == 1) { showPlayerGames(id); }
        if (option == 2) { showPlayerCallUps(id); }
        if (option == 3) { showGameStats(id);}
        if (option == 4) { showCallUpStats(id);}

        break;
    }
}


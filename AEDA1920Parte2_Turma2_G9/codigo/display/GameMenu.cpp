//
// Created by tiago on 08/11/2019.
//


#include "Menu.h"

void Menu::runGameMenu() {
    int option;

    while (true) {
        cout << "Welcome to the Game Menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "See information from all games.                                    [1]" << endl;
        cout << "See information from a specific game.                              [2]" << endl;
        cout << "See information from a specific game for a specific player.        [3]" << endl;
        cout << "Create new game.                                                   [4]" << endl;
        cout << "Remove Game.                                                       [5]" << endl;
        cout << "Modify Game.                                                       [6]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        while (cin.fail() || option < 0 || option > 6) {
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> option;
        }

        cin.clear();
        cin.ignore(100, '\n');

        menuSeparator();

        if (option == 0) { break; }
        if (option == 1) { showAllGames(cout); }
        if (option == 2) { showSpecificGame(cout); }
        if (option == 3) { showSpecificStats(cout); }
        if (option == 4) { addGameCallUpMenu(createGameOption(cout)); }
        if (option == 5) { removeGameCallUpMenu(); }
        if (option == 6) { showModifyGameOptions(cout); }

        break;
    }
}

void Menu::tableHeaderAllGames(ostream &out) {
    out << endl << endl << endl;
    out << "Games:\n";
    out << setw(104) << setfill('-') << "-" <<  endl;
    out <<  left << setw(4)  << setfill(' ') << "id" << "│  ";
    out <<  left << setw(20) << setfill(' ') << "City"  << "│ ";
    out <<  left << setw(20) << setfill(' ') <<  "Country"<< "│ ";
    out <<  left << setw(30)  << setfill(' ') << "Stadium" << "│ ";
    out <<  left << setw(20 )  << setfill(' ') << "Game Title" << "│ ";
    out << endl << setw(103) << setfill('-') << "-" << "│" <<  endl;

}

void Menu::tableFooterAllGames(ostream &out) {
    out << setw(104) << setfill('-') << "-" << endl;
}

void Menu::tableHeaderStatistics(ostream &out) {
    out << endl << endl << endl;
    out << "Player Statistics:\n";
    out << setw(110) << setfill('-') << "-" <<  endl;
    out <<  left << setw(11)  << setfill(' ') << "Player ID" << "│ ";
    out <<  left << setw(15) << setfill(' ') << "Goals"  << "│ ";
    out <<  left << setw(16) << setfill(' ') <<  "Minutes Played"<< "│ ";
    out <<  left << setw(12)  << setfill(' ') << "Kilometers" << "│ ";
    out <<  left << setw(18)  << setfill(' ') << "Number of Passes" << "│ ";
    out <<  left << setw(14)  << setfill(' ') << "Yellow Cards" << "│ ";
    out <<  left << setw(11)  << setfill(' ') << "Red Cards" << "│ ";
    out <<  endl << setw(109) << setfill('-') << "-" << "│" <<  endl;
}

void Menu::tableHeaderEnemyTeam(ostream &out) {
    out << endl << endl << endl;
    out << "Enemy Team:\n";
    out << setw(30) << setfill('-') << "-" <<  endl;
    out <<  left << setw(30) << setfill(' ') << "Name"  << "│ ";
    out <<  endl << setw(30) << setfill('-') << "-" << "│" <<  endl;
}

void Menu::tableHeaderReferee(ostream &out) {
    out << endl << endl << endl;
    out << "Referees:\n";
    out << setw(30) << setfill('-') << "-" <<  endl;
    out <<  left << setw(30) << setfill(' ') << "Name"  << "│ ";
    out <<  endl << setw(30) << setfill('-') << "-" << "│" <<  endl;
}

void Menu::tableFooterStatistics(ostream &out){
    out << setw(110) << setfill('-') << "-" << endl;
}

void Menu::tableFooterEnemyTeamReferee(ostream &out) {
    out << setw(30) << setfill('-') << "-" << endl;
}

void Menu::showAllGames(ostream &out) {

    tableHeaderAllGames(out);
    for(Game* g : games){
        g->print(out);
    }

    tableFooterAllGames(out);

}

void Menu::showSpecificGame(ostream &out) {
    while(true) {
        out << "Which game do you wish to see?\n";
        int id = askForId();

        try{
            searchGameByID(games, id);
        }
        catch(...){
            cout << "There id no game with id (" << id << ")!" << endl;
            menuSeparator();
            break;
        }

        tableHeaderAllGames(out);

        games[id - 1]->print(out);

        tableFooterAllGames(out);

        tableHeaderStatistics(out);

        for (PlayerGameStatistics stat : games[id - 1]->getPlayerStatistics()) {
            stat.print(out);
        }

        tableFooterStatistics(out);

        tableHeaderPlayer(out);

        for (FootballPlayer *p : games[id - 1]->getNationalPlayers()) {
            p->print(out);
        }

        tableFooterPlayer(out);

        tableHeaderEnemyTeam(out);

        for (string s : games[id - 1]->getEnemyPlayers()) {
            out << left << setw(30) << setfill(' ') << s << "│\n";
        }

        tableFooterEnemyTeamReferee(out);

        tableHeaderReferee(out);

        for (string s : games[id - 1]->getReferees()) {
            out << left << setw(30) << setfill(' ') << s << "│\n";
        }

        tableFooterEnemyTeamReferee(out);

        break;
    }
}

void Menu::showSpecificStats(ostream &out) {
    int game_pos;
    while(true) {
        out << "Which game do you wish to see?\n";
        int gameID = askForId();

        try {
            game_pos = searchGameByID(games, gameID);
        }
        catch (...) {
            cout << "There id no game with id (" << gameID << ")!" << endl;
            menuSeparator();
            break;
        }

        out << "Which player do you wish to see?\n";
        int playerID = askForId();

        try {
            bool error = true;
            for (auto i = 0; i < games[game_pos]->getNationalPlayers().size(); i++){
                if (playerID == games[game_pos]->getNationalPlayers()[i]->getId()) error = false;
            }
            if (error) throw exception();
        }
        catch (...) {
            cout << "There id no player with id (" << playerID << ") in game with id (" << gameID << ")!" << endl;
            menuSeparator();
            break;
        }

        tableHeaderAllGames(out);

        games[gameID - 1]->print(out);

        tableFooterAllGames(out);

        tableHeaderStatistics(out);

        for (PlayerGameStatistics stat : games[gameID - 1]->getPlayerStatistics()) {
            if (stat.getPlayerID() == playerID) {
                stat.print(out);
                break;
            }
        }
        tableFooterStatistics(out);
        break;
    }
}

int Menu::createGameOption(ostream &out) {
    Game *newGame = new Game();

    newGame->setCity(askForString("City"));
    newGame->setCountry(askForString("Country"));
    newGame->setStadium(askForString("Stadium"));
    newGame->setGameTitle(askForString("Game Title"));

    menuSeparator();
    askForPlayers(out, newGame);

    menuSeparator();
    askForStringVector(out, "EnemyPlayers", newGame);

    menuSeparator();
    askForStringVector(out, "Referee", newGame);

    games.push_back(newGame);

    out << "Game created with success.\n";

    return newGame->getId();
}

int Menu::removeGameOption(ostream &out, const int& idc) {
    out << "What Game do you wish to remove?\n";
    int gameID = askForId();

    //GETS CALL UP AND REMOVES GAME FROM IR
    try {
        getCallUpWithID(idc)->removeGame(getGameWithID(gameID));
    }
    catch(GameDontExistsCallUp){
        cout << "The game does not exist in call up!" << endl;
        menuSeparator();
        return 0;
    }

    //REMOVES GAME FROM LIST OF GAMES
    if(removeGame(games, gameID)){
        out << "Game removed with success.\n";
        return gameID;
    }

    out << "Unable to remove the game.\n";
    return 0;
}



void Menu::askForPlayers(ostream &out, Game * game) {
    int playerID;
    PlayerGameStatistics stats;
    int index;
    vector<FootballPlayer*> vec;

    for(int i = 0; i < 11; i++){


        //CHECK IF PLAYER IS ALREADY IN THIS GAME
        while (true){
            out << "Insert the ID of the player number " << i+1 << " to add.\n";

            playerID = askForValidId(players);
            vec = game->getNationalPlayers();

            try{
                searchByID(vec, playerID);
                cout << endl << endl << "Player already exists in game!" << endl << endl << endl;
            }
            catch(InexistentId){
                break;
            }
        }
        index = searchByID(players, playerID);
        game->addNationalPlayer(players[index], askForPlayerStatistics(out, playerID));

        menuSeparator();
    }
}

void Menu::askForStringVector(ostream &out, string what, Game *game) {
    int counter = 0;

    if(what == "EnemyPlayers") {
        for (int i = 0; i < 11; i++) {
            counter++;
            game->addEnemyPlayer(askForString("Enemy Player " + to_string(counter)));
        }
    }
    else {
        counter = 0;
        for(int i=0; i < 5; i++){
            counter++;
            game->addReferee(askForString("Referee " + to_string(counter)));
        }
    }

}

PlayerGameStatistics Menu::askForPlayerStatistics(ostream &out, int playerID) {
    PlayerGameStatistics stats;

    stats.setPlayerID(playerID);

    //ASKS FOR NUMBER OF GOALS
    while (true) {
        try {
            stats.setNumberOfGoals(askForInt("Number of Goals"));
            break;
        }
        catch (...) {
            menuSeparator();
        }
    }

    //ASKS FOR MINUTES PLAYED
    while (true) {
        try {
            stats.setMinutesPlayed(askForInt("Minutes Played"));
            break;
        }
        catch (...) {
            menuSeparator();
        }
    }

    //ASKS FOR KILOMETERS
    while (true) {
        try {
            stats.setKilometers(askForInt("Kilometers"));
            break;
        }
        catch (...) {
            menuSeparator();
        }
    }

    //ASKS FOR NUMBER OF PASSES
    while (true) {
        try {
            stats.setNumberOfPasses(askForInt("Passes"));
            break;
        }
        catch (...) {
            menuSeparator();
        }
    }

    //ASKS FOR NUMBER OF YELLOW CARDS
    while (true) {
        try {
            stats.setNumberOfYellowCards(askForInt("Yellow Cards"));
            break;
        }
        catch (...) {
            menuSeparator();
        }
    }

    //ASKS FOR NUMBER OF RED CARDS
    while (true) {
        try {
            stats.setNumberOfRedCards(askForInt("Red Cards"));
            break;
        }
        catch (...) {
            menuSeparator();
        }
    }

    return stats;
}

void Menu::showModifyGameOptions(ostream &out) {
    int option;

    while(true) {
        cout << "Welcome to the Game Menu! Please choose what you want to do: ";
        cout << endl << endl;
        cout << "Go back.                                                           [0]" << endl;
        cout << "City                                                               [1] " << endl;
        cout << "Country                                                            [2]" << endl;
        cout << "Stadium                                                            [3]" << endl;
        cout << "Player Statistics                                                  [4]" << endl;
        cout << "National Players                                                   [5]" << endl;
        cout << "Enemy Players                                                      [6]" << endl;
        cout << "Referees                                                           [7]" << endl;
        cout << "Everything                                                         [8]" << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;

        while (cin.fail() || option < 0 || option > 8) {
            cout << "Invalid option, please insert the option again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> option;
        }

        cin.clear();
        cin.ignore(10000, '\n');

        menuSeparator();

        if (option == 0) { break; }
        else { modifyGameOption(cout, option); }

        break;
    }
}

void Menu::modifyGameOption(ostream &out, int option) {
    out << "What Game do you wish to modify?\n";
    int gameID = askForId();

    cin.clear();

    int index = searchGameByID(games, gameID);


    if(option == 1){
        games[index]->setCity(askForString("City"));
    }
    else if(option == 2){
        games[index]->setCountry(askForString("Country"));
    }
    else if(option == 3){
        games[index]->setStadium(askForString("Stadium"));
    }
    else if(option == 4){
        games[index]->setGameTitle(askForString("Game Title"));
    }
    else if(option == 5){

        tableHeaderPlayer(out);

        for(FootballPlayer * p : games[index]->getNationalPlayers()){
            p->print(out);
        }

        tableFooterPlayer(out);

        modifyPlayerOption();

    }
    else if(option == 6){
        tableHeaderEnemyTeam(out);

        for(string s : games[index]->getEnemyPlayers()){
            out <<  left << setw(30) << setfill(' ') << s  << "│\n";
        }

        tableFooterEnemyTeamReferee(out);

        askForStringVector(out, "EnemyPlayers", games[index]);

    }
    else if(option == 7){
        tableHeaderReferee(out);

        for(string s : games[index]->getReferees()){
            out <<  left << setw(30) << setfill(' ') << s  << "│\n";
        }

        tableFooterEnemyTeamReferee(out);

        askForStringVector(out, "Referee", games[index]);
    }
    else if(option == 8){
        modifyGameOption(cout, 1);
        modifyGameOption(cout, 2);
        modifyGameOption(cout, 3);
        modifyGameOption(cout, 4);
        modifyGameOption(cout, 5);
        modifyGameOption(cout, 6);
        modifyGameOption(cout, 7);
    }


}
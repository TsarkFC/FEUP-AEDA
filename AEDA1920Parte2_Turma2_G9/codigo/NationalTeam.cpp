//
// Created by tiago on 06/11/2019.
//

#include "NationalTeam.h"
#include "Exceptions.h"
#include <algorithm>
#include <fstream>

using namespace std;


NationalTeam::NationalTeam() : coaches(Coach())  {
    readNationalTeam("NationalTeam.txt");
}

bool NationalTeam::readPeople(string fileName) {
    string text;
    string id;
    ifstream peopleFile;
    Date birthday = Date();
    peopleFile.open("..//Files//" + fileName);
    if (peopleFile.fail()) {
        cerr << "Error Opening File";
        return false;
    } else {
        while (!peopleFile.eof()) {
            getline(peopleFile, text);
            if (text == "Football Player") {
                FootballPlayer *player = new FootballPlayer();
                player->read(&peopleFile);
                people.push_back((player));
                players.push_back(player);
                getline(peopleFile, text);
            } else if (text == "Technician") {
                Technician *technician = new Technician();
                technician->read(&peopleFile);
                people.push_back((technician));
                technicians.push_back(technician);
                technician_table.addItem(technician);
                getline(peopleFile, text);
            } else if (text == "Coach"){
                Coach * coach = new Coach();
                coach->read(&peopleFile);
                if (coach->getIsWorking()) currentCoach = coach;
                //people.push_back(coach);
                coaches.insert(*coach);
                getline(peopleFile, text);
            }
        }
    }

    peopleFile.close();

    return true;
}

void NationalTeam::read(string peopleFile, string callUpFile, string gameFile, string statisticsFile, string providersFile) {
    readPeople(peopleFile);
    readGames(gameFile);
    readCallUp(callUpFile);
    readGameStatistics(statisticsFile);
    readProviders(providersFile);
}

bool NationalTeam::readNationalTeam(string fileName) {
    string text;
    ifstream teamFile;
    teamFile.open("..//Files//" + fileName);
    if (teamFile.fail()) {
        cerr << "Error Opening National Team File";
        return false;
    } else {
        getline(teamFile, text);
        callUpFile = text;
        getline(teamFile, text);
        gameFile = text;
        getline(teamFile, text);
        peopleFile = text;
        getline(teamFile, text);
        statisticsFile = text;
        getline(teamFile, text);
        providersFile = text;
    }
    teamFile.close();
    read(peopleFile, callUpFile, gameFile, statisticsFile, providersFile);
    return true;
}

/*bool NationalTeam::savePeople(string fileName) {
    ofstream content("..//Files//" + fileName);
    for (int i = 0; i < people.size(); ++i) {
        people[i]->printToFile(content);
        content << "::::::::::" << endl;
    }
    BSTItrIn<Coach> it(coaches);{
        while (!it.isAtEnd()){
            it.retrieve().printToFile(content);
            it.advance();
            content << "zas";
        }
    }
    content.close();
    return true;
}*/

bool NationalTeam::idComparable(const Person *person1, const int id) {
    return (person1->getId() < id);
}

bool NationalTeam::idComparablePeople(const Person *person1, const Person *person2) {
    return (person1->getId() < person2->getId());
}

bool NationalTeam::nameComparable(const Person* person1, const Person* person2){
    return (person1->getName() < person2->getName());	    return (person1->getName() < person2->getName());
}

void NationalTeam::sortByName(vector<Person *> &people) {
    sort(people.begin(),people.end(),nameComparable);
}

void NationalTeam::sortByID(vector<Person *> &people) {
    sort(people.begin(),people.end(),idComparablePeople);
}

vector<Person *> NationalTeam::searchByName(vector<Person *> people, string name) {

    vector<Person *> peopleName;
    for (int i = 0; i < people.size(); ++i) {
        if (people[i]->getName() == name) {
            peopleName.push_back(people[i]);
        }
    }
    return peopleName;

}



Game *NationalTeam::getGameWithID(int id) {
    for (auto i = games.begin(); i != games.end(); i++) {
        if ((*i)->getId() == id) return *i;
    }
    throw InexistentId(id);
}

CallUp *NationalTeam::getCallUpWithID(int id) {
    for (auto i = callUps.begin(); i != callUps.end(); i++) {
        if ((*i)->getId() == id) {return *i;}
    }
    throw InexistentId(id);
}

bool NationalTeam::searchCallUpByID(const int &id) {
    bool check = false;
    for (auto i = callUps.begin(); i != callUps.end(); i++) {
        if ((*i)->getId() == id) check = true;
    }

    if (!check) throw InexistentId(id);

    return check;
}

//DELETE CALL UP
void NationalTeam::deleteCallUp(int id) {
    for (auto i = callUps.begin(); i != callUps.end(); i++) {
        if ((*i)->getId() == id) {
            callUps.erase(i);
            return;
        }
    }
}

//READ FROM TEXT FILE
bool NationalTeam::readCallUp(string file) {

    ifstream callUpFile;
    callUpFile.open("..//Files//" + file);

    if (callUpFile.fail()) {
        cerr << "Error Opening File";
        return false;
    }

    //READ FROM FILE VARIABLES
    string text;
    vector<int> game_indexes;

    //VARIABLES TO CONSTRUCT CALLUP
    int callUpId = 0;
    Date begginingDate, endingDate;
    float dailyCost;
    vector<Game *> callUpGames;
    vector<CallUpPlayerStatistics *> playerStatistics;

    //VARIABLES TO CONSTRUCT CALLUPPLAYERSTATISTICS
    int playerID;
    Date begDate, endDate;

    unsigned int counter = 0;

    while (getline(callUpFile, text)) {

        //ID
        if (counter == 0) {
            callUpId = stoi(text);
        }

        //BEGINNING DATE
        if (counter == 1) {
            begginingDate = begginingDate.dateTextConverter(text);
        }

        //END DATE
        if (counter == 2) {
            endingDate = endingDate.dateTextConverter(text);
        }

        //DAILY COST
        if (counter == 3) {
            dailyCost = stof(text);
        }

        //VECTOR OF GAMES
        if (counter == 4) {
            game_indexes = separateCharacterInt(text, ',');
            insertionSort(game_indexes);

            for (auto j = game_indexes.begin(); j < game_indexes.end(); j++) {
                callUpGames.push_back(getGameWithID(*j));
            }


        }
        //CALLUP PLAYER STATISTICS VECTOR
        if (counter == 5) {

            while (getline(callUpFile, text)) {
                if (text == "::::::::::") break;
                playerID = stoi(text);

                getline(callUpFile, text);
                begDate = begDate.dateTextConverter(text);

                getline(callUpFile, text);
                endDate = endDate.dateTextConverter(text);

                playerStatistics.push_back(new CallUpPlayerStatistics(playerID, begDate, endDate));
            }
            counter = -1;
            callUps.push_back(new CallUp(callUpId, dailyCost, callUpGames, playerStatistics, begginingDate, endingDate));
            callUpGames = {};
            playerStatistics = {};
        }
        counter++;
    }
    callUpFile.close();
    return true;
}


//HANDLE COSTS
//player costs
float NationalTeam::playerCostCalculator(Date d1, Date d2, int playerID) {

    //save pass value - wre assumed 1% of the pass value as current player's value has astronomical values
    float pass = players[searchByID(players, playerID)]->getPassValue() * 0.01;

    //variable that sums the costs associated with this player
    float val = 0;

    //postition of player in data base vector
    int playerPos;

    //Date variables used in loops
    Date beg, end;

    //iterates over different call ups
    for (auto i = callUps.begin(); i < callUps.end(); i++) {

        //iterates over the players that were in that call up
        for (auto j = 0; j < (*i)->getPlayerStatistics().size(); j++) {

            playerPos = searchByID(players, (*i)->getPlayerStatistics()[j]->getPlayerID());

            if ((*i)->getPlayerStatistics()[j]->getPlayerID() == playerID) {

                beg = (*i)->getPlayerStatistics()[j]->getBegDate();
                end = (*i)->getPlayerStatistics()[j]->getEndDate();

                //found player in this call up
                //checking number of days player was in call up between the given days

                if (d1 <= beg && d2 >= end) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (end.dateToDays() - beg.dateToDays()) * 3 * (*i)->getDailyCost();
                    } else val += pass * (end.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost();
                } else if (d1 <= beg) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (d2.dateToDays() - beg.dateToDays()) * 3 * (*i)->getDailyCost();
                    } else val += pass * (d2.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost();
                } else if (d2 >= end) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (end.dateToDays() - d1.dateToDays()) * 3 * (*i)->getDailyCost();
                    } else val += pass * (end.dateToDays() - d1.dateToDays()) * (*i)->getDailyCost();
                } else if (d1 >= beg && d2 <= end) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (d2.dateToDays() - d1.dateToDays()) * 3 * (*i)->getDailyCost();
                    } else val += pass * (d2.dateToDays() - d1.dateToDays()) * (*i)->getDailyCost();
                }
            }
        }
    }
    return val;
}

float NationalTeam::teamCostCalculator(Date d1, Date d2) {
    float val = 0;
    float pass;

    //Date variables used in loops
    Date beg, end;

    //Variable to get player position in palyer vector
    int playerPos;

    //iterates over different call ups
    for (auto i = callUps.begin(); i < callUps.end(); i++) {

        //iterates over the players that were in that call up
        for (auto j = 0; j < (*i)->getPlayerStatistics().size(); j++) {

            playerPos = searchByID(players, (*i)->getPlayerStatistics()[j]->getPlayerID());

            pass = players[playerPos]->getPassValue() * 0.01;

            beg = (*i)->getPlayerStatistics()[j]->getBegDate();
            end = (*i)->getPlayerStatistics()[j]->getEndDate();

            //checking number of days player was in call up between the given days
            if (d1 <= beg && d2 >= end) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (end.dateToDays() - beg.dateToDays()) * 3 * (*i)->getDailyCost();
                } else val += pass * (end.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost();
            } else if (d1 <= beg) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (d2.dateToDays() - beg.dateToDays()) * 3 * (*i)->getDailyCost();
                } else val += pass * (d2.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost();
            } else if (d2 >= end) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (end.dateToDays() - d1.dateToDays()) * 3 * (*i)->getDailyCost();
                } else val += pass * (end.dateToDays() - d1.dateToDays()) * (*i)->getDailyCost();
            } else if (d1 >= beg && d2 <= end) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (d2.dateToDays() - d1.dateToDays()) * 3 * (*i)->getDailyCost();
                } else val += pass * (d2.dateToDays() - d1.dateToDays()) * (*i)->getDailyCost();
            }
        }
    }
    return val;
}

float NationalTeam::staffCostCalculator(Date d1, Date d2) {
    float costs = 0;
    float date_difference;
    float no_months;
    //iterate over technicians menu
    for (auto i = technicians.begin(); i != technicians.end(); i++) {
        //GET DATE DIFERENCE IN DAYS - setting an average of 30.44 days per month
        no_months = (d2.dateToDays() - d1.dateToDays()) / 30.44;
        costs += no_months * (*i)->getSalary();
    }

    return costs;
}

float NationalTeam::playerCostCalculatorMonth(int monthNumber, int yearNumber, int pID) {
    //save pass value - wre assumed 1% of the pass value as current player's value has astronomical values
    float pass = players[searchByID(players, pID)]->getPassValue() * 0.01;

    //variable that sums the costs associated with this player
    float val = 0;

    //Date variables used in loops
    Date beg, end;

    //Variable to get player position in palyer vector
    int playerPos;

    //iterates over different call ups
    for (auto i = callUps.begin(); i < callUps.end(); i++) {

        //iterates over the players that were in that call up
        for (auto j = 0; j < (*i)->getPlayerStatistics().size(); j++) {

            playerPos = searchByID(players, (*i)->getPlayerStatistics()[j]->getPlayerID());

            if ((*i)->getPlayerStatistics()[j]->getPlayerID() == pID) {
                //found player in this call up
                beg = (*i)->getPlayerStatistics()[j]->getBegDate();
                end = (*i)->getPlayerStatistics()[j]->getEndDate();

                if (beg.getMonth() == monthNumber && end.getMonth() == monthNumber && beg.getYear() == yearNumber &&
                    end.getYear() == yearNumber) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (end.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost() * 3;
                    } else val += pass * (end.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost();
                } else if (beg.getMonth() == monthNumber && end.getYear() == yearNumber) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (beg.daysInMonth(monthNumber, yearNumber) - beg.getDay()) * (*i)->getDailyCost() *
                               3;
                    } else
                        val += pass * (beg.daysInMonth(monthNumber, yearNumber) - beg.getDay()) * (*i)->getDailyCost();
                } else if (end.getMonth() == monthNumber && end.getYear() == yearNumber) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (end.getDay()) * (*i)->getDailyCost() * 3;
                    } else val += pass * (end.getDay()) * (*i)->getDailyCost();
                } else if (((beg.getMonth() <= monthNumber && beg.getYear() == yearNumber) ||
                            (beg.getYear() == yearNumber)) &&
                           ((end.getMonth() >= monthNumber && end.getYear() == yearNumber) ||
                            (end.getYear() == yearNumber))) {
                    if (players[playerPos]->isInjury()) {
                        val += pass * (beg.daysInMonth(monthNumber, yearNumber)) * (*i)->getDailyCost() * 3;
                    } else val += pass * (beg.daysInMonth(monthNumber, yearNumber)) * (*i)->getDailyCost();
                }
            }
        }
    }
    return val;
}

float NationalTeam::teamCostCalculatorMonth(int monthNumber, int yearNumber) {
    //save pass value - wre assumed 1% of the pass value as current player's value has astronomical values
    float pass;

    //variable that sums the costs associated with this player
    float val = 0;

    //Date variables used in loops
    Date beg, end;

    //postition of player in data base vector
    int playerPos;

    //iterates over different call ups
    for (auto i = callUps.begin(); i < callUps.end(); i++) {

        //iterates over the players that were in that call up
        for (auto j = 0; j < (*i)->getPlayerStatistics().size(); j++) {

            //found player in this call up
            beg = (*i)->getPlayerStatistics()[j]->getBegDate();
            end = (*i)->getPlayerStatistics()[j]->getEndDate();

            playerPos = searchByID(players, (*i)->getPlayerStatistics()[j]->getPlayerID());

            pass = players[playerPos]->getPassValue() * 0.01;

            if (beg.getMonth() == monthNumber && end.getMonth() == monthNumber && beg.getYear() == yearNumber &&
                end.getYear() == yearNumber) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (end.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost() * 3;
                } else val += pass * (end.dateToDays() - beg.dateToDays()) * (*i)->getDailyCost();

            } else if (beg.getMonth() == monthNumber && end.getYear() == yearNumber) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (beg.daysInMonth(monthNumber, yearNumber) - beg.getDay()) * (*i)->getDailyCost() * 3;
                } else val += pass * (beg.daysInMonth(monthNumber, yearNumber) - beg.getDay()) * (*i)->getDailyCost();
            } else if (end.getMonth() == monthNumber && end.getYear() == yearNumber) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (end.getDay()) * (*i)->getDailyCost() * 3;
                } else val += pass * (end.getDay()) * (*i)->getDailyCost();
            } else if ((beg.getMonth() <= monthNumber && beg.getYear() <= yearNumber) &&
                       ((end.getMonth() >= monthNumber && end.getYear() >= yearNumber))) {
                if (players[playerPos]->isInjury()) {
                    val += pass * (beg.daysInMonth(monthNumber, yearNumber)) * (*i)->getDailyCost() * 3;
                } else val += pass * (beg.daysInMonth(monthNumber, yearNumber)) * (*i)->getDailyCost();
            }
        }
    }
    return val;
}

float NationalTeam::staffCostCalculatorMonth(int monthNumber) {
    float costs;
    for (auto i = technicians.begin(); i != technicians.end(); i++) {
        costs += (*i)->getSalary();
    }
    return costs;
}

bool NationalTeam::readGames(string filename) {
    string text;
    ifstream gamesFile;
    vector<int> splited_int_string;
    vector<string> splited_str_string;
    gamesFile.open("..//Files//" + filename);


    if (gamesFile.fail()) {
        cerr << "Error Opening File";
        return false;
    } else {
        while (!gamesFile.eof()) {
            vector<FootballPlayer *> nationalTeamPlayers;
            Game *game = new Game();

            getline(gamesFile, text);
            game->setCity(text);

            getline(gamesFile, text);
            game->setCountry(text);

            getline(gamesFile, text);
            game->setStadium(text);

            getline(gamesFile, text);
            game->setGameTitle(text);

            getline(gamesFile, text);
            splited_int_string = separateCharacterInt(text, ',');

            getline(gamesFile, text);
            splited_int_string = separateCharacterInt(text, ',');
            for (int i = 0; i < splited_int_string.size(); i++) {
                nationalTeamPlayers.push_back(this->players[splited_int_string[i] - 1]);
            }

            game->setNationalPlayers(nationalTeamPlayers);

            getline(gamesFile, text);
            splited_str_string = separateCharacterStr(text, ',');
            game->setEnemyPlayers(splited_str_string);

            getline(gamesFile, text);
            splited_str_string = separateCharacterStr(text, ',');
            game->setReferees(splited_str_string);

            getline(gamesFile, text);

            games.push_back(game);
        }

        gamesFile.close();

        return true;
    }
}

Coach NationalTeam::searchCoachById(BST<Coach> coaches, int id) {
    BSTItrIn<Coach> it(coaches);
    while(!it.isAtEnd()){
        if(it.retrieve().getId() == id){
            return it.retrieve();
        }
        it.advance();
    }
    throw InexistentId(id);
}

void NationalTeam::setCurrentCoach(Coach &coach){
    coaches.remove(*currentCoach);
    currentCoach->setIsWorking(false);
    coaches.insert(*currentCoach);
    coaches.remove(coach);
    coach.setIsWorking(true);
    coaches.insert(coach);
    *currentCoach = coach;
}

Technician * NationalTeam::searchTechById(int id) {

    for(int i = 0; i < technicians.size(); i++){
        if(technicians[i]->getId() == id){
            return technicians[i];
        }
    }
    throw InexistentId(id);

}

bool NationalTeam::readGameStatistics(string filename) {
    //VARIABLES TO READ FILE
    ifstream statsFile;
    statsFile.open("..//Files//" + filename);
    string text;

    if (statsFile.fail()) {
        cerr << "Error Opening File";
        return false;
    }


    int gameID;

    while (!statsFile.eof()) {

        getline(statsFile, text);
        gameID = stoi(text);
        vector<PlayerGameStatistics> stats = {};

        while (text != "::::::::::") {
            PlayerGameStatistics statistics;

            getline(statsFile, text);
            statistics.setPlayerID(stoi(text));

            getline(statsFile, text);
            statistics.setNumberOfGoals(stoi(text));

            getline(statsFile, text);
            statistics.setMinutesPlayed(stoi(text));

            getline(statsFile, text);
            statistics.setKilometers(stoi(text));

            getline(statsFile, text);
            statistics.setNumberOfPasses(stoi(text));

            getline(statsFile, text);
            statistics.setNumberOfYellowCards(stoi(text));

            getline(statsFile, text);
            statistics.setNumberOfRedCards(stoi(text));

            getline(statsFile, text);

            stats.push_back(statistics);
        }

        games[gameID - 1]->setPlayerStatistics(stats);
    }


    statsFile.close();
    return true;
}

bool NationalTeam::readProviders(string providersFile) {
    ifstream provFile;
    provFile.open("..//Files//" + providersFile);
    string text;

    string name;
    float reputation;
    vector<string> equipement;

    while(!provFile.eof()){
        getline(provFile, text);
        name = text;

        getline(provFile, text);
        reputation = stof(text);

        while(true){
            getline(provFile, text);
            if (text == "::::::::::") break;
            equipement.push_back(text);
        }
        Providers provider(name, reputation, equipement);
        equipement = {};
        providers.push(provider);
    }

    provFile.close();
    return true;
}

Providers NationalTeam::getProvider(string equipement) {
    priority_queue<Providers> copy = providers;
    vector<string> temp;

    while (!copy.empty()){
        Providers p = copy.top();
        copy.pop();

        temp = p.getEquipement();

        if (find(temp.begin(),temp.end(), equipement) != temp.end()){
            return p;
        }
    }
    throw EquipementDontExist(equipement);
}

void NationalTeam::showAllProvidersName() {
    priority_queue<Providers> copy = providers;
    int counter = 0;

    while (!copy.empty()){
        counter ++;

        Providers p = copy.top();
        copy.pop();

        cout << left << setw(67) << setfill(' ') << p.getName();
        cout << "[" << counter << "]" << endl;
    }
}

vector<string> NationalTeam::getAvailableEquipement() {
    vector<string> equipement;
    priority_queue<Providers> copy = providers;

    while (!copy.empty()){
        Providers p = copy.top();
        copy.pop();

        for (auto str:p.getEquipement()){
            if (find(equipement.begin(), equipement.end(), str) == equipement.end()) equipement.push_back(str);
        }
    }
    return equipement;
}

void NationalTeam::showAvailableEquipement(vector<string> equipement) {
    int counter = 0;
    for (auto str : equipement) {
        counter++;
        cout << left << setw(30) << setfill(' ') << str;
        cout << left << setw(10) << setfill(' ') << "(" + getProvider(str).getName() + ":";
        cout << left << setw(27) << setfill(' ') << "reputation = " + to_string(int(getProvider(str).getReputation() + 0.5)) + ")";
        cout << "[" << counter << "]" << endl;
    }
}


//Exists the program and saves the information to new files
void
NationalTeam::saveAndExit(string peepzFile, string callupFileName, string gamesFileName, string statisticsFileName, string providersFileName) {
    string content;
    //SEND PEOPLE INFORMATION TO FILE
    ofstream peopleFile("../Files/" + peepzFile);

    for (int i = 0; i < people.size(); i++) {
        people[i]->printToFile(peopleFile);
        peopleFile << endl;
        //if (i != people.size() - 1) peopleFile << endl;
    }
    BSTItrIn<Coach> it(coaches);
    while (!it.isAtEnd()){
        it.retrieve().printToFile(peopleFile);
        peopleFile << endl;
        it.advance();

    }

    peopleFile.close();

    //SEND GAME INFORMATION TO FILE
    ofstream gameFile("../Files/" + gamesFileName);

    for (int i = 0; i < games.size(); i++) {
        games[i]->printIntoFile(gameFile);

        if (i != games.size() - 1) {
            gameFile << "::::::::::" << endl;
        }
        else gameFile << "::::::::::";
    }

    gameFile.close();

    //SEND CALL UP INFORMATION TO FILE
    ofstream callupFile("../Files/" + callupFileName);

    for (int i = 0; i < callUps.size(); i++) {
        callUps[i]->printIntoFile(callupFile);
        if (i != callUps.size() - 1) callupFile << endl;
    }

    callupFile.close();

    //SEND STATISTICS TO FILE
    ofstream statisticsFile("../Files/" + statisticsFileName);

    for (int i = 0; i < games.size(); i++) {
        statisticsFile << games[i]->getId() << endl;

        for (int j = 0; j < games[i]->getPlayerStatistics().size(); j++) {
            games[i]->getPlayerStatistics()[j].printIntoFile(statisticsFile);

            if (j != games[i]->getPlayerStatistics().size() - 1) statisticsFile << "---------" << endl;
            else if (i == games.size() - 1) statisticsFile << "::::::::::";
            else statisticsFile << "::::::::::" << endl;
        }
    }

    statisticsFile.close();

    //SEND PROVIDERS TO FILE
    ofstream providerFile("../Files/" + providersFileName);

    while (!providers.empty()){
        Providers p = providers.top();
        providers.pop();

        providerFile << p.getName() << endl << p.getReputation() << endl;

        for (auto j = 0; j < p.getEquipement().size(); j++){
            providerFile << p.getEquipement().at(j) << endl;
        }
        if(!providers.empty()) providerFile << "::::::::::" << endl;
        else providerFile << "::::::::::";
    }

    providerFile.close();

    exit(0);
}







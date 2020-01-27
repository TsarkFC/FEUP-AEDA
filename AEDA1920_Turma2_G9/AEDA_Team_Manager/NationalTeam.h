//
// Created by tiago on 06/11/2019.
//

#ifndef AEDA_TEAM_MANAGER_NATIONALTEAM_H
#define AEDA_TEAM_MANAGER_NATIONALTEAM_H


#include <vector>
#include <string>
#include <sstream>
#include "Date.h"
#include "People//Person.h"
#include "People//FootballPlayer.h"
#include "People//Technician.h"
#include "CallUp.h"
#include "Exceptions.h"


class NationalTeam {
protected:
    /**
     * Vector contaning all people
     */
    vector<Person*> people;
    /**
     * Vector containing all players
     */
    vector<FootballPlayer*> players;
    /**
     * Vector containing all technicians
     */
    vector<Technician*> technicians;
    /**
     * Vector containing all call ups
     */
    vector<CallUp*> callUps;
    /**
     * Vector containing all games
     */
    vector<Game*> games;
    /**
     * People file name
     */

    string peopleFile;
    /**
     * Game file name
     */
    string gameFile;
    /**
     * Statistics file name
     */
    string statisticsFile;
    /**
     * Call up file name
     */
    string callUpFile;


public:


    NationalTeam();


    /****************************************************
    *******************PEOPLE FUNCTIONS******************
    *****************************************************/

    //Files

    /**
     * @brief Given the name of the file, reads all the
     * people that are in the file
     * it contains both Football Players and Technicians
     * @param fileName Name of the people's file
     * @return true if the file was read successfully
     */
    bool readPeople(string fileName);

    /**
     * @brief Given a file name, it outputs to the file all the information from everyone
     * @param filename - Name of the people's file
     * @return true in case the operation was successfull
     */
    bool savePeople(string filename);


    //Search and Sort

    /**
     * Function used to compare if a id of a person is equal to id
     * @param person1 Person we want to compare
     * @param id to compare
     * @return True if the id of the person is equal to the second argument
     */
    static bool idComparable(const Person *person1, const int id);


    /**
     * Function used to compare if a id of a person is less than id of second person
     * @param person1 fisrt person we want to compare
     * @param second person we want to compare
     * @return True if the id of the person is equal to the second argument
     */
    static bool idComparablePeople(const Person *person1, const Person *person2);

    /**
     * Given a Person* vector and a name, returns all the people with that same name
     * @param people vector with all the people
     * @param name -Name we want to search for
     * @return vector with all the people with that name
     */
    vector<Person *> searchByName(vector<Person *> people, string name);

    /**
     * @brief Given a Object* vector and an id, Returns the Object with that same id
     * This sort uses Binary search since the ids are always ordered
     * @tparam T Template function so it accepts all types that have a unique ID as a menber
     * @param objects vector we want to search
     * @param id - Id we want to search for
     * @return
     */
    template<class T>
    int searchByID(vector<T *> &object, int id) {
        auto it = lower_bound(object.begin(), object.end(), id, idComparable);
        if (it != object.end() && (*it)->getId() == id) return (it - object.begin());
        else throw InexistentId(id);
    }

    /**
     * Function that returns true if person1 name is smaller than person's 2 name
     * @param person1 First person to compare
     * @param person2 second person to compare
     * @return True if person1->name < person2->name
     */
    static bool nameComparable(const Person* person1, const Person* person2);

    /**
     *@brief Given a vector sorts all people by their name
     * @param people vector to order
     */
    void sortByName(vector<Person *> &people);

    void sortByID(vector<Person *> &people);

    //Vector operations

    /**
     * Given a person and a vector of people, it adds that person to the end of the vector
     * @tparam T It can be of any time if R is compatible
     * @tparam R can be of any type if T is compatible
     * @param objects  vector we want to add the object
     * @param object Object we want to add
     * @return true if operation was successfull
     */
    template<class T, class R>
    bool addtoVector(vector<T> &objects, R object) {
        objects.push_back(object);
        return true;
    }

    /**
     * Given a id and a vector of people, it removes the person with the id of the vector
     * @tparam T Of type people or derivatives
     * @param objects  vector we want to remove the object
     * @param id id of the person we want to remove
     * @return true if operation was successfull
     */
    template<class T>
    bool removeById(vector<T> &objects, int id) {
        int index;
        try { index = searchByID(objects, id); }
        catch (InexistentId(index)) {
            cerr << "Tried to remove Person that doesn't exist" << endl;
            return false;
        }
        objects.erase(objects.begin() + index);
        return true;
    }


    /**
     * Given a vector of people, and two people, it sets all the atribbutes
     * from the person to the attributes of the newPerson
     * @tparam T Can be of type people or derivatives
     * @tparam R Can only be of people derivatives
     * @param people vector where we want to modify
     * @param person - person we want to modify
     * @param newPerson - Person with all the new information about the person
     * @return
     */
    template<class T, class R>
    bool modifyPerson(vector<T> &people, R person, R newPerson) {
        try { position(people, person); }
        catch (out_of_range) {
            cerr << "Tried to modify Person that doesn't exist: " << person->getName() << endl;
            return false;
        }
        person->modify(newPerson);
        return true;
    }

    /**
     * Given a person and a vector of people, it returns the position of the person in the vector
     * Uses Bynary search since people vectors are always ordered by the id
     * @tparam T Can be of people or derivatives
     * @tparam R Can only be of people derivatives
     * @param objects vector where we want to search
     * @param object Person we want to search
     * @return Index of the person position in the vector
     */
    template<class T, class R>
    int position(vector<T> &objects, R object) {
        int index = BinarySearch(objects, object);
        if (index == -1) throw out_of_range("Person not in vector");
        return index;
    }

    /****************************************************
    ********************GAMES FUNCTIONS******************
    *****************************************************/

    /**
     * Reads games from file
     * @param file - file name from which games will be read
     * @return - true if read was successful, false otherwise
     */
    bool readGames(string filename);

    /**
     * Reads PlayerGameStatistics from file
     * @param file - file name from which PlayerGameStatistics will be read
     * @return - true if read was successful, false otherwise
     */
    bool readGameStatistics(string filename);

    /**
     * Given a id and a vector of games, it removes the game with the id from the vector
     * @tparam T of type Game or derivatives
     * @param game - Vector we want to remove the object
     * @param id - Id of the object to be removed
     * @return True if it was removed, otherwise false
     */
    template<class T>
    bool removeGame(vector<T> &game, int id) {
        int index;
        try { index = searchGameByID(game, id); }
        catch (InexistentId(index)) {
            cerr << "Tried to remove Game that doesn't exist" << endl;
            return false;
        }
        games.erase(games.begin() + index);
        return true;
    }

    /**
     * Function used to compare if a id of a game is equal to id
     * @param game Game we want to compare
     * @param id to compare
     * @return True if the id of the game is equal to the second argument
     */
    static bool idGameComparable(const Game *game, const int id) {
        return (game->getId() < id);
    }

    /**
     * @brief Given a Game* vector and an id, Returns the game with that same id
     * This sort uses Binary search since the ids are always ordered
     * @param game vector we want to search
     * @param id - Id we want to search for
     * @return
     */
    int searchGameByID(vector<Game *> &game, int id) {
        auto it = lower_bound(game.begin(), game.end(), id, idGameComparable);
        if (it != game.end() && (*it)->getId() == id) return (it - game.begin());
        else throw InexistentId(id);
    }

    /**
     * Function used to compare if a id of a PlayerGameStatistics is equal to id
     * @param stats PlayerGameStatistics we want to compare
     * @param id to compare
     * @return True if the id of the PlayerGameStatistics is equal to the second argument
     */
    static bool idStatsComparable(const PlayerGameStatistics stats, const int id) {
        return (stats.getPlayerID() < id);
    }

    /**
     * @brief Given a PlayerGameStatistics vector and an id, Returns the PlayerGameStatistics
     * with that same id. This sort uses Binary search since the ids are always ordered
     * @param stats vector we want to search
     * @param id - Id we want to search for
     * @return
     */
    int searchStatsByID(vector<PlayerGameStatistics> stats, int id) {
        auto it = lower_bound(stats.begin(), stats.end(), id, idStatsComparable);
        if (it != stats.end() && (*it).getPlayerID() == id) return (it - stats.begin());
        else throw InexistentId(id);
    }





    /****************************************************
    *******************SALARY FUNCTIONS******************
    *****************************************************/



    //Handle costs (sallaries + insurance)
    //player costs
    /**
     * Calculates the expenses with a player with given id, between two dates
     * @param d1 - first date of the interval
     * @param d2 - last date of the interval
     * @param playerID - id of the player whose expenses will be calculated
     * @return - expenses value
     */
    float playerCostCalculator(Date d1, Date d2, int playerID);

    /**
     * Calculates the expenses with a player with given id in a given month
     * @param monthNumber
     * @param yearNumber
     * @param playerID - id of the player whose expenses will be calculated
     * @return - expenses value
     */
    float playerCostCalculatorMonth(int monthNumber, int yearNumber, int playerID);

    //team costs
    /**
     * Calculates the expenses with the whole team, between two dates
     * @param d1 - first date of the interval
     * @param d2 - last date of the interval
     * @return - expenses value
     */
    float teamCostCalculator(Date d1, Date d2);

    /**
     * Calculates the expenses with the whole team in a given month
     * @param monthNumber
     * @param yearNumber
     * @return - expenses value
     */
    float teamCostCalculatorMonth(int monthNumber, int yearNumber);

    //staff costs
    /**
     * Calculates the expenses with whole team and staff, between two dates
     * @param d1 - first date of the interval
     * @param d2 - last date of the interval
     * @return - expenses value
     */
    float staffCostCalculator(Date d1, Date d2);

    /**
     * Calculates the expenses with whole team and staff in a given month
     * @param monthNumber
     * @return
     */
    float staffCostCalculatorMonth(int monthNumber);


    //READ FROM TEXT FILES
    /**
     * Reads all text files information
     * @param peopleFile
     * @param callUpFile
     * @param gameFile
     * @param statisticsFile
     */
    void read(string peopleFile, string callUpFile, string gameFile, string statisticsFile);


    /****************************************************
    *******************HANDLE CALLUPS******************
    *****************************************************/

    //READ FROM FILE
    /**
     * Reads call up from file
     * @param file - file name from which call up will be read
     * @return - true if read was successful, false otherwise
     */
    bool readCallUp(string file);



    //DELETE CALLUP
    /**
     * Deletes call up
     * @param id - id of the call up that will be deleted
     */
    void deleteCallUp(int id);



    //SEARCH CALL UP BY ID
    /**
     * Searches call up with id in data base
     * @param id - id of the call up that will be looked for
     * @return true if call up was found
     */
    bool searchCallUpByID(const int &id);

    //GET GAME AND CALLUP USING ID
    /**
     * Gets game with id from data base
     * @param id - id of the game that will be looked for
     * @return game address
     */
    Game *getGameWithID(int id);

    /**
     * Gets call up with id from data base
     * @param id - id of the call up that will be looked for
     * @return call up address
     * @return call up address
     */
    CallUp *getCallUpWithID(int id);


    /**
     * Saves all the information into the specific files and exits the program
     * @param fileName - name of the file containing the people's information
     * @param callUpFileName - name of the file containing the call up's information
     * @param gamesFileName - name of the file containing the game's information
     * @param statisticsFileName - name of the file containing the PlayerGameStatistics information
     */
    void saveAndExit(string fileName, string callUpFileName, string gamesFileName, string statisticsFileName);

    /**
     * Reads National Team from file
     * @param file - file name from which the National Team will be read
     * @return - true if read was successful, false otherwise
     */
    bool readNationalTeam(string fileName);

    /**
     * Return position of player with id in vector of his statistics in a call up
     * @param stats
     * @param id
     * @return
     */
    int searchCallStatsByID(vector<CallUpPlayerStatistics*> stats, int id) {
        for (auto i = 0;  i < stats.size(); i++){
            if (stats[i]->getPlayerID() == id) return id;
        }
        throw InexistentId(id);
    }


};

#endif //AEDA_TEAM_MANAGER_NATIONALTEAM_H

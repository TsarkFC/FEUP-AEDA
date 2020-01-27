//
// Created by tiago on 07/11/2019.
//

#ifndef AEDA_TEAM_MANAGER_TEST_H
#define AEDA_TEAM_MANAGER_TEST_H
#include <iostream>
#include <sstream>
#include "People//Person.h"
#include "People//FootballPlayer.h"
#include "Date.h"
#include "NationalTeam.h"
#include "Utilities.h"
using namespace std;

//CLASS JUST FOR TESTING


void testPerson(){

    vector<Person*> people;
    vector<Person*> people1;
    Date date(1,1,3000);

    Date birthdayDate(1,2,2018);
    Person *person1 = new Person("John Wick",birthdayDate,100);
    Person *person2 = new Person("Terry Wick",birthdayDate,100);
    Person *footballPlayer = new FootballPlayer("name", date,200,"position", "club",50.0, 20.0, 5.0,false);
    Person *person3 = new Person("Tiago Wick",birthdayDate,200);
    Person *person4 = new Person("Richard Wick",birthdayDate,300);
    Person *person5 = new Person("Bob Wick",birthdayDate,100);
    Person *person6 = new Person("John Wick",birthdayDate,300);
    Person *person7 = new Person("Bob Wick",birthdayDate,200);
    Person *tech = new Technician("John",birthdayDate,100,"Janitor");


    NationalTeam team;

    team.addtoVector(people,person1);
    team.addtoVector(people,person2);
    team.addtoVector(people,person3);
    team.addtoVector(people,person4);
    team.addtoVector(people,person5);
    team.addtoVector(people,person6);

    team.addtoVector(people,footballPlayer);
    team.addtoVector(people,tech);

    //cout << tech;
    //cout << footballPlayer;
    //cout << person1;
    //tech->printNicely(cout);
    //footballPlayer->printNicely(cout);
    //person1->printNicely(cout);

    vector<Person*> p = team.searchByName(people,"Bob Wick");
    //cout << p[0]->getName() << p.size() << endl;


    for (int i = 0; i < people.size(); ++i) {
        //cout << people[i]->getId() << endl;
    }

    //Verify Position Team
    int index = team.position(people,footballPlayer);
    //cout << index << endl;
    //cout << people[index]->type() << endl;
    //cout << people[6]->type() << endl;


    //people[index]->print(cout);
    //cout << people[index];
    //people[index+1]->print(cout);
    //people[index]->print(cout);

}

void testPlayers(){
    NationalTeam n;

    vector<FootballPlayer*> players;
    Date date(1,1,3000);
    Date birthdayDate(1,2,2018);

    FootballPlayer *player1 = new FootballPlayer("name", date,200,"position", "club",50.0, 20.0, 5.0,false);
    FootballPlayer *player2 = new FootballPlayer("John", date,200,"position", "club",50.0, 20.0, 5.0,false);
    FootballPlayer *player3 = new FootballPlayer("Ramalho", date,200,"pos", "club",50.0, 20.0, 5.0,false);
    FootballPlayer *player4 = new FootballPlayer("Diogo", date,200,"position", "club",50.0, 20.0, 5.0,false);
    FootballPlayer *player5 = new FootballPlayer("Tiago", date,200,"position", "club",50.0, 20.0, 5.0,false);
    FootballPlayer *player6 = new FootballPlayer("Terry", date,200,"position", "club",50.0, 20.0, 5.0,false);
    FootballPlayer *player7 = new FootballPlayer("Zas", date,300,"position", "club",40.0, 30.0, 4.0,true);

    n.addtoVector(players, player1);
    n.addtoVector(players, player2);
    n.addtoVector(players, player3);
    n.addtoVector(players, player4);
    n.addtoVector(players, player5);
    n.addtoVector(players, player6);
    n.addtoVector(players, player7);

    for (int i = 0; i < players.size() ; ++i) {
        //players[i]->print(cout);
    }


    //cout << n.personPosition(players, player3) << endl;
    //player1->print(cout);
    n.modifyPerson(players, player1, player3);
    //player3->print(cout);
    //n.removePerson(players, player3);
    //cout << n.personPosition(players, player3) << endl;


}

void testNationalTeam(){

    Date date(1,1,3000);

    NationalTeam team = NationalTeam();
    team.readPeople("Person.txt");

    /***************COMO E QUE E POSSIVEL ESTAR A FUNCIONAR AQUI MAS NAO NO MENU??*********************************/

    //int i = team.askForId();
    //cout << team.searchByID(team.people,i);
    team.savePeople("x.txt");

}

void testExceptions(){

    //Invalid Date
    /*try { Date date = Date(32,1,2000);}
    catch (InvalidDate &a){cout << a.getMessage();
        throw;
    }*/



    vector<Person*> people;
    vector<Person*> people1;
    Date date(1,1,3000);

    Date birthdayDate(1,2,2018);
    Person *person1 = new Person("John Wick",birthdayDate,100);
    Person *person2 = new Person("Terry Wick",birthdayDate,100);
    Person *footballPlayer = new FootballPlayer("name", date,200,"position", "club",50.0, 20.0, 5.0,false);
    Person *person3 = new Person("Tiago Wick",birthdayDate,200);


    NationalTeam team;
    team.addtoVector(people,person1);
    team.addtoVector(people,person2);
    team.addtoVector(people,footballPlayer);

    //Remove Element that doesnt exist
    //team.removePerson(people,person1);
   // team.removePerson(people,person1);



}

#endif //AEDA_TEAM_MANAGER_TEST_H

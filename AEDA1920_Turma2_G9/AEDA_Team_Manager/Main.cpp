#include <iostream>
#include "NationalTeam.h"

#include <windows.h>
#include "display/Menu.h"

using namespace std;

void runTeamManager(){

    Menu menu = Menu();
    menu.runMenu();
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    runTeamManager();

    system("Pause");

    return 0;


}
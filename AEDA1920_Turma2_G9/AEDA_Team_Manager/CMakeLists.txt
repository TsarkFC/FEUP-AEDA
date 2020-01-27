cmake_minimum_required(VERSION 3.10)
project(AEDA_Team_Manager)

set(CMAKE_CXX_STANDARD 11)


add_executable(AEDA_Team_Manager Main.cpp  Date.cpp Date.h People//FootballPlayer.cpp People//FootballPlayer.h Game.cpp Game.h People//Person.cpp People//Person.h People//Technician.cpp People//Technician.h CallUp.cpp CallUp.h PlayerGameStatistics.cpp PlayerGameStatistics.h CallUpPlayerStatistics.h CallUpPlayerStatistics.cpp Utilities.cpp Utilities.h NationalTeam.cpp NationalTeam.h display/Menu.cpp Exceptions.h display/PeopleMenu.cpp display/GameMenu.cpp display/CallUpMenu.cpp display/EconomiesMenu.cpp display/Menu.h)

target_link_libraries(AEDA_Team_Manager)

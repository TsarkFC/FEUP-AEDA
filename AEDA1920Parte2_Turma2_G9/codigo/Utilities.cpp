//
// Created by tiago on 24/10/2019.
//

#include <stdexcept>
#include <iostream>
#include "Utilities.h"
using namespace std;

//String Operations

//Trim
void trimRight(string &s) {
	s.erase(s.find_last_not_of(" ") + 1);
}
void trimLeft(string &s) {
	s.erase(0, s.find_first_not_of(" "));
}
void trim(string &s) {
	trimRight(s);
	trimLeft(s);
}

//Separate a string using a certain char and put it in a int vector
vector<int> separateCharacterInt(string s, char ch) {
	vector<int> vetor;
	if (s == "")
		return vetor;
	while (s.find_first_of(ch) != s.npos) {
		vetor.push_back(stoi(s.substr(0, s.find_first_of(ch))));
		s.erase(0, s.find_first_of(ch) + 1);
	}
	vetor.push_back(stoi(s.substr(0, s.find_first_of(ch))));
	return vetor;
}

//Separate a string using a certain char and put it in a string vector
vector<string> separateCharacterStr(string s, char ch) {
	vector<string> vetor;
	string aux;
	while (s.find_first_of(ch) != s.npos) {
		aux = s.substr(0, s.find_first_of(ch));
		trim(aux);
		vetor.push_back(aux);
		s.erase(0, s.find_first_of(ch) + 1);
	}
	aux = s.substr(0, s.find_first_of(ch));
	trim(aux);
	vetor.push_back(aux);
	return vetor;
}

//Returns true if a string is a number
bool stringIsNumber(string number) {
	int count = 0;
	for (int i = 0; i < number.size(); i++) {
		if (!isdigit(number[i]))
			return false;
	}
	return true;
}


bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
bool isPositiveNumber(int n){
    return n >= 0;
}

void validFloat(string num) {
    try {stof(num);}
    catch (std::invalid_argument ia){ throw;}

}

void validInt(string num) {
    try {stoi(num);}
    catch (std::invalid_argument ia){ throw;}

}

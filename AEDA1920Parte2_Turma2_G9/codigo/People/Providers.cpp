//
// Created by digas on 29/12/2019.
//

#include "Providers.h"


string Providers::getName() const{
    return name;
}

float Providers::getReputation() const {
    return reputation;
}

vector<string> Providers::getEquipement() const {
    return equipement;
}

void Providers::setName(string name) {
    this->name = name;
}

void Providers::setEquipement(vector<string> equipement) {
    this->equipement = equipement;
}

void Providers::setReputation(float reputation) {
    this->reputation = reputation;
}

Providers::Providers(string name, float reputation, vector<string> equipement) {
    this->name = name;
    this->reputation = reputation;
    this->equipement = equipement;
}

bool Providers::operator< (Providers p1) const{
    return (reputation < p1.reputation);
}

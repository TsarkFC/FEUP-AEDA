/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include "Car.h"
using namespace std;

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

//d)
template <class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle){
    /*Esta função deve adicionar ao vector vehicles o argumento vehicle, mas apenas se a garagem não
estiver cheia (membro dado capacity), e se o veículo a adicionar ainda não existir. Se o veículo for
adicionado, a função deve retornar true, senão deve retornar false.*/
    typename vector<Vehicle*>::iterator it;
    bool found = false;

    for (it = vehicles.begin(); it != vehicles.end(); it++){
        if((**it) == *vehicle) found = true;
    }

    if (!found && (vehicles.size() < capacity)){
        vehicles.push_back(vehicle);
        return true;
    }
    else return false;
}

//e)
bool sort_car(const Car* c1, const Car* c2){
    if (c1->getBrand() < c2->getBrand()) return true;
    else if (c1->getBrand() == c2->getBrand()){
        if (c1->getPrice() > c2->getPrice()) return true;
        else return false;
    }
    else return false;
}

template <class Vehicle>
void Garage<Vehicle>::sortVehicles() {
    sort(vehicles.begin(), vehicles.end(), sort_car);
}

//f)
template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model){
    /*Esta função remove do vector vehicles o veículo de marca brand e modelo model, retornando o
elemento removido. No caso de o veículo não existir, a função deve lançar a exceção
NoSuchVehicleException (já fornecida).*/
    typename vector<Vehicle*>::iterator it;
    Vehicle* remove;

    for (it = vehicles.begin(); it != vehicles.end(); it++){
        if (((*it)->getBrand() == brand) && ((*it)->getModel() == model)){
            remove = *it;
            vehicles.erase(it);
            return remove;
        }
    }
    throw NoSuchVehicleException();
}

//g)
class NoSuchBrandException{
    string name;
public:
    NoSuchBrandException(const string& name){
        this->name = name;
    }
    string getBrand() const{
        return name;
    }
};

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const{
    /*Esta função calcula e retorna o preço médio dos veículos de marca brand. No caso de não haver
veículos dessa marca, a função deve lançar uma exceção NoSuchBrandException, a qual deve conter
um membro-dado que é o nome da marca e um membro função de acesso a esse membro-dado,
chamado getBrand.
*/
    typename vector<Vehicle*>::const_iterator it;
    int counter = 0; float total_price = 0;

    for (it = vehicles.begin(); it != vehicles.end(); it++){
        if ((*it)->getBrand() == brand){
            counter++;
            total_price += (*it)->getPrice();
        }
    }
    if (counter == 0) throw NoSuchBrandException(brand);

    return total_price / counter;

}


#endif /* SRC_GARAGE_H_ */

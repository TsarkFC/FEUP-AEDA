#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include "Kart.h"


using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)
bool compareKarts(CKart ck1, CKart ck2){
    if (ck1.getNumero() < ck2.getNumero()) return true;
    else return false;
}

vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
	//get all karts
	for (auto i = pistasG.begin(); i != pistasG.end(); i++){
        for (auto j = (*i).getFrotaActual().begin(); j != (*i).getFrotaActual().end(); j++){
            vord.push_back(*j);
        }
	}

	sort(vord.begin(), vord.end(), compareKarts);
	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    int counter = 0;
    //get all karts
    for (auto i = pistasG.begin(); i != pistasG.end(); i++){
        for (auto j = (*i).getFrotaActual().begin(); j != (*i).getFrotaActual().end(); j++){
            if (j->getAvariado() && cilind == j->getCilindrada()) counter++;
        }
    }
    return counter;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    int counter = 0;
    for (auto i = frotaKartsPista.begin(); i != frotaKartsPista.end(); i++){
        if (!i->getAvariado() && i->getCilindrada() == cilind) {
            kartsLinhaPartida.push(*i);
            counter++;
        }
        if (counter == numeroKarts) return true;
    }
    return false;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    int i = kartsLinhaPartida.size();
    for (int i = 0; i < kartsLinhaPartida.size(); i++){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return i;
}


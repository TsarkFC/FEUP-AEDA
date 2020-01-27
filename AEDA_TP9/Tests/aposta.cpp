#include "aposta.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
	if (find(numeros.begin(), numeros.end(), num) == numeros.end()) return false;
	else return true;
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    /*Considere valores um vetor de m (m>n) valores gerados aleatoriamente. Esta função cria uma aposta que
inclui os primeiros n números não repetidos do vetor valores e guarda esses números na tabela*/

    int count = 0;
    vector<unsigned> rep;

    for (auto i = valores.begin(); i != valores.end(); i++){
        if (find(rep.begin(), rep.end(), *i) == rep.end()){
            count++;
            numeros.insert(*i);
            rep.push_back(*i);
        }
        if (count == n) break;
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned certos = 0;

    for (auto i = sorteio.begin(); i != sorteio.end(); i++){
        if (find(numeros.begin(), numeros.end(), *i) != numeros.end()) certos++;
    }

    return certos;
}






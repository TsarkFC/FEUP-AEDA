#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}
int Frota::numVeiculos() const {
    return veiculos.size();
}
int Frota::menorAno() const {
    if (veiculos.size() == 0) return 0;
    int menor = veiculos[0]->getAno();
    for (size_t i = 1; i < veiculos.size(); i++){
        if (veiculos[i]->getAno() < menor) menor = veiculos[i]->getAno();
    }
    return menor;
}
vector<Veiculo *> Frota::operator () (int anoM) const{
    //Esta função retorna um vetor de apontadores para os veículos cujo ano de matrícula é igual a anoM.
    vector<Veiculo *> v;
    vector<Veiculo *>::const_iterator it = veiculos.begin();

    for (it; it < veiculos.end(); it++){
        if ((*it)->getAno() == anoM) v.push_back(*it);
    }
    return v;
}
float Frota::totalImposto() const {
    vector<Veiculo *>::const_iterator it = veiculos.begin();
    float imposto = 0;

    for (it; it < veiculos.end(); it++){
        imposto += (*it)->calcImposto();
    }
    return imposto;
}

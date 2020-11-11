#include "parque.h"
#include <vector>

using namespace std;

//TEST1
ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : numMaximoClientes(nMaxCli), lotacao(lot) {
    vagas = lot;
}
unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}
unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

//TEST2
int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (size_t i = 0; i < clientes.size(); i++){
        if (clientes[i].nome == nome){
            return i;
        }
    }
    return -1;
}
bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size() == numMaximoClientes) return false;
    if (posicaoCliente(nome) == -1) return false;
    InfoCartao info;
    info.nome = nome;
    info.presente = false;
    clientes.push_back(info);
    return true;
}

//TEST3
bool ParqueEstacionamento::entrar(const string &nome){
    //vagas
    if (vagas == 0) return false;
    if (posicaoCliente(nome) == -1) return false;
    int pos = posicaoCliente(nome);
    if (clientes[pos].presente == true) return false;
    return false;
}

//TEST4
bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int pos = posicaoCliente(nome);
    if (clientes[pos].presente == true) return false;
    clientes.erase(clientes.begin() + pos);
    return true;
}

//TEST5
bool ParqueEstacionamento::sair(const string &nome) {
    if (posicaoCliente(nome) == -1) return false;
    int pos = posicaoCliente(nome);
    if (clientes[pos].presente) return false;
    return true;
}

//TEST6
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}
unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}
#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    numPresentes = rand() % 5 + 1;
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    clientes_atendidos = 0;
    tempo_atual = 0;
    prox_chegada = rand() % 20 + 1;
    prox_saida = 0;
}

//a alterar
void Balcao:: proximoEvento(){
    if (tempo_atual < prox_chegada) chegada();
    else saida();
}

//a alterar
void Balcao::chegada(){
    Cliente* c = new Cliente();
    clientes.push(*c);

    prox_chegada = rand() % 20 + 1;

    if (clientes.size() == 0) prox_saida = tempo_atual + c->getNumPresentes() * tempo_embrulho;
    else prox_saida = c->getNumPresentes() * tempo_embrulho;

}

//a alterar
void Balcao::saida(){
    if (clientes.size() == 0) throw FilaVazia();

    Cliente c = getProxCliente();

    clientes.pop();

    prox_saida = c.getNumPresentes() * tempo_embrulho;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
queue<Cliente> Balcao::getClientes() const {
    return clientes;
}

ostream & operator << (ostream & out, const Balcao & b1)
{
    out << "Clientes atendidos: " << b1.getClientesAtendidos() << endl;
    out << "Clientes em espera: " << b1.getClientes().size() << endl;
    return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    Cliente *c = new Cliente();
    clientes_atendidos++;

    if (clientes.size() == 0) throw FilaVazia();

    *c = clientes.front();
    return *c;
}


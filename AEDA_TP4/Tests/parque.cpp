#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

class ClienteNaoExistente;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    //que retorna o índice do cliente de nome "nome" no vetor clientes. Se o cliente não existir, retorna -1
    for (size_t i = 0; i < clientes.size(); i++){
        if (clientes[i].nome == nome) return i;
    }
    return -1;
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    if (posicaoCliente(nome) == -1) throw (ClienteNaoExistente(nome));
    else{
        return (clientes[posicaoCliente(nome)].frequencia);
    }
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[posicaoCliente(nome)].frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(), clientes.end(), name_compare);
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;

    ordenaClientesPorFrequencia();

    for (size_t i = 0; i < clientes.size(); i++){
        if (clientes[i].frequencia >= n1 && clientes[i].frequencia <= n2) nomes.push_back(clientes[i].nome);
    }

    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    /*Deve imprimir no monitor informação sobre todos os clientes registados, mostrando o nome do cliente, se
    está presente ou não no parque e o número de vezes que utilizou o parque.
            Implemente também o membro-função:
    InfoCartao ParqueEstacionamento::
    getClienteAtPos(vector<InfoCartao>::size_type p) const
    que retorna o cliente (InfoCartao) existente no índice p do vetor clientes. Se não existir tal cliente, lança
    uma exceção do tipo PosicaoNaoExistente.
            Implemente a classe PosicaoNaoExistente e note que o tratamento desta exceção efetua uma chamada ao
    membro-função getValor() que deve retornar a posição do vetor inválida que originou a exceção.*/
    for (size_t i = 0; i < pe.getClientes().size(); i++){
        os << "Nome: " << pe.getClientes()[i].nome << endl;
        os << "Frequencia: " << pe.getClientes()[i].frequencia << endl;
        os << "Presente: " << pe.getClientes()[i].presente << endl;
    }

    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    if (p > clientes.size() || p < 0) throw(PosicaoNaoExistente(p));
    info.nome = clientes[p].nome;
    info.frequencia = clientes[p].frequencia;
    info.presente = clientes[p].presente;
    return info;
}

bool InfoCartao::operator<(const InfoCartao &cliente) const {
    if (frequencia > cliente.frequencia) return true;
    else if (frequencia < cliente.frequencia) return false;
    else if (nome < cliente.nome) return true;
    return false;
}

bool name_compare(InfoCartao n1, InfoCartao n2){
    return n1.nome < n2.nome;
}




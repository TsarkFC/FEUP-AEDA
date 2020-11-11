#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap)
{
    apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;

	for (auto ap : apostas){
	    if (find(ap.getNumeros().begin(), ap.getNumeros().end(), num) != ap.getNumeros().end()) count ++;
	}

	return count;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
    /*Esta função retorna uma tabela de dispersão contendo as apostas do jogador que são premiadas (isto é,
aquelas que possuem mais de 3 valores iguais aos valores de sorteio*/

	tabHAposta money;
	for (auto ap : apostas){
	    if (ap.calculaCertos(sorteio) > 3) money.insert(ap);
	}
	return money;
}

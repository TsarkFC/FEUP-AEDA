/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo()
{
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    return criancas;
}

// a implementar
string Jogo::escreve() const
{
    string res;
    list<Crianca>::const_iterator it = criancas.begin();

    for (it; it != criancas.end(); it++){
        res += (*it).getNome() + " : " + to_string((*it).getIdade()) + "\n";
    }
    return res;

}

// a implementar
Crianca& Jogo::perdeJogo(string frase)
{
    int count = 0;
    list<Crianca>::const_iterator it = criancas.begin();
    int id;
    while (criancas.size() != 1){
        id = (numPalavras(frase)-1) % criancas.size();
        it = criancas.begin();

        while (count < id) {
            it++;
            count++;
        }

        count = 0;
        criancas.erase(it);
    }
    return (*criancas.begin());
}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    /*Esta função remove do jogo as crianças de idade superior ao valor id especificado como parâmetro, e retorna
uma nova lista com as crianças que foram removidas*/

    list<Crianca> res;
    list<Crianca>::const_iterator it = criancas.begin();

    for (it; it != criancas.end(); it ++){
        if ((it)->getIdade() > id){
            criancas.erase(it);
            res.push_back(*it);
        }
    }

    return res;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    list<Crianca>::const_iterator it = l1.begin();
    for (it; it != l1.end(); it++){
        criancas.push_back(*it);
    }
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
    /*list<Crianca>::const_iterator it1 = criancas.begin();
    list<Crianca>::const_iterator it2 = j2.getCriancasJogo().begin();

    if (criancas.size() != j2.getCriancasJogo().size()) return false;

    while(it1 != criancas.end()){
        if ((*it1) == (*it2)) {
            it2++;
            it1++;
        }
        else return false;
    }
	return true;*/
    return (criancas == j2.getCriancasJogo());
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    srand(time(NULL));
    list<Crianca> res;
    list<Crianca>::const_iterator it;
    list<Crianca>::const_iterator move;

    int pos; bool check = true;

    while (res.size() != criancas.size()) {
        it = criancas.begin();

        pos = rand() % (criancas.size());
        advance(it, pos);

        move = res.begin();
        while (move != res.end()) {
            if (*it == *move) {
                check = true;
            }
            move++;
        }
        if (!check) res.push_back(*it);
        check = false;
    }
    return res;
}

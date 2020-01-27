#include "jogo.h"
#include <sstream>


//a alterar
ostream &operator << (ostream &os, Circulo &c1)
{
	return os;
}


//a alterar
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo = iniciaJogo(0, niv, pontos, estados);
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados){
    Circulo c(pontos[pos], estados[pos]);
    if (niv == 0) return BinaryTree<Circulo>(c);
    BinaryTree<Circulo> left = iniciaJogo(2*pos+1, niv-1, pontos, estados);
    BinaryTree<Circulo> right = iniciaJogo(2*pos+2, niv-1, pontos, estados);
    return BinaryTree<Circulo>(c,left,right);
}

//a alterar
string Jogo::escreveJogo()
{
    BTItrLevel<Circulo> bt(jogo);
    string ret = "";

    while(!bt.isAtEnd()){
         ret += to_string(bt.retrieve().getPontuacao()) + "-";
         if (bt.retrieve().getEstado()) ret += "true-";
         else ret += "false-";
         ret += to_string(bt.retrieve().getNVisitas()) + "\n";
         bt.advance();
    }
	return ret;
}

//a alterar
int Jogo::jogada()
{
    BTItrLevel<Circulo> bt(jogo);
    int pontos = 0;

    while(true){
        Circulo &c = bt.retrieve();
        if (c.getEstado()){
            int i = 0;
            while(i < c.getPontuacao()+1 && !bt.isAtEnd()){
                bt.advance();
                i++;
            }
        }
        else{
            int i = 0;
            while(i < c.getPontuacao() && !bt.isAtEnd()){
                bt.advance();
                i++;
            }
        }
        c.mudaEstado();
        c.incNVisitas();
        pontos = c.getPontuacao();
        if (bt.isAtEnd()) break;
    }
	return pontos;
}


//a alterar
int Jogo::maisVisitado()
{
    int max = 0;
    BTItrLevel<Circulo> c(jogo);

    c.advance();
    while(!c.isAtEnd()){
        if (c.retrieve().getNVisitas() > max) max = c.retrieve().getNVisitas();
        c.advance();
    }
	return max;
}


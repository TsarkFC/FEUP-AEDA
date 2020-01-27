#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return palavra < ps1.getPalavra();
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich)
{
    string word, meaning;

    while(!fich.eof()){
        getline(fich, word);
        getline(fich, meaning);
        PalavraSignificado a(word, meaning);
        palavras.insert(a);
    }
}

//a alterar
string Dicionario::consulta(string palavra) const
{
    BSTItrIn<PalavraSignificado> dic(palavras);
    PalavraSignificado antes("","");
    PalavraSignificado depois("","");
    bool first = true;

    while(!dic.isAtEnd()){
        if (dic.retrieve().getPalavra() == palavra) return dic.retrieve().getSignificado();
        if (dic.retrieve().getPalavra() > palavra && first) throw PalavraNaoExiste(antes, dic.retrieve());
        antes = dic.retrieve();
        dic.advance();
    }
    throw PalavraNaoExiste(antes, depois);
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    /*modifica o significado da palavra para um novo significado indicado no argumento. Se a palavra
para a qual se pretende alterar o significado existir, o método retorna true, senão esta nova palavra é
adicionada ao dicionário e o método retorna false*/

    BSTItrIn<PalavraSignificado> dic(palavras);

    try{
        consulta(palavra);
    }catch (PalavraNaoExiste){
        palavras.insert(PalavraSignificado(palavra, significado));
        return false;
    }

    while(!dic.isAtEnd()){
        if (dic.retrieve().getPalavra() == palavra){
            palavras.remove(PalavraSignificado(dic.retrieve().getPalavra(), dic.retrieve().getPalavra()));
            palavras.insert(PalavraSignificado(palavra, significado));
            return true;
        }
        dic.advance();
    }
    return true;
}

//a alterar
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> dic(palavras);

    while(!dic.isAtEnd()){
        cout << dic.retrieve().getPalavra() << endl;
        cout << dic.retrieve().getSignificado() << endl;
        dic.advance();
    }
}


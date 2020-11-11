#include "caixa.h"
#include <sstream>


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;

// a alterar
bool Objeto::operator<(const Objeto& o1) const {
	return peso != o1.peso ? peso < o1.peso : id < o1.id;
}

// a alterar
bool Caixa::operator<(const Caixa& c1) const {
	return cargaLivre > c1.cargaLivre;
}

// a alterar
string Caixa::imprimeConteudo() const {
    /*retorna uma string contendo o ID da caixa, assim como os respetivos ID e peso dos objetos que a
caixa contém. A string a retornar deve ser da forma “C[<ID> <InfoObj1> <InfoObj2> … ]”.
Consulte o teste para verificar a formatação da string. Note que o operador << já está implementado
na classe Objeto. Caso não existam objetos na caixa, a função retorna a string “Caixa <ID>
vazia!”
*/
    string ret = "";
    stack<Objeto> objs = objetos;

    if (objetos.empty()) ret = "Caixa " + to_string(id) + " vazia!\n";

    else {
        ret += "C" + to_string(id) + "[ ";
        while (!objs.empty()) {
            Objeto o = objs.top();
            objs.pop();

            ret += "O" + to_string(o.getID()) + ": " + to_string(o.getPeso()) + " ";
        }
        ret += "]";
    }

	return ret;
}




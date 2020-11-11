#include "maquinaEmpacotar.h"
#include <sstream>
#include <algorithm>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


// a alterar
bool sort_weight(Objeto o1, Objeto o2){
    if (o1.getPeso() > o2.getPeso()) return false;
    return true;
}

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
    /*que lê de um vetor fornecido os objetos a serem empacotados. Apenas os objetos com peso igual ou
inferior à capacidade das caixas são carregados na máquina. A função retorna o número de objetos
efetivamente carregados na máquina, sendo a paleta (vetor objs) atualizada com a retirada dos objetos
que são carregados. Guarde os objetos na fila de prioridade objetos, ordenando-os por peso (o primeiro
elemento da fila de prioridade é o objeto mais pesado).*/
    unsigned emp = 0;

    vector<Objeto> temp;

    for (auto i = objs.begin(); i != objs.end(); i++){
        if (i->getPeso() <= capacidadeCaixas){
            emp++;
            temp.push_back(*i);
            i = objs.erase(i);
            i--;
        }
    }

    sort(temp.begin(), temp.end(), sort_weight);

    for (auto j = temp.begin(); j != temp.end(); j++){
        objetos.push(*j);
    }

    return emp;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {

    /*Esta função procura na fila de prioridade caixas a próxima caixa com carga remanescente suficiente
para guardar o objeto obj. Se essa caixa existir, retira-a da fila de prioridade e retorna-a. Caso não exista
uma caixa com carga livre suficiente para alojar obj, a máquina usa uma nova caixa para o objeto,
retornando-a.
*/
    vector<Caixa> temp;

    while (!caixas.empty()) {
        Caixa c = caixas.top();
        caixas.pop();

        if (c.getCargaLivre() >= obj.getPeso()) {

            //PUT EVERYTHING BACK IN PRIORITY QUEUE
            for (auto i = 0;  i < temp.size(); i++){
                caixas.push(temp[i]);
            }
            return c;
        }
        else {
            temp.push_back(c);
        }
    }
    //PUT EVERYTHING BACK IN PRIORITY QUEUE
    for (auto i = 0;  i < temp.size(); i++){
        caixas.push(temp[i]);
    }

    Caixa c;
    return c;

}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {
    /*que guarda os objetos da paleta carregada no menor número possível de caixas, e retorna o número de
caixas utilizadas. Considere que inicialmente nenhuma caixa está a ser usada.*/

    while(!objetos.empty()){
        Objeto o = objetos.top();
        objetos.pop();

        Caixa c = procuraCaixa(o);
        c.addObjeto(o);
        caixas.push(c);
    }

	return caixas.size();
}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    /*retorna uma string contendo o ID e respetivo peso dos objetos por empacotar, que estão na fila
    objetos (a informação de cada objeto é separada por \n). Consulte o teste para verificar a formatação da
    string. Note que o operador << já está implementado na classe Objeto. Caso não existam objetos
    para empacotar, a função retorna a string “Nao ha objetos!”*/

    if (objetos.empty()) return "Nao ha objetos!\n";

    priority_queue<Objeto> obj = objetos;
    string ret = "";

    while(!obj.empty()){
        Objeto o = obj.top();
        obj.pop();

        ret += "O" + to_string(o.getID()) + ": " + to_string(o.getPeso()) + "\n";

    }
	return ret;
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
    /* encontra na fila de prioridade caixas aquela que contém o maior número de objetos, retornando-a.
Se não houver caixas na lista, a função lança uma exceção do tipo MaquinaSemCaixas (implementada
na classe MaquinaEmpacotar).*/

    if (caixas.empty()) throw MaquinaSemCaixas();
    int max = 0;

    priority_queue<Caixa> boxes = caixas;
    Caixa ret;

    while (!boxes.empty()){
        Caixa temp = boxes.top();
        boxes.pop();

        if (temp.getSize() > max) {
            ret = temp;
            max = temp.getSize();
        }
    }

	return ret;
}




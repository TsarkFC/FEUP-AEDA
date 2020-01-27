/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
    /*Cria um novo artigo com base nos dados do cliente. O construtor de Article deve ser invocado
passando o membro-dado client da classe Purchase, juntamente com o código de barras barCode. O
argumento present indica se o artigo é um presente (deve atualizar o membro-dado respetivo na
classe Article). O argumento deliverHome indica se o artigo vai ser entregue em casa (deve atualizar
o membro-dado respetivo na classe Article). A função deve retornar o artigo criado.*/

    Article *a = new Article(client, barCode);

    a->setPresent(present);
    a->setDeliverHome(deliverHome);

	return a;
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
    /*que adiciona à lista de sacos de compras do cliente o artigo passado no argumento. Adicionar o artigo
significa colocá-lo no último saco (que é uma pilha) da lista bags. Caso esse saco esteja cheio (ver
Purchase::BAG_SIZE), deve ser adicionado um novo saco à lista, que conterá o artigo.*/

    for (auto i = bags.begin(); i != bags.end(); i++){
        if (i->size() < BAG_SIZE){
            i->push(article);
            return;
        }
    }
    stack<Article*> s;
    s.push(article);

    bags.push_back(s);
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
    /*que retira dos sacos de compras todos os artigos que são presentes. Os restantes artigos devem voltar
a ficar nos sacos onde estavam, pela mesma ordem relativa. Os sacos onde havia presentes deixam
portanto de estar cheios. A função deve retornar um vector com os presentes , na ordem em que foram
encontrados (percorrendo os sacos do início para o fim do vector bags).*/

	vector<Article*> presents;
	vector<Article*> temp;

	for (auto i = bags.begin(); i != bags.end(); i++){
	    while(!i->empty()){
	        if (i->top()->getPresent()) presents.push_back(i->top());
	        else temp.push_back(i->top());
	        i->pop();
	    }
	    //PUT EVERYTHING NON PRESENT BACK (REVERSE ORDER)
	    for (vector<Article*>::reverse_iterator it = temp.rbegin(); it != temp.rend(); it++){
	        i->push(*it);
	    }
	    temp = {};
	}
	return presents;
}


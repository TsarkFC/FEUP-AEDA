#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo();
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};



template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

//excecao ArestaRepetida
template<class N>
class ArestaRepetida{
public:
    N info1; N info2;
    ArestaRepetida(N inf1, N inf2){
        info1 = inf1;
        info2 = inf2;
    }
};
template<class N>
ostream & operator<<(ostream &out, const ArestaRepetida<N> &a){
    out << "Aresta repetida: " << a.info1 << " , " << a.info2; return out;
}

//Excecao ArestaInexistente
template<class N>
class ArestaInexistente{
public:
    N info1; N info2;
    ArestaInexistente(N inf1, N inf2){
        info1 = inf1;
        info2 = inf2;
    }
};
template<class N>
ostream & operator<<(ostream &out, const ArestaInexistente<N> &a){
    out << "Aresta inexistente: " << a.info1 << " , " << a.info2; return out;
}

template <class N, class A>
Grafo<N,A>::Grafo() {};

template <class N, class A>
Grafo<N,A>::~Grafo() {
    typename vector< No<N,A> *>::iterator it;

    for (it = nos.begin(); it != nos.end(); it++){
        delete *it;
    }
}
//A implementar

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){
    //que insere um novo nó no grafo e retorna o
    //grafo alterado (this). Esta função deve lançar a exceção NoRepetido caso esse nó já exista
    typename vector< No<N,A> *>::const_iterator it;

    for (it = nos.begin(); it != nos.end(); it++){
        if ((*it)->info == dados) throw NoRepetido<N>(dados);
    }

    No<N,A>*no = new No<N,A>(dados);
    nos.push_back(no);
    return *this;
}

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){
    /*que insere uma nova aresta no grafo e retorna o grafo alterado (this). Esta função deve lançar a exceção apropriada
caso a aresta já exista.
*/
    bool findInicio = false;
    bool findFim = false;
    typename vector<No<N,A>*>::iterator it = nos.begin();
    typename vector<Aresta<N,A>>::iterator ita;

    No<N,A>* begin = NULL;
    No<N,A>* end = NULL;

    for (it; it != nos.end(); it++){
        if ((*it)->info == inicio){ //encontrou no
            findInicio = true;
            begin = (*it);
            ita = (*it)->arestas.begin();
            for (ita; ita != (*it)->arestas.end(); ita++){
                if (ita->destino->info == fim){ //encontrou aresta com inicio e fim igual
                    throw ArestaRepetida<N> (inicio, fim);
                }
            }
            if (findFim == true) break;
        }
        else if ((*it)->info == fim){
            findFim = true;
            end = (*it);
            if (findInicio == true) break;
        }
    }
    if (!findFim) throw NoInexistente<N>(fim);
    if (!findInicio) throw NoInexistente<N>(inicio);

    Aresta<N,A> ares(end,val);
    begin->arestas.push_back(ares);

    return *this;
}

template<class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim){
    /*que retorna uma referência
para os dados da aresta especificada. Esta função deve lançar a exceção apropriada caso a aresta não
exista no grafo (ver teste unitário para esta alínea)*/
    typename vector<No<N,A>*>::iterator it = nos.begin();
    typename vector<Aresta<N,A>>::iterator ita;

    for (it; it != nos.end(); it++){
        if ((*it)->info == inicio){
            for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++){
                if (ita->destino->info == fim){
                    return ita->valor;

                }
            }
            throw ArestaInexistente<N> (inicio, fim);
        }
    }
    throw NoInexistente<N> (inicio);

}
template <class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim){
    /*que elimina uma aresta
do grafo e retorna o grafo alterado (this). Esta função deve lançar a exceção apropriada caso a aresta
não exista no grafo (idêntica à da alínea anterior)*/
    typename vector<No<N,A>*>::iterator it = nos.begin();
    typename vector<Aresta<N,A>>::iterator ita;

    for (it; it != nos.end(); it++){
        if ((*it)->info == inicio){
            for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++){
                if (ita->destino->info == fim){
                    (*it)->arestas.erase(ita);
                    return *this;
                }
            }
            throw ArestaInexistente<N> (inicio, fim);
        }
    }
    throw NoInexistente<N> (inicio);


}
template<class N, class A>
int Grafo<N,A>::numArestas(void) const{
    int counter = 0;
    typename vector< No<N,A> *>::const_iterator it;

    for (it = nos.begin(); it != nos.end(); it++){
        counter += (*it)->arestas.size();
    }
    return counter;
}

template<class N, class A>
int Grafo<N, A>::numNos(void) const{
    return nos.size();
}

template <class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const{
    typename vector<No<N,A>*>::const_iterator it;
    typename vector<Aresta<N,A>>::const_iterator ita;

    for (it = nos.begin(); it != nos.end(); it ++){
        os << "( " << (*it)->info;
        for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++){
            os << "[ " << ita->destino->info << " " << ita->valor << "] ";
        }
        os << ") ";
    }
}

template<class N, class A>
ostream & operator<<(ostream &out, const Grafo<N,A> & gr){
    gr.imprimir(out);
    return out;
}
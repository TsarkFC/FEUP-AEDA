#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }

bool Impressora::imprime(Documento doc1) {}



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1){

    if(doc1.getNumPaginas() > numPagImprimir) return false;
    else{
        docsImpressos.push_back(doc1);
        numPagImprimir -= doc1.getNumPaginas();
        return true;
    }
}
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
                                                                numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1) {
    int pag = doc1.getNumPaginas();

    if (pag*doc1.getPercentagemAmarelo() >= numPagImprimirAmarelo || pag*doc1.getPercentagemPreto() >= numPagImprimirPreto){
        return false;
    }
    else{
        docsImpressos.push_back(doc1);
        numPagImprimirAmarelo -= pag*doc1.getPercentagemAmarelo();
        numPagImprimirPreto -= pag*doc1.getPercentagemPreto();
        return true;
    }
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

#include <set>
int Escritorio::numImpressorasSemResponsavel() const{
    /*Esta função retorna o número de impressoras que não têm responsável. Um funcionário pode ser
responsável por múltiplas impressoras, mas uma impressora tem, no máximo, um responsável.*/
    vector<Funcionario>::const_iterator it;
    vector<Impressora*>::const_iterator itI;
    vector<Impressora*> vec;
    set<Impressora*> s;

    for (it = funcionarios.begin(); it != funcionarios.end(); it++){
        vec = it->getImpressoras();
        for (itI = vec.begin(); itI != vec.end(); itI++){
            s.insert(*itI);
        }
    }
    return impressoras.size() - s.size();
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1){
    /*Esta função remove do vetor impressoras, todas as impressoras com ano de aquisição menor que
ano1. Retorna um vetor com (referências para ) as impressoras removidas.*/
    vector<Impressora*> vec;
    vector<Impressora*>::const_iterator it;

    for (it = impressoras.begin(); it != impressoras.end(); it++){
        if ((*it)->getAno() < ano1){
            vec.push_back(*it);
            impressoras.erase(it);
            it--;
        }
    }
    return vec;
}



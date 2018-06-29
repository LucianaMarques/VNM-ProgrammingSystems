#include "ListadeInstrucoes.h"

ListaDeInstrucoes::ListaDeInstrucoes(Instrucao *inicial)
{
    this->arrayInstrucoes[0] = inicial;
    this->numeroDeInstrucoes = 1;
}

ListaDeInstrucoes::~ListaDeInstrucoes()
{

}

void ListaDeInstrucoes::adicionarIntrucao(Instrucao *i)
{
    this->numeroDeInstrucoes = this->numeroDeInstrucoes+1;
    this->arrayInstrucoes[numeroDeInstrucoes-1] = i;
}

int ListaDeInstrucoes::getNumeroDeInstrucoes()
{
    return this->numeroDeInstrucoes;
}

void ListaDeInstrucoes::verificarInstrucoes()
{
    int i;
    unsigned char c;
    for (i=0; i<this->numeroDeInstrucoes; i++){
        c = this->arrayInstrucoes[i]->getComando();
        cout << "Comando x:" << c;
    }
}

void ListaDeInstrucoes::mudarInstrucao(int posicao, unsigned char comando)
{
    int i,n;
    n = this->numeroDeInstrucoes-1;
    for (i = n; i>posicao; i--){
        this->arrayInstrucoes[n+1]=this->arrayInstrucoes[n];
    }
    this->arrayInstrucoes[posicao] = new Instrucao(comando);
}

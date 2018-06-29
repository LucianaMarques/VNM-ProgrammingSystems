#ifndef LISTADEINSTRUCOES_H_INCLUDED
#define LISTADEINSTRUCOES_H_INCLUDED
#include <iostream>
using namespace std;
#include "Instrucao.h"

class ListaDeInstrucoes
{
private:
    Instrucao *arrayInstrucoes[100];
    int numeroDeInstrucoes;
public:
    ListaDeInstrucoes(Instrucao *inicial);
    ~ListaDeInstrucoes();
    void adicionarIntrucao(Instrucao *i);
    int getNumeroDeInstrucoes();
    void verificarInstrucoes();
    void mudarInstrucao(int posicao, unsigned char comando);
};


#endif // LISTADEINSTRUCOES_H_INCLUDED

#ifndef LISTADEREACOES_H_INCLUDED
#define LISTADEREACOES_H_INCLUDED
#include <iostream>
using namespace std;

#include "Reacao.h"

class ListaDeReacoes{
public:
    Reacao* inicio;
    int tamanho;
    ListaDeReacoes(Reacao* i);
    ~ListaDeReacoes();
};



#endif // LISTADEREACOES_H_INCLUDED

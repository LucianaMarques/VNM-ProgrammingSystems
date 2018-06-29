#ifndef LISTADEREACOESMVN_H_INCLUDED
#define LISTADEREACOESMVN_H_INCLUDED
#include <iostream>
using namespace std;

#include "ReacaoMVN.h"

class ListaDeReacoesMVN{
public:
    Reacao* inicio;
    int tamanho;
    ListaDeReacoes(Reacao* i);
    ~ListaDeReacoes();
};



#endif // LISTADEREACOESMVN_H_INCLUDED

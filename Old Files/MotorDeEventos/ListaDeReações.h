#ifndef LISTADEREAçõES_H_INCLUDED
#define LISTADEREAçõES_H_INCLUDED

#include <iostream>
using namespace std;
#include "Reacao.h"

class ListaDeReacoes
{
public:
    ListaDeReacoes();
    ~ListaDeReacoes();
    void setInicio (Reacao *i);
private:
    Reacao *inicio;
};

#endif // LISTADEREAçõES_H_INCLUDED

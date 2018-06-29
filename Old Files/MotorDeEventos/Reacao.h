#ifndef REACAO_H_INCLUDED
#define REACAO_H_INCLUDED
#include <iostream>
using namespace std;
#include "ListadeInstrucoes.h"

class Reacao
{
private:
    string identificador;
    Reacao *proximo;
    ListaDeInstrucoes *lista;
public:
    Reacao(string i, ListaDeInstrucoes *l);
    ~Reacao();
    string getIdentificador();
    void setIdentificador(string i);
    void setListaDeInstrucoes(ListaDeInstrucoes *lista);
    ListaDeInstrucoes *getListaDeInstrucoes();
};


#endif // REACAO_H_INCLUDED

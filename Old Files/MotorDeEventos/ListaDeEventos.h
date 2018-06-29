#ifndef LISTADEEVENTOS_H_INCLUDED
#define LISTADEEVENTOS_H_INCLUDED
#include <iostream>
using namespace std;

#include "Evento.h"
#include "ListaDeReações.h"

class ListaDeEventos
{
private:
    Evento *inicio;
    int numeroDeEventos;
public:
    ListaDeEventos(Evento *inicio);
    ~ListaDeEventos();
    int getNumeroDeEventos();
    Evento* getInicio();
};




#endif // LISTADEEVENTOS_H_INCLUDED

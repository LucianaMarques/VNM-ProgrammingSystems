#ifndef LISTADEEVENTOS_H_INCLUDED
#define LISTADEEVENTOS_H_INCLUDED
#include <iostream>
using namespace std;

#include "Evento.h"

class ListaDeEventos{
public:
    Evento* inicio;
    Evento* fim;
    ListaDeEventos(Evento* e);
    ~ListaDeEventos();
};


#endif // LISTADEEVENTOS_H_INCLUDED

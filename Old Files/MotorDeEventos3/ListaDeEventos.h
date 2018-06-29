#ifndef LISTADEEVENTOS_H_INCLUDED
#define LISTADEEVENTOS_H_INCLUDED
#include <iostream>
using namespace std;
#include "Evento.h"

class ListaDeEventos{
public:
    ListaDeEventos();
    ~ListaDeEventos();
    Evento* inicio;
    Evento* fim;
};


#endif // LISTADEEVENTOS_H_INCLUDED

#ifndef LISTALIGADA_H_INCLUDED
#define LISTALIGADA_H_INCLUDED

#include <iostream>
using namespace std;

#include "Mneumonico.h"
#include "Montador.h"
#include "Simbolo.h"
#include "Evento.h"
#include "SimboloLigador.h"
class ListaLigada
{
public:
    Mneumonico* mInicio;
    Mneumonico* mFinal;

    Simbolo* sInicio;
    Simbolo* sFinal;

    Evento* eInicio;
    Evento* eFim;

    ListaLigada();
    ~ListaLigada();

    SimboloLigador* slInicio;
    SimboloLigador* slFinal;
};

#endif // LISTALIGADA_H_INCLUDED

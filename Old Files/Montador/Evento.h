#ifndef EVENTO_H_INCLUDED
#define EVENTO_H_INCLUDED

#include <iostream>
using namespace std;

class Evento{
public:
    Evento(string Reacao);
    ~Evento();
    string tipoDeReacao;
    int instanteProgramado;
    bool breakpoint = false;
    Evento* proximo;
};


#endif // EVENTO_H_INCLUDED

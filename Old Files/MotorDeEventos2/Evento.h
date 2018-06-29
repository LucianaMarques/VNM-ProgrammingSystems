#ifndef EVENTO_H_INCLUDED
#define EVENTO_H_INCLUDED
#include <iostream>
using namespace std;

class Evento{
public:
    int instanteProgramado;
    string tipoDeReacao;
    bool breakpoint = false;
    Evento* proximo;
    bool fim=false;

    Evento(string Reacao, int instante, bool breakpoint);
    ~Evento();
};


#endif // EVENTO_H_INCLUDED

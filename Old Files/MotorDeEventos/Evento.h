#ifndef EVENTO_H_INCLUDED
#define EVENTO_H_INCLUDED
#include <iostream>
using namespace std;
#include <string.h>
#include "Reacao.h"

class Evento
{
    public:
        Evento(string i);
        ~Evento();
        void setProximo(Evento *p);
        Evento* getProximo();
        void setReacao (Reacao *r);
        Reacao* getReacao();
        string identificador;

    private:
        int instanteProgramado;
        Evento *proximo;
        Reacao *reacao;
};

#endif // EVENTO_H_INCLUDED

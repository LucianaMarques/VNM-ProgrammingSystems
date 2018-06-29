#include "Evento.h"

Evento::Evento(string i)
{
    identificador = i;
}

Evento::~Evento()
{

}

void Evento::setProximo(Evento *p)
{
    this->proximo = p;
}

Evento* Evento::getProximo()
{
    return this->proximo;
}

void Evento::setReacao(Reacao *r)
{
    this->reacao = r;
}

Reacao* Evento::getReacao()
{
    return this->reacao;
}

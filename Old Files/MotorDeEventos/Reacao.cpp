#include "Reacao.h"

Reacao::Reacao(string i, ListaDeInstrucoes *l)
{
    this->identificador = i;
    this->lista = l;
}

Reacao::~Reacao()
{

}

string Reacao::getIdentificador()
{
    return this->identificador;
}

void Reacao::setIdentificador(string i)
{
    this->identificador = i;
}

void Reacao::setListaDeInstrucoes(ListaDeInstrucoes *l)
{
    this->lista = l;
}

ListaDeInstrucoes* Reacao::getListaDeInstrucoes()
{
    return this->lista;
}

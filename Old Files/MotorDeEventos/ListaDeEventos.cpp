#include "ListaDeEventos.h"
#include "Evento.h"

ListaDeEventos::ListaDeEventos(Evento *i){
    this->inicio = i;
    this->numeroDeEventos = 1;

}

ListaDeEventos::~ListaDeEventos(){

}

int ListaDeEventos::getNumeroDeEventos(){
    return this->numeroDeEventos;
}

Evento* ListaDeEventos::getInicio(){
    return this->inicio;
}



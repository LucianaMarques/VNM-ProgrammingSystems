#include "Evento.h"

Evento::Evento(string Reacao, int instante, bool breakpoint){
    this->tipoDeReacao = Reacao;
    this->instanteProgramado = instante;
    this->breakpoint = breakpoint;
}

Evento::~Evento(){

}

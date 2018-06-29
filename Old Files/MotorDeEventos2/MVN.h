#ifndef MVN_H_INCLUDED
#define MVN_H_INCLUDED
#include <iostream>
using namespace std;

#include "ListaDeEventos.h"
#include "Evento.h"
#include "Reacao.h"
#include "ListaDeReacoes.h"


class MVN {
public:
    uint8_t memoria[4095];
    uint16_t acc;
    uint16_t ci;
    uint16_t arg;
    uint16_t instrucao;
    MVN();
    ~MVN();
    ListaDeReacoes* lista;
    void gravar_programa();
    void captar_instrucao();
    string decodificar();

};


#endif // MVN_H_INCLUDED

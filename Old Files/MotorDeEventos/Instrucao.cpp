#include "Instrucao.h"

Instrucao::Instrucao(unsigned char c)
{
    this->comando = c;
}

Instrucao::~Instrucao()
{

}

unsigned char Instrucao::getComando()
{
    return this->comando;
}

void Instrucao::setComando(unsigned char c)
{
    this->comando = c;
}

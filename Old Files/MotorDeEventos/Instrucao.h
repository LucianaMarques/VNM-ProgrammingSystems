#ifndef INSTRUCAO_H_INCLUDED
#define INSTRUCAO_H_INCLUDED
#include <iostream>
using namespace std;

class Instrucao
{
private:
    unsigned char comando;
public:
    Instrucao(unsigned char c);
    ~Instrucao();
    unsigned char getComando();
    void setComando(unsigned char comando);
};


#endif // INSTRUCAO_H_INCLUDED

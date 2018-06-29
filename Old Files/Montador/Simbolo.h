#ifndef SIMBOLO_H_INCLUDED
#define SIMBOLO_H_INCLUDED

#include <iostream>
using namespace std;

class Simbolo
{
public:
    string rotulo;
    uint16_t endereco;
    string status = "indefinido";
    string referenciado;

    Simbolo* proximo;
    Simbolo* anterior;

    Simbolo(string rotulo);
    ~Simbolo();
};



#endif // SIMBOLO_H_INCLUDED

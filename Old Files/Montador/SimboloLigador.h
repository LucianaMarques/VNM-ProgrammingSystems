#ifndef SIMBOLOLIGADOR_H_INCLUDED
#define SIMBOLOLIGADOR_H_INCLUDED
#include <iostream>
using namespace std;
class SimboloLigador
{
public:
    string simbolo;
    uint16_t enderecos[0xfff];
    uint16_t cont = 0;
    uint16_t endereco_inicial;
    SimboloLigador(string s);
    ~SimboloLigador();
    SimboloLigador* proximo;
};


#endif // SIMBOLOLIGADOR_H_INCLUDED

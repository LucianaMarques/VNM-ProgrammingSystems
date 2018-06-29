#ifndef REACAOMVN_H_INCLUDED
#define REACAOMVN_H_INCLUDED
#include <iostream>
using namespace std;
class ReacaoMVN{
public:
    ReacaoMVN(string tipo, bool fim);
    ~ReacaoMVN();
    ReacaoMVN* proximo;
    string tipoDeReacao;
    bool fim;
};



#endif // REACAOMVN_H_INCLUDED

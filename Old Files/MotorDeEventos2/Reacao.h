#ifndef REACAO_H_INCLUDED
#define REACAO_H_INCLUDED

class Reacao{
public:
    string tipoDeReacao;
    int numInstrucoes;
    int listaInstrucoes[1000];
    Reacao* proximo;
    bool fim;

    Reacao(string tipoDeReacao, int numInstrucoes, bool fim);
    ~Reacao();
};


#endif // REACAO_H_INCLUDED

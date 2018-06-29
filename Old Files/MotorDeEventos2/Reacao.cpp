#include <iostream>
using namespace std;

#include "Reacao.h"

Reacao::Reacao(string tipoDeReacao, int numInstrucoes, bool fim){
    this->tipoDeReacao = tipoDeReacao;
    this->numInstrucoes = numInstrucoes;
    this->fim = fim;
    //Procedimento para definir as instrucoes
    int i;
    for (i=0; i<numInstrucoes; i++){
        cout << "Digite a instrucao " << i+1 << " :";
        cin >> this->listaInstrucoes[i];
    }
    cout << "Reacao Criada!\n";
}

Reacao::~Reacao(){

}

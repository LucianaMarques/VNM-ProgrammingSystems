#include "MVN.h"

MVN::MVN(){
    //criar a lista de reacoes global

}

void MVN::gravar_programa(){
    bool finalizou = false;
    uint8_t posicao = 0x00;
    cout << "Escolher posicao de memoria inicial: \n";
    cin >> posicao;

    while (finalizou == false){
        cout << "Digite o comando: ";
        cin >> this->instrucao;
        this->memoria[posicao] = instrucao>>8;
        this->memoria[posicao+1] = (instrucao&00001111);
        posicao = posicao + 2;
        int parada;
        cout << "Deseja parar? (0-Nao 1-Sim \n";
        cin >> parada;
        if (parada == 1){
            finalizou = true;
        }
    }
}

void MVN::captar_instrucao(){
    this->instrucao = 8<<(this->memoria[ci]) + this->memoria[ci+1];
}

/*ListaDeEventos* MVN::eventos_instrucoes(){
    cout << "Informar endereco de inicio: ";
    cin >> this->ci;

    //criacao da lista de eventos a partir dos codigos
    uint8_t = codigo;
    codigo = memoria[ci];
    string mneumonico = decodificar(codigo);
    Evento* evento = new Evento(mneumonico,0,false);
    ListaDeEventos* lista = new ListaDeEventos(evento);
    ci = ci + 4;

    int acabou = 0;
    while (acabou != 1){
        codigo = memoria[ci];
        mneumonico = decodificar(codigo);
        Evento* e = new Evento(mneumonico,0,false);
        lista->fim->proximo = e;
        lista->fim = e;
        ci = ci + 4;
        cout << "Parar simulacao? 0- Nao 1- Sim\n";
        cin >> acabou;
    }

    // reacoes à lista de eventos
}
*/
string MVN::decodificar(){
    uint8_t codigo = this->instrucao>>12;
    if (codigo == 0x0) return("JP");
    if (codigo == 0x1) return("JZ");
    if (codigo == 0x2) return("JN");
    if (codigo == 0x3) return("LV");
    if (codigo == 0x4) return("+");
    if (codigo == 0x5) return("-");
    if (codigo == 0x6) return("*");
    if (codigo == 0x7) return("/");
    if (codigo == 0x8) return("LD");
    if (codigo == 0x9) return("MM");
    if (codigo == 0xA) return("JP");
    if (codigo == 0xB) return("RS");
    if (codigo == 0xC) return("HM");
    if (codigo == 0xD) return("GD");
    if (codigo == 0xE) return("PD");
    if (codigo == 0xF) return("OS");
}

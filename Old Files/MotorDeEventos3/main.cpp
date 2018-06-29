#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string>
using namespace std;

#include <fstream>
#include <sstream>
#include <cstring>

#include "Evento.h"
#include "ListaDeEventos.h"
#include "MVN.h"

#include <stdio.h>
#include <conio.h>

//Eventos Simulador De Eventos
Evento* iniciar_simulador = new Evento("INICIAR SIMULADOR");
Evento* finalizar_simulador = new Evento("FINALIZAR SIMULADOR");
Evento* imprimir_ola = new Evento("OLA");

//Eventos MVN
Evento* carregar_programa = new Evento("CARREGAR PROGRAMA");
Evento* simular_programa = new Evento("SIMULAR PROGRAMA");
Evento* capturar_instrucao = new Evento("CAPTURAR INSTRUCAO");
Evento* decodificar = new Evento("DECODIFICAR");
Evento* executar = new Evento("EXECUTAR");
Evento* fim = new Evento("FINAL");

void menu();
void reacaoMVN(ListaDeEventos* listaMVN, MVN* MVN);
string decode(MVN* mvn);
void executarMVN(MVN* mvn, string inst);
uint16_t ascii_hex(string texto);
void verificar_registradores(MVN* mvn);
void imprimirListaDeEventos(ListaDeEventos* lista);
void reacaoSimulador (ListaDeEventos* listaSimulador);

int main()
{
    menu();
    return 0;
}

void menu(){
    int escolha = 3;
    while (escolha!=2){
        cout << "Bem vindo ao Simulador de Eventos \n";
        cout << "O que deseja simular? \n";
        cout << "0 - Lista de Eventos Nova \n";
        cout << "1 - Programa utilizando MVN \n";
        cout << "2 - Sair \n";
        cin >> escolha;
        if (escolha == 0){
            int escolha2 = 7;
            ListaDeEventos* listaEventosDisponiveis = new ListaDeEventos();
            listaEventosDisponiveis->inicio = iniciar_simulador;
            listaEventosDisponiveis->fim = finalizar_simulador;
            Evento* atual = listaEventosDisponiveis->inicio;
            atual->proximo = imprimir_ola;
            atual = atual->proximo;
            atual->proximo = listaEventosDisponiveis->fim;

            ListaDeEventos* nova = new ListaDeEventos();
            nova->inicio = iniciar_simulador;
            nova->fim = finalizar_simulador;
            nova->inicio->proximo = nova->fim;
            atual = nova->inicio;

            while (escolha2!=3)
            {
                cout << "O que fazer? \n";
                cout << "0 - Imprimir Eventos Disponíveis\n";
                cout << "1 - Criar lista de Eventos nova\n";
                cout << "2 - Simular Lista de Eventos\n";
                cout << "3 - Sair\n";
                cin >> escolha2;
                if (escolha2 == 0)
                {
                    cout << "\n-------------------------\n";
                    cout << "Lista de Eventos disponiveis: \n";
                    cout << "Evento 1: " << iniciar_simulador->tipoDeReacao << "\n";
                    cout << "Evento 2: " << imprimir_ola->tipoDeReacao << "\n";
                    cout << "Evento 3: " << finalizar_simulador->tipoDeReacao << "\n";
                    cout << "-------------------------\n\n";
                }
                if (escolha2 == 1)
                {
                    int sair2 = 0;
                    cout << "Criando lista de eventos nova\n";
                    cout << "------------------------\n";
                    cout << "Lista de Eventos Atual: \n";
                    imprimirListaDeEventos(nova);
                    cout << "\n------------------------\n\n";
                    cout << "0 - Adicionar Evento \n";
                    cout << "1 - Sair \n";
                    cin >> sair2;
                    bool sair = false;
                    if (sair2 == 1) sair = true;
                    else sair = false;
                    while (sair == false)
                    {
                        string reacao;
                        cout << "Escrever reacao do evento desejado: \n";
                        cin >> reacao;
                        atual->proximo = new Evento(reacao);
                        atual->proximo->proximo = nova->fim;
                        atual = atual->proximo;
                        cout << "\n0 - Adicionar Evento \n";
                        cout << "1 - Sair \n";
                        cin >> sair2;
                        if (sair2 == 1) sair = true;
                    }
                    cout << "------------------------\n";
                    cout << "Lista de Eventos Atual: \n";
                    imprimirListaDeEventos(nova);
                    cout << "------------------------\n";
                }
                if (escolha2 == 2)
                {
                    cout << "Simulando a lista de eventos criada\n";
                    reacaoSimulador(nova);
                }
            }
        }
        if (escolha == 1){
            int escolha3=10;
            MVN* mvn = new MVN();
            while(escolha3!=4){
                cout << "O que fazer? \n";
                cout << "0 - Carregar Programa Novo na Memoria\n";
                cout << "1 - Simular Programa\n";
                cout << "2 - Imprimir Instrucoes de Memoria\n";
                cin >> escolha3;

                ListaDeEventos* listaMVN = new ListaDeEventos();
                listaMVN->fim = fim;
                if (escolha3 == 0)
                { // reacao ao evento de carregar programa
                    listaMVN->inicio = carregar_programa;
                    listaMVN->fim = fim;
                    listaMVN->inicio->proximo = fim;
                    reacaoMVN(listaMVN,mvn);
                }

                if (escolha3 == 1)
                {
                    listaMVN->inicio = simular_programa;
                    listaMVN->fim = fim;
                    listaMVN->inicio->proximo = fim;
                    reacaoMVN(listaMVN,mvn);
                }

                if (escolha3 == 2)
                {
                    int escolha5;
                    cout << "Posicao do contador de instrucoes: " << hex << mvn->pc << '\n';
                    cout << "Deseja altera-la? 0- Nao 1- Sim \n";
                    cin >> escolha5;
                    if (escolha5 == 1) cin >> mvn->pc;
                    uint16_t parada;
                    cout << "Escolher Posicao de parada: ";
                    cin >> hex >> parada;
                    cout << '\n';
                    while(mvn->pc < parada)
                    {
                        cout << "Posicao " << hex << (int)mvn->pc << ": " << hex << (int)mvn->memoria[mvn->pc] << '\n';
                        mvn->pc++;
                    }
                }
            }
         }
    }
}


void reacaoSimulador (ListaDeEventos* listaSimulador)
{
    Evento* atual = listaSimulador->inicio;
    int sair = 0;
    string codigo;
    while(sair == 0)
    {
        codigo = atual->tipoDeReacao;
        cout << "Evento atual: " << codigo << "\n";
        if (codigo == "INICIAR SIMULADOR")
        {
            cout << "\n\nIniciando Simulador\n\n";
            atual = atual->proximo;
        }
        if (codigo == "OLA")
        {
            cout << "Ola! Bem vindo ao Simulador de Eventos!\n";
            atual = atual->proximo;
        }
        if (codigo == "FINALIZAR SIMULADOR")
        {
            cout << "\n\nFinalizando Simulador\n\n";
            sair = 1;
        }
    }
}

void reacaoMVN(ListaDeEventos* listaMVN, MVN* MVN){
    Evento* atual = listaMVN->inicio;
    int sair = 0;
    int ir;
    string inst;
    while (sair == 0){
        string codigo = atual->tipoDeReacao;
        cout << "Evento atual " << atual->tipoDeReacao << "\n";
        cout << "Aperte 1 para continuar\n";
        cin >> ir;
        if (ir == 1) {
        if (codigo == "CARREGAR PROGRAMA"){
                uint16_t escolha;
                cout << "Posicao do contador de instrucao: " << hex << MVN->pc << '\n';
                cout << "Deseja alterar a posicao? 0- Nao 1- Sim \n";
                cin >> hex >> escolha;
                if (escolha == 1){
                    cout << "Digite a posicao desejada: \n";
                    cin >> MVN->pc;
                }
                string comando;
                ifstream file ("exercicio2.txt");
                uint16_t converter[2];
                string vez;
                if (file.is_open()){
                    while (getline(file,comando)){
                        //Primeiro byte
                        vez = comando[0];
                        converter[0] = ascii_hex(vez);
                        vez = comando[1];
                        converter[1] = ascii_hex(vez);
                        MVN->memoria[MVN->pc] = (converter[0])*16 + converter[1];
                        cout << "Posicao " << MVN->pc << ": " ;
                        cout << hex << (int)MVN->memoria[MVN->pc] << '\n';
                        MVN->pc++;

                        //Segundo byte
                        vez = comando[2];
                        converter[0] = ascii_hex(vez);
                        vez = comando[3];
                        converter[1] = ascii_hex(vez);
                        MVN->memoria[MVN->pc] = (converter[0])*16 + converter[1];
                        cout << "Posicao " << hex << MVN->pc << ": ";
                        cout << hex << (int)MVN->memoria[MVN->pc] << '\n';
                        MVN->pc++;
                    }
                    file.close();
                    cout << "Programa carregado com sucesso. \n\n";
                }
                else
                {
                    cout << "Unable to read file" << "\n";
                }
        }
        if (codigo == "SIMULAR PROGRAMA"){
            cout << "Valor atual do Contador de Instrucoes: " << MVN->pc << "\n";
            cout << "Deseja alterar o valor? 0- Nao 1- Sim: \n";
            int decisao;
            cin >> decisao;
            if (decisao == 1){
                cin >> MVN->pc;
            }
            listaMVN->inicio->proximo = capturar_instrucao;
            listaMVN->inicio->proximo->proximo = listaMVN->fim;
            cout << "Comecou simulacao\n";
        }
        if (codigo == "CAPTURAR INSTRUCAO"){
            cout << "Captura de instrucao \n";
            MVN->instrucao = (MVN->memoria[MVN->pc])*256 + MVN->memoria[MVN->pc+1];
            cout << "Instrucao: " << hex << MVN->instrucao << "\n";
            atual->proximo = decodificar;
            atual->proximo->proximo = listaMVN->fim;
            cout << "Acumulador: " << MVN->acc << '\n';
        }
        if (codigo == "DECODIFICAR"){
            cout << "Decodificacao \n";
            cout << "Acumulador: " << MVN->acc << '\n';
            inst = decode(MVN);
            cout << "Codigo: " << inst << "\n";
            if (inst == "HM") atual->proximo = listaMVN->fim;
            else
            {
                atual->proximo = executar;
                atual->proximo->proximo = listaMVN->fim;
            }
        }

        if (codigo == "EXECUTAR")
        {
            executarMVN(MVN,inst);
            atual->proximo = capturar_instrucao;
            atual->proximo->proximo = listaMVN->fim;
            verificar_registradores(MVN);
            cout << "Acumulador: " << MVN->acc << '\n';
        }

        if (codigo == "FINAL"){
            sair = 1;
        }
        atual = atual->proximo;
        }
    }
}

string decode(MVN* mvn){
    uint8_t codigo = mvn->instrucao>>12;
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
    if (codigo == 0xA) return("SC");
    if (codigo == 0xB) return("RS");
    if (codigo == 0xC) return("HM");
    if (codigo == 0xD) return("GD");
    if (codigo == 0xE) return("PD");
    if (codigo == 0xF) return("OS");
}

void executarMVN(MVN* mvn, string inst){
    mvn->arg = (mvn->memoria[mvn->pc]&0x01)*256 + mvn->memoria[mvn->pc + 1];

    //JUMP
    if (inst == "JP"){
        mvn->pc = mvn->arg;
    }

    //JUMP IF ZERO
    if (inst == "JZ")
    {
        if (mvn->acc == 0) mvn->pc = mvn->arg;
        else mvn->pc = mvn->pc + 2;
    }

    //JUMP IF NEGATIVE
    if (inst == "JN")
    {
        if (mvn->acc < 0) mvn->pc = mvn->arg;
        else mvn->pc = mvn->pc + 1;
    }

    //LV
    if (inst == "LV")
    {
        mvn->acc = mvn->arg;
        mvn->pc = mvn->pc + 2;
    }

    //ADD
    if (inst == "+")
    {
        mvn->acc = mvn->acc + mvn->memoria[mvn->arg];
        mvn->pc = mvn->pc + 2;
    }

    //SUBTRACT
    if (inst == "-")
    {
        mvn->acc = mvn->acc - mvn->memoria[mvn->arg];
        mvn->pc = mvn->pc + 2;
    }

    //MULTIPLY
    if (inst == "*")
    {
        mvn->acc = mvn->acc * mvn->memoria[mvn->arg];
        mvn->pc = mvn->pc + 2;
    }

    //DIVIDE
    if (inst == "/"){
        mvn->acc = mvn->acc / mvn->memoria[mvn->arg];
        mvn->pc = mvn->pc + 2;
    }

    //LOAD FROM MEMORY
    if (inst == "LD"){
        mvn->acc = mvn->memoria[mvn->arg];
        cout << "Valor carregado no acumulador: " << hex << mvn->acc << '\n';
        mvn->pc = mvn->pc + 2;
    }

    //STORE
    if (inst == "MM"){
        mvn->memoria[mvn->arg] = mvn->acc;
        mvn->pc = mvn->pc + 2;
    }

    //CALL SUBROUTINE
    if (inst == "SC"){
        mvn->memoria[mvn->pc] = mvn->arg >> 8;
        mvn->memoria[mvn->pc + 1] = mvn->arg&0x011;
        mvn->pc = mvn->arg + 2;
    }

    //RETURN FROM SUBROUTINE
    if (inst == "RS"){
        mvn->pc = mvn->arg;
    }

    //HM já é lidado sozinho em menu

    //INPUT
    if (inst == "GD"){
        cout << "Inserir input: ";
        cin >> mvn->acc;
        cout << "\n";
        mvn->pc = mvn->pc + 2;
    }
    //OUTPUT
    if (inst == "PD"){
        cout << "Valor: " << mvn->acc << "\n";
        mvn->pc = mvn->pc + 2;
    }
    //OPERATING SYSTEM CALL
    if (inst == "OS"){
        mvn->pc = mvn->pc + 2;
    }
}

uint16_t ascii_hex(string texto)
{
    if (texto == "0") return 0x0;
    if (texto == "1") return 0x1;
    if (texto == "2") return 0x2;
    if (texto == "3") return 0x3;
    if (texto == "4") return 0x4;
    if (texto == "5") return 0x5;
    if (texto == "6") return 0x6;
    if (texto == "7") return 0x7;
    if (texto == "8") return 0x8;
    if (texto == "9") return 0x9;
    if (texto == "A") return 0xa;
    if (texto == "B") return 0xb;
    if (texto == "C") return 0xc;
    if (texto == "D") return 0xd;
    if (texto == "E") return 0xe;
    if (texto == "F") return 0xf;
}

void verificar_registradores(MVN* mvn)
{
    cout << "Valores armazenados nos registradores: \n";
    cout << "Acumulador: " << mvn->acc << '\n';
    cout << "Contador de Instrucao: " << mvn->pc << '\n';
    cout << "Argumento: " << mvn->arg << '\n';
    cout << "Instrucao: " << mvn->instrucao << '\n';
}

void imprimirListaDeEventos(ListaDeEventos* lista)
{
    Evento* atual = lista->inicio;
    int cont = 1, sair = 0;
    while(sair == 0)
    {
        if (atual == lista->fim)
        {
            sair = 1;
        }
        else
        {
            cout << "Evento " << cont << ": " << atual->tipoDeReacao << '\n';
            cont++;
            atual = atual->proximo;
        }
    }
    cout << "Evento " << cont << ": " << atual->tipoDeReacao << "\n";

}

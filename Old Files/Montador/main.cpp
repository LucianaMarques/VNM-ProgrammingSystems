#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

#include "Evento.h"
#include "ListaLigada.h"
#include "Simbolo.h"
#include "MVN.h"
#include "Mneumonico.h"


//Eventos do Montador
Evento* LeituraLinha = new Evento("LEITURA LINHA");
Evento* TratarLinha = new Evento("TRATAR LINHA");
Evento* AnalisarMneumonico = new Evento("ANALISAR MNEUMONICO");
Evento* AnalisarOperando = new Evento("ANALISAR OPERANDO");
Evento* Fim = new Evento("FINAL");

//Eventos do Ligador
Evento* AnalisarMain = new Evento("ANALISAR MAIN");
Evento* AnalisarRotina = new Evento("ANALISAR ROTINA");
Evento* EscreveCodigo = new Evento("ESCREVE CODIGO");
Evento* AtualizarTabelaRefExternas = new Evento("ATUALIZAR TABELA DE REFERENCIAS EXTERNAS");
Evento* FimLigador = new Evento("FINAL LIGADOR");

//MVN
MVN* mvn = new MVN();

//Tabela de Simbolos
ListaLigada* TabelaDeSimbolos = new ListaLigada();

//Tabela de Mneumonicos
ListaLigada* TabelaDeMneumonicos = new ListaLigada();

//Variavel para analisar operando
bool operando = false;

//Funcoes do Programa
void menu();

void reacaoListaEventos(ListaLigada* listaEventos, Simbolo* SimboloFinal, uint16_t pc);

void definir_simbolo(ListaLigada* TabelaDeSimbolos,string rotulo,uint16_t pc);
void verificarRotulo(string linha, Simbolo* SimboloFinal);
void imprimirTabelaDeSimbolos (ListaLigada* TabelaDeSimbolos);
bool checar_tabela_simbolos(string rotulo, ListaLigada* TabelaDeSimbolos);
void atualizar_tabela_simbolos(ListaLigada* TabelaDeSimbolos, Simbolo* novo);
uint16_t obter_endereco (string simbolo,ListaLigada* TabelaDeSimbolos);


void criar_tabela_mneumonicos(ListaLigada* TabelaDeMneumonicos);
bool verificar_mneumonico(string mneumonico, ListaLigada* TabelaDeMneumonicos);
uint8_t decode(string codigo);
uint16_t ascii_to_dec(string codigo);
Mneumonico* procurar_mneumonico(string mneumonico, ListaLigada* TabelaDeMneumonicos);

void split_linha(string linha, string meneumonico, string op_ou_simb);
string captar_op_ou_simbolo(string linha);
string captar_mneumonico(string linha);
string captar_codigo(string linha);

uint16_t ascii_hex(char texto);

void imprimirTabelaSimbolosExternos(ListaLigada* listaSimbolos);
void reacoesLigador(ListaLigada* eventosLigador,uint16_t pc_inicial);
string simboloexterno (string linha);
string simboloexterno (string linha);
void achar_comando(string linha,string c);


int main()
{
    int passo = 1;
    menu();
    return 0;
}

void menu()
{
    int sair = 0;
    int passo = 0;
    while (sair ==0)
    {
        cout << "Selecione a opcao: \n";
        cout << "1- Montador de 2 passos \n";
        cout << "2- Ligador \n";
        cout << "3- Sair\n";
        int escolha;
        cin >> escolha;
        if (escolha == 1)
        {
            string I = "INICIO TABELA DE SIMBOLOS";
            string F = "FIM TABELA DE SIMBOLOS";
            Simbolo* SimboloInicio = new Simbolo(I);
            Simbolo* SimboloFinal = new Simbolo(F);
            TabelaDeSimbolos->sInicio = SimboloInicio;
            TabelaDeSimbolos->sFinal = SimboloFinal;
            TabelaDeSimbolos->sInicio->proximo = SimboloFinal;
            TabelaDeSimbolos->sFinal->anterior = SimboloInicio;
            cout << "Criou Tabela de Simbolos \n";

            criar_tabela_mneumonicos(TabelaDeMneumonicos);
            cout << "Criou Tabela de Mneumonicos\n";

            ListaLigada* ListaDeEventos = new ListaLigada();
            ListaDeEventos->eInicio = LeituraLinha;
            ListaDeEventos->eFim = Fim;
            ListaDeEventos->eInicio->proximo = ListaDeEventos->eFim;
            uint16_t pc = 0;
            reacaoListaEventos(ListaDeEventos, SimboloFinal, pc);
        }
        if (escolha == 2)
        {
            cout << "Iniciando Ligador\n";
            uint16_t pc_inicial;
            cout << "Digitar valor de endereco inicial: \n";
            cin >> pc_inicial;
            int passoligador = 1;
            ListaLigada* eventosLigador = new ListaLigada();
            eventosLigador->eInicio = AnalisarMain;
            eventosLigador->eFim = FimLigador;
            reacoesLigador(eventosLigador, pc_inicial);
        }
        if (escolha == 3)
        {
            sair = 1;
        }
    }
}

void reacoesLigador(ListaLigada* eventosLigador,uint16_t pc_inicial)
{
    Evento* atual = eventosLigador->eInicio;
    eventosLigador->eFim = FimLigador;
    atual->proximo = eventosLigador->eFim;
    int sair = 0;
    int linhaAtual = 0;
    uint16_t pc = pc_inicial;
    string comando, nome, subrotina;
    int passoLigador = 0;
    ifstream principal;
    ofstream codigofinal;
    principal.open("MAIN.txt");
    codigofinal.open("codigoligador.txt");
    ListaLigada* tabelaSimbolosMAIN = new ListaLigada();
    while(sair == 0)
    {
        cout << "Evento Atual: " << atual->tipoDeReacao << '\n';
        if (atual->tipoDeReacao == "ANALISAR MAIN")
        {
            string linha;
            while (getline(principal,linha))
            {
                string c,simb;
                split_linha(linha,c,simb);
                cout << c << "\n";
                cout << simb << "\n";
                cout << linha << "\n";
                if (c == "EXT")
                {
                    SimboloLigador* s = new SimboloLigador(simb);
                    SimboloLigador* slatual = new SimboloLigador("INICIO");
                    if (pc == pc_inicial)
                    {
                        tabelaSimbolosMAIN->slInicio = s;
                        SimboloLigador* slfim = new SimboloLigador("FINAL LIGADOR");
                        tabelaSimbolosMAIN->slFinal = slfim;
                        tabelaSimbolosMAIN->slInicio->proximo = tabelaSimbolosMAIN->slFinal;
                    }
                    else
                    {
                        slatual->proximo = s;
                        slatual = slatual->proximo;
                        slatual->proximo = tabelaSimbolosMAIN->slFinal;
                    }
                }
            }
            imprimirTabelaSimbolosExternos(tabelaSimbolosMAIN);
            atual = atual->proximo;
        }
        if (atual == eventosLigador->eFim)
        {
            sair =1;
        }
    }

}
void imprimirTabelaSimbolosExternos(ListaLigada* listaSimbolos)
{
    SimboloLigador* atual = listaSimbolos->slInicio;
    cout << "------------------------------\n";
    cout << "Tabela de Simbolos externos \n";
    int cont = 1;
    while (atual!= listaSimbolos->slFinal)
    {
        cout << "Simbolo " << cont << ": " << atual->simbolo << "\n";
        cont ++;
    }
    cout << "------------------------------\n";
}
string simboloexterno (string linha)
{
    stringstream ss(linha);
    vector<string> tokens;
    string buf;
    int cont=0;
    while (ss >> buf)
    {
        tokens.push_back(buf);
        if (cont == 1)
        {
            return buf;
        }
        cont++;
    }
}

/*void achar_comando(string linha,string c)
{
    stringstream ss(linha);
    vector<string> tokens;
    string buf, buf1, buf2;
    int cont=0;
    while (ss >> buf)
    {
        tokens.push_back(buf);
        if (cont == 0)
        {
            buf1 = buf;
            cout << buf1 << endl;
            mneumonico = buf1;
        }
        if (cont == 1)
        {
            buf2 = buf;
            cout << buf2 << endl;
            op_ou_simb = buf2;
        }
        cont++;
    }
    cout << "Gravou com sucesso" << endl;
    cout << mneumonico << '\n';
    cout << op_ou_simb << '\n';
}
*/
string linha;
void reacaoListaEventos(ListaLigada* listaEventos, Simbolo* SimboloFinal, uint16_t pc)
{
    Evento* atual;
    atual = listaEventos->eInicio;
    int sair = 0;
    int linhaAtual = 0;
    string mneumonico, op_ou_simb, codigo;
    int passo = 1;
    ofstream codigogerado;
    codigogerado.open("codigo.txt");
    uint16_t instrucao;
    while (sair == 0)
    {
        cout << "Evento Atual: " << atual->tipoDeReacao << '\n';
        if (atual->tipoDeReacao == "LEITURA LINHA")
        {
            ifstream file ("programaexemplo3.txt");
            if (file.is_open())
            {
                int contLinha = 0;
                bool achouLinha = false;
                while (achouLinha == false && getline(file,linha))
                {
                    //cout << "Linha Atual: " << linhaAtual << '\n';
                    //cout << "Linha sendo verificada: " << contLinha << '\n';
                    //cout << linha << '\n';
                    if (contLinha == linhaAtual)
                    {
                        if (passo == 2) cout << linha << endl;
                        cout << "PC: " << hex << pc << endl;
                        Evento* proximo = atual->proximo;
                        atual->proximo = TratarLinha;
                        atual->proximo->proximo = proximo;
                        achouLinha = true;
                    }
                    contLinha++;
                }
                linhaAtual++;
                file.close();
            }
            else
            {
                cout << "Unable to read file" << "\n";
            }
        }
        if (atual->tipoDeReacao == "TRATAR LINHA")
        {
            cout << "Linha Atual: " << linha << '\n';
            //DIVIDIR A LINHA EM DUAS STRINGS
            mneumonico = captar_mneumonico(linha);
            op_ou_simb = captar_op_ou_simbolo(linha);
            //if (mneumonico == "K") codigo = captar_codigo(linha);
            cout << "Mneumonico: " << mneumonico << endl;
            cout << "Operando ou simbolo: " << op_ou_simb << endl;
            if (passo == 1)
            {
                if (op_ou_simb[0] == '*')
                {
                    cout << "eh operando" << endl;
                }
                else
                {
                    cout << "contem rotulo" << endl;
                    if (checar_tabela_simbolos(op_ou_simb,TabelaDeSimbolos) == false)
                    {
                        Simbolo* novo = new Simbolo(op_ou_simb);
                        atualizar_tabela_simbolos(TabelaDeSimbolos,novo);
                    }
                    else
                    {
                        if (mneumonico == "K")
                        {
                            cout << "Definindo simbolo" << endl;
                            definir_simbolo(TabelaDeSimbolos,op_ou_simb, pc-1);
                        }
                    }
                }
                Evento* proximo = atual->proximo;
                atual->proximo = LeituraLinha;
                atual->proximo->proximo = proximo;
                if (mneumonico == "K") pc++;
                else pc = pc + 2;
            }
            if (passo == 2)
            {
                //ANALISAR MNEUMONICO
                Evento* proximo = atual->proximo;
                atual->proximo = AnalisarMneumonico;
                atual->proximo->proximo = proximo;
            }
        }
        if (atual->tipoDeReacao == "ANALISAR MNEUMONICO")
        {
            bool existe = verificar_mneumonico(mneumonico,TabelaDeMneumonicos);
            if (existe == true)
            {
                instrucao = (uint16_t)decode(mneumonico)*16*16*16;
                Mneumonico* m = procurar_mneumonico(mneumonico, TabelaDeMneumonicos);
                cout << "Exige operando? " << m->operando << endl;
                if (m->operando == true)
                {
                    Evento* proximo = atual->proximo;
                    atual->proximo = AnalisarOperando;
                    atual->proximo->proximo = proximo;
                }
                else
                {
                    Evento* proximo = atual->proximo;
                    atual->proximo = LeituraLinha;
                    atual->proximo->proximo = proximo;
                }
            }
            else
            {
                if (mneumonico == "K")
                {
                    codigo = captar_codigo(linha);
                    cout << "Codigo: " << codigo;
                    instrucao = ascii_to_dec(codigo);
                    codigogerado << hex << pc << " " << codigo << endl;
                    Evento* proximo = atual->proximo;
                    atual->proximo = LeituraLinha;
                    atual->proximo->proximo = proximo;
                    pc = pc++;
                }
                else
                {
                    cout << "Mneumonico nao encontrado" << endl;
                }
            }
        }
        if (atual->tipoDeReacao == "ANALISAR OPERANDO")
        {
            instrucao = instrucao + obter_endereco(op_ou_simb, TabelaDeSimbolos);
            codigogerado << hex << pc << " " << hex << instrucao << endl;

            Evento* proximo = atual->proximo;
            atual->proximo = LeituraLinha;
            atual->proximo->proximo = proximo;
            if (mneumonico == "K") pc++;
            else pc = pc + 2;
        }
        if (atual->tipoDeReacao == "FINAL")
        {
            cout << "PASSO: " << passo << endl;
            if (passo == 2){
                imprimirTabelaDeSimbolos(TabelaDeSimbolos);
                sair = 1;
                codigogerado.close();
            }
            if (passo == 1)
            {
                passo = 2;
                cout << "Construindo o novo arquivo\n";
                pc = 0;
                linhaAtual = 0;
                Evento* proximo = atual->proximo;
                atual->proximo = LeituraLinha;
                cout << "Atualizou evento\n";
            }
        }
        atual = atual->proximo;
    }
}

bool checar_tabela_simbolos(string rotulo, ListaLigada* TabelaDeSimbolos)
{
    /*(string,ListaLigada*)->bool
    Verifica se jah existe um simbolo com o rotulo passado pela string*/
    Simbolo* atual = TabelaDeSimbolos->sInicio->proximo;
    int achou = 0;
    while(atual!=TabelaDeSimbolos->sFinal && achou == 0)
    {
        if (atual->rotulo == rotulo)
        {
            achou = 1;
            return true;
        }
        atual = atual->proximo;
    }
    if (achou == 0)
    {
        return false;
    }
}

void atualizar_tabela_simbolos(ListaLigada* TabelaDeSimbolos, Simbolo* novo)
{
    Simbolo* atual = TabelaDeSimbolos->sInicio;
    while(atual!=TabelaDeSimbolos->sFinal->anterior)
    {
        atual = atual->proximo;
    }
        atual->proximo = novo;
        atual->proximo->anterior = atual;
        atual->proximo->proximo = TabelaDeSimbolos->sFinal;
        TabelaDeSimbolos->sFinal->anterior = atual->proximo;
}

void definir_simbolo(ListaLigada* TabelaDeSimbolos,string rotulo,uint16_t pc)
{
    Simbolo* atual = TabelaDeSimbolos->sInicio;
    int achou = 0;
    while(atual!=TabelaDeSimbolos->sFinal && achou == 0)
    {
        if (atual->rotulo == rotulo)
        {
            atual->endereco = pc;
            atual->status = "definido";
            achou = 1;
        }
        atual = atual->proximo;
    }
}


void imprimirTabelaDeSimbolos (ListaLigada* TabelaDeSimbolos)
{
    cout << "-------------------------------" << '\n';
    cout << "Imprimindo tabela de Simbolos: " << '\n';
    Simbolo* atual = TabelaDeSimbolos->sInicio->proximo;
    while (atual != TabelaDeSimbolos->sFinal)
    {
        cout << "Simbolo: " << atual->rotulo << endl;
        cout << "Status: " << atual->status << endl;
        if (atual->status == "definido") cout << "Endereco: " << atual->endereco << endl;
        atual = atual->proximo;
    }
    cout << "-------------------------------" << '\n';
}

void criar_tabela_mneumonicos(ListaLigada* TabelaDeMneumonicos)
{
    //0RG
    Mneumonico* ORG = new Mneumonico("ORG");
    TabelaDeMneumonicos->mInicio = ORG;

    Mneumonico* atual = TabelaDeMneumonicos->mInicio;

    Mneumonico* ENTRY = new Mneumonico("ENTRY");
    atual->proximo = ENTRY;
    atual = atual->proximo;

    Mneumonico* EXTERNAL = new Mneumonico("EXTERNAL");
    atual->proximo = EXTERNAL;
    atual = atual->proximo;

    Mneumonico* NAME = new Mneumonico("NAME");
    atual->proximo = NAME;
    atual = atual->proximo;

    Mneumonico* END = new Mneumonico("END");
    atual->proximo = END;
    atual = atual->proximo;

    //JUMP
    Mneumonico* JP = new Mneumonico("JP");
    atual->proximo = JP;
    atual = atual->proximo;
    atual->operando = true;

    //JUMP IF ZERO
    Mneumonico* JZ = new Mneumonico("JZ");
    atual->proximo = JZ;
    atual = atual->proximo;
    atual->operando = true;

    //JUMP IF NEGATIVE
    Mneumonico* JN = new Mneumonico("JN");
    atual->proximo = JN;
    atual = atual->proximo;
    atual->operando = true;

    //LV
    Mneumonico* LV = new Mneumonico("LV");
    atual->proximo = LV;
    atual = atual->proximo;

    //ADD
    Mneumonico* ADD = new Mneumonico("+");
    atual->proximo = ADD;
    atual = atual->proximo;
    atual->operando = true;

    //SUBTRACT
    Mneumonico* SUBTRACT = new Mneumonico("-");
    atual->proximo = SUBTRACT;
    atual = atual->proximo;
    atual->operando = true;

    //MULTIPLY
    Mneumonico* MULTIPLY = new Mneumonico("*");
    atual->proximo = MULTIPLY;
    atual = atual->proximo;
    atual->operando = true;

    //DIVIDE
    Mneumonico* DIVIDE = new Mneumonico("/");
    atual->proximo = DIVIDE;
    atual = atual->proximo;
    atual->operando = true;

    //LOAD FROM MEMORY
    Mneumonico* LD = new Mneumonico("LD");
    atual->proximo = LD;
    atual = atual->proximo;
    atual->operando = true;

    //STORE
    Mneumonico* MM = new Mneumonico("MM");
    atual->proximo = MM;
    atual = atual->proximo;
    atual->operando = true;

    //CALL SUBROUTINE
    Mneumonico* SC = new Mneumonico("SC");
    atual->proximo = SC;
    atual = atual->proximo;

    //RETURN FROM SUBROUTINE
    Mneumonico* RS = new Mneumonico("RS");
    atual->proximo = RS;
    atual = atual->proximo;

    //HALT MACHINE
    Mneumonico* HM = new Mneumonico("HM");
    atual->proximo = HM;
    atual = atual->proximo;

    //INPUT
    Mneumonico* GD = new Mneumonico("GD");
    atual->proximo = GD;
    atual = atual->proximo;

    //OUTPUT
    Mneumonico* PD = new Mneumonico("PD");
    atual->proximo = PD;
    atual = atual->proximo;

    //OPERATING SYSTEM CALL
    Mneumonico* OS = new Mneumonico("OS");
    atual->proximo = OS;
    atual = atual->proximo;

    TabelaDeMneumonicos->mFinal = atual;

}

bool verificar_mneumonico(string mneumonico, ListaLigada* TabelaDeMneumonicos)
{
    bool achou = false;
    Mneumonico* atual = TabelaDeMneumonicos->mInicio;
    while(atual!=TabelaDeMneumonicos->mFinal && achou == false)
    {
        if (atual->mneumonico == mneumonico)
        {
            cout << "Encontrou Mneumonico\n";
            achou = true;
        }
        atual = atual->proximo;
    }
    if (achou == false)
    {
        if (mneumonico == atual->mneumonico)
        {
            cout << "Encontrou Mneumonico \n";
            achou = true;
        }
    }
    return achou;
}

void split_linha(string linha, string mneumonico, string op_ou_simb)
{
    stringstream ss(linha);
    vector<string> tokens;
    string buf, buf1, buf2;
    int cont=0;
    while (ss >> buf)
    {
        tokens.push_back(buf);
        if (cont == 0)
        {
            buf1 = buf;
            cout << buf1 << endl;
            mneumonico = buf1;
        }
        if (cont == 1)
        {
            buf2 = buf;
            cout << buf2 << endl;
            op_ou_simb = buf2;
        }
        cont++;
    }
    cout << "Gravou com sucesso" << endl;
    cout << mneumonico << '\n';
    cout << op_ou_simb << '\n';
}

string captar_mneumonico (string linha)
{
    stringstream ss(linha);
    vector<string> tokens;
    string buf, buf1, buf2;
    int cont=0;
    while (ss >> buf)
    {
        tokens.push_back(buf);
        if (cont == 0)
        {
            buf1 = buf;
        }
        cont++;
    }
    return buf1;
}

string captar_op_ou_simbolo(string linha)
{
    stringstream ss(linha);
    vector<string> tokens;
    string buf, buf1, buf2;
    int cont=0;
    while (ss >> buf)
    {
        tokens.push_back(buf);
        if (cont == 1)
        {
            buf2 = buf;
        }
        cont++;
    }
    return buf2;
}

string captar_codigo(string linha)
{
    stringstream ss(linha);
    vector<string> tokens;
    string buf, buf3;
    int cont=0;
    while (ss >> buf)
    {
        tokens.push_back(buf);
        if (cont == 2)
        {
            buf3 = buf;
        }
        cont++;
    }
    return buf3;
}

uint16_t ascii_hex(char texto)
{
    if (texto == '0') return 0x0;
    if (texto == '1') return 0x1;
    if (texto == '2') return 0x2;
    if (texto == '3') return 0x3;
    if (texto == '4') return 0x4;
    if (texto == '5') return 0x5;
    if (texto == '6') return 0x6;
    if (texto == '7') return 0x7;
    if (texto == '8') return 0x8;
    if (texto == '9') return 0x9;
    if (texto == 'A') return 0xa;
    if (texto == 'B') return 0xb;
    if (texto == 'C') return 0xc;
    if (texto == 'D') return 0xd;
    if (texto == 'E') return 0xe;
    if (texto == 'F') return 0xf;
}

uint8_t decode(string codigo){
    if (codigo == "JP") return 0x0;
    if (codigo == "JZ") return 0x1;
    if (codigo == "JN") return 0x2;
    if (codigo == "LV") return 0x3;
    if (codigo == "+")  return 0x4;
    if (codigo == "-")  return 0x5;
    if (codigo == "*")  return 0x6;
    if (codigo == "/")  return 0x7;
    if (codigo == "LD") return 0x8;
    if (codigo == "MM") return 0x9;
    if (codigo == "SC") return 0xa;
    if (codigo == "RS") return 0xb;
    if (codigo == "HM") return 0xc;
    if (codigo == "GD") return 0xd;
    if (codigo == "PD") return 0xe;
    if (codigo == "OS") return 0xf;
}

uint16_t obter_endereco (string simbolo,ListaLigada* TabelaDeSimbolos)
{
    Simbolo* atual = TabelaDeSimbolos->sInicio;
    bool achou = false;
    uint16_t endereco;
    while(atual!=TabelaDeSimbolos->sFinal && achou == false)
    {
        if (simbolo == atual->rotulo)
        {
            endereco = atual->endereco;
            achou = true;
        }
        atual = atual->proximo;
    }
    if (achou == false)
    {
        endereco = atual->endereco;
        achou = true;
    }
    return endereco;
}

uint16_t ascii_to_dec(string codigo)
{
    int i;
    uint16_t resultado = 0;
    uint16_t fator;
    for (i=0; i< codigo.size(); i++)
    {
        if (codigo[i] < 57) fator = (uint16_t)codigo[i] - 48;
        else fator = (uint16_t)codigo[i] - 55;
        resultado = resultado+fator*(uint16_t)pow(16,((codigo.size()-i)));
    };
}

Mneumonico* procurar_mneumonico(string mneumonico, ListaLigada* TabelaDeMneumonicos)
{
    Mneumonico* atual = TabelaDeMneumonicos->mInicio;
    bool achou = false;
    while (atual!= TabelaDeMneumonicos->mFinal && achou == false)
    {
        if (mneumonico == atual->mneumonico)
        {
            return atual;
            achou = true;
        }
        atual = atual->proximo;
    }
    if (achou == false)
    {
        if (mneumonico == atual->mneumonico) return atual;
    }
}

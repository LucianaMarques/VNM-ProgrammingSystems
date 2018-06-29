#ifndef MNEUMONICO_H_INCLUDED
#define MNEUMONICO_H_INCLUDED

#include <iostream>
using namespace std;

class Mneumonico
{
public:
    string mneumonico;
    uint8_t codigo;
    string classe;
    bool operando = false;
    Mneumonico* proximo;

    Mneumonico(string mne);
    ~Mneumonico();
};

#endif // MNEUMONICO_H_INCLUDED

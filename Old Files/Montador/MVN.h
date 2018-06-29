#ifndef MVN_H_INCLUDED
#define MVN_H_INCLUDED

#include <iostream>
using namespace std;

class MVN {
public:
    uint8_t memoria[0xFFF];
    uint16_t acc;
    uint16_t arg;
    uint16_t pc = 0;
    uint16_t instrucao;
    MVN();
    ~MVN();
};

#endif // MVN_H_INCLUDED

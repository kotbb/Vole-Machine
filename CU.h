
#ifndef VOLE_MACHINE_CU_H
#define VOLE_MACHINE_CU_H

#include "Register.h"
#include "Memory.h"
#include "ALU.h"


// CU (Control Unit) class
class CU {
public:
    void load(int idReg, int intMem, Register& reg, Memory& mem);

    void load(int idReg, string &valInt, Register& reg);
    //>
    string loadReg(int &id,Register& reg);
    //>
    void jumpGreater(int regVal, int idMem, int& programCount,int regZeroVal);

    void store(int idReg, int idMem, Register& reg, Memory& mem);
    //>
    void copy(int idReg1, int idReg2, Register& reg);
    //>
    void jump(int regVal, int idMem, int& programCount,int regZeroVal);

    void halt();
};


#endif //VOLE_MACHINE_CU_H

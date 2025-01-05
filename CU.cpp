#include <bits/stdc++.h>
using namespace std;
#include "CU.h"

// CU (Control Unit) class

    // load the reg with the value at a memory
    void CU::load(int idReg, int intMem, Register &reg, Memory &mem) {
        reg.setCell(idReg, mem.getCell(intMem));
    }
    // load the reg with hexa value
    void CU::load(int idReg, string &valHex, Register& reg) {
        reg.setCell(idReg, valHex);
    }
    // load the hexa value that is in the reg
    string CU::loadReg(int &id, Register &reg)
    {
        return reg.getCell(id);
    }
    // store the value at the reg into the XY memory
    void CU::store(int idReg, int idMem, Register& reg, Memory& mem) {
        mem.setCell(idMem, reg.getCell(idReg));
    }
    // copy the value at reg1 to the reg2
    void CU::copy(int idReg1, int idReg2, Register& reg) {
        reg.setCell(idReg2, reg.getCell(idReg1));
    }
    // jump to a memory address if the value at reg R equals to the value at reg 0
    void CU::jump(int regVal, int idMem, int& programCount,int regZeroVal) {
        if (regVal == regZeroVal) {
            programCount = idMem;
        }
    }
    // jump to a memory address if the value at reg R greater than the value at reg 0
    void CU::jumpGreater(int regVal, int idMem, int &programCount,int regZeroVal) {
        if(regVal > regZeroVal) {
            programCount = idMem;
        }
    }
    // print the halt of the program
    void CU::halt() {

        cout << "Execution halted." << endl;
    }



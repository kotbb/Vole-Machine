
#ifndef VOLE_MACHINE_MACHINE_H
#define VOLE_MACHINE_MACHINE_H
#include "CPU.h"



// Machine class
class Machine {
private:
    CPU processor;
    Memory memory;

public:
    void loadProgramFile();
    void clearMemory();
    void clearRegister();
    //>
    void clearCounter();
    void loadInstruction();
    void loadCounter();
    void outputState();

    void runProgram();

};
#endif //VOLE_MACHINE_MACHINE_H

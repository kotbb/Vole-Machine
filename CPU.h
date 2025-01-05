
#ifndef VOLE_MACHINE_CPU_H
#define VOLE_MACHINE_CPU_H

#include "ALU.h"
#include "CU.h"

// CPU class
class CPU {
private:
    int programCounter = 10;
    string instructionRegister;
    vector <string> expectedOut;
    Register registerFile;
    ALU alu;
    CU cu;
public:
    CPU();
    int getProgramCounter() const;
    string getCurrentInstruction() const;
    void untilHalt(Memory &memory);
    void setExpectedOut(string op1);
    void setMemAddress(string memoryAdd);
    void runNextStep(Memory &memory);
    void setCounter(string &counter);
    void fetch(Memory &memory);
    void decode(int &opCode, int &R, int &X, int &Y);
    void execute(int &opCode, int &R, int &X, int &Y, Register &reg, Memory &memory);
    void displayStatus(const Memory &memory) ;
    void clearRegister();
    void clearCount();
    bool validMemory(string &mem);
    bool validInstruction(string &inst);
    int convertMem(string &hexaMem);
};


#endif //VOLE_MACHINE_CPU_H

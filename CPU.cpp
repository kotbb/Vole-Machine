#include <bits/stdc++.h>
using namespace std;
#include "CPU.h"
    // constructor to initialize the program Counter
    CPU::CPU()
    {
        programCounter = 10;
    }
    // Getter for current ProgramCounter
    int CPU::getProgramCounter() const {
        return programCounter;
    }
    // setter to set the counter you want to begin with
    void CPU::setCounter(string &counter) {
        if(alu.isDec(counter) )
        {
            int count = stoi(counter);
            if(alu.validCounter(count))      // check if it valid counter and is even.
                programCounter = count;
            else
                cout << "Failed to set the counter.\n"
                        "It is not an even number.  Note: memory size = 256 only\n";
        }
        else
        {
            cout << "Failed to set the counter\n"
                    "Not an integer number.\n";
        }
    }
    // Getter for current instruction
    string CPU::getCurrentInstruction() const {
        return instructionRegister;
    }
    // to run until halt in the run one step
    void CPU::untilHalt(Memory &memory) {
        while (getProgramCounter() < 256) {
            runNextStep(memory);
            if (getCurrentInstruction() == "C000") { // to break the program
                cout << "Program halted by HALT instruction." << endl;
                break;
            }
        }
    }
    // run the program and fetch the memory and decode it and then perform the instructions
    void CPU::runNextStep(Memory &memory) {
        fetch(memory);      // to get the instruction register from the memory
        if(!alu.validInst(instructionRegister)) // check it is valid instruction
        {
            return;
        }
        int opCode,R,X,Y;
        decode(opCode,R,X,Y);
        execute(opCode,R,X,Y, registerFile, memory); // perform the instruction
    }
    // setter for memory address to begin the program from it
    void CPU::setMemAddress(string memoryAdd) {
        programCounter = alu.hexToDec(memoryAdd);
    }
    // to clear the counter
    void CPU::clearCount() {
        programCounter = 10;
    }
    // convert the memory into decimal value
    int CPU::convertMem(string &hexaMem) {
        return alu.hexToDec(hexaMem);
    }
    // setter for adding the output to the console
    void CPU::setExpectedOut(std::string op1) {
        expectedOut.push_back(op1);
    }
    void CPU::fetch(Memory &memory) {
        string op1,op2;
        op1 = memory.getCell(programCounter);
        programCounter++;
        op2 = memory.getCell(programCounter);
        instructionRegister = op1 + op2;
        programCounter++;
    }
    // extract the opcode,R,X,Y
        void CPU::decode(int &opCode, int &R, int &X, int &Y) {
         opCode = alu.hexToDec(instructionRegister[0]);
         R = alu.hexToDec(instructionRegister[1]);
         X = alu.hexToDec((instructionRegister[2]));
         Y = alu.hexToDec((instructionRegister[3]));
    }
    // execute the instructions
    void CPU::execute( int &opCode, int &R, int &X, int &Y, Register &reg, Memory &memory) {
        string OR,XOR,AND,rotated,resFloat;
        int xReg = alu.hexToDec(cu.loadReg(X,reg)),yReg = alu.hexToDec(cu.loadReg(Y,reg))
                   ,rReg = alu.hexToDec(cu.loadReg(R,reg));     // the values that are in these registers
        string hexVal = instructionRegister.substr(2,2);    // the hexVal of X,Y
        int memAdd = alu.hexToDec(instructionRegister.substr(2,2));     // get the memory address
        if(instructionRegister == "0000")
            return;
        switch (opCode) {
            // load the register R with that in the memory XY
            case 1:
                cu.load(R,memAdd, reg, memory);
                break;
            // load the register with value XY
            case 2:
                cu.load(R, hexVal , reg);
                break;
            // store the memory XY with the value at register R
            case 3:
                if(X+Y == 0)
                    expectedOut.push_back(alu.decToHex(rReg));  // if the memory is 00 print it to the screen
                else
                    cu.store(R, memAdd, reg, memory);
                break;
            // copy the value at reg X to the reg Y
            case 4:
                cu.copy(X, Y, reg);
                break;
            // add the 2nd complement of two registers
            case 5:
                alu.add(R, X, Y, reg);
                break;
            // add the float point of two registers with explicit
            case 6:
                resFloat = alu.addFloat(X,Y,reg);
                cu.load(R,resFloat,reg);
                break;
            // function to get the OR of two registers
            case 7:

                OR = alu.OR(xReg,yReg);
                cu.load(R,OR,reg);
                break;
            // function to get the AND of two registers
            case 8:

                AND = alu.AND(xReg,yReg);
                cu.load(R,AND,reg);
                break;
            // function to get the XOR of two registers
            case 9:

                XOR = alu.XOR(xReg,yReg);
                cu.load(R,XOR,reg);
                break;
            // rotate the bin value of a register
            case 10:
                rotated = alu.rotateBin(rReg, X + Y);
                cu.load(R, rotated, reg);
                break;
            // to jump to a memory if the reg R equals to reg 0
            case 11:
                if(alu.hexToDec(hexVal) % 2 == 0)
                {
                    int regZeroVal = alu.hexToDec(reg.getCell(0));
                    cu.jump(rReg, memAdd, programCounter,regZeroVal);
                }
                else  // must be even to run the program correctly
                {
                    cout << "Invalid Memory (it must be an even address)\n";
                }
                break;
            // halt execution
            case 12:
                cu.halt();
                break;
            // to jump to a memory if the reg R greater than reg 0
            case 13:
                if(alu.hexToDec(hexVal) % 2 == 0)
                {
                    int regZeroVal = alu.hexToDec(reg.getCell(0));
                    cu.jumpGreater(rReg, memAdd,programCounter,regZeroVal);
                }
                else
                {
                    cout << "Invalid Memory (it must be an even address)\n";
                }
                break;

            default:
                break;
        }
    }
    // check the validation of the memory input
    bool CPU::validMemory(string &mem)
    {
        return alu.validMemory(mem);
    }
    // check the validation of the instruction input
    bool CPU::validInstruction(string &inst) {
        return alu.validInst(inst);
    }
    // display the status of the machine and the console
    void CPU::displayStatus(const Memory &memory)  {
        cout << "Program Counter (PC): " << programCounter << endl;
        cout << "Instruction Register (IR): " << instructionRegister << endl;
        cout << "Registers  Hex  Int  Binary  Floating" << endl;
        for (int i = 0; i < 16; ++i) {
            cout << "  R[" << alu.decToHex(i) << "]" << ":" << "\t   " << registerFile.getCell(i) << "   "
            << alu.hexToSecondComp(registerFile.getCell(i)) << "  "<< alu.hexToBin(registerFile.getCell(i))
            << "  "<< alu.hexToFloat(registerFile.getCell(i)) << endl;

        }
        cout << "\nMemory State:\n";
        for (int i = 0; i < 256; ++i) {
            cout << "M[" << setw(1) << setfill('0') << ALU::decToHex(i) << "] = " << memory.getCell(i) << "  ";
            if ((i + 1) % 8 == 0) cout << endl;
        }
        cout << endl;
        cout << "Console:\n" << "Ascii:";
        for(const string& str : expectedOut)
        {
            int dec = alu.hexToDec(str);
            char ascii = dec;
            cout << ascii;
        }
        cout << endl;
        cout << "Hexa:";
        for(const string& str : expectedOut)
        {
            cout << str;
        }
        cout << endl;
    }
    // to clear the register
    void CPU::clearRegister() {
        registerFile.clear();
    }




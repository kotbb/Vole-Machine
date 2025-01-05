#include <bits/stdc++.h>
using namespace std;
#include "Register.h"

    // constructor to intialize the cells of the register with 00
    Register::Register(){
        memory.resize(size,"00");
    }
    // getter for the cell of the reg
    string Register::getCell(int address) const {
        if (address >= 0 && address < size) {
            return memory[address];
        }
        return "00";
    }
    // setter for the value to some register
    void Register::setCell(int address, string val) {
        if (address >= 0 && address < size) {
            memory[address] = val;
        }
    }
    // to clear the register
    void Register::clear() {
        fill(memory.begin(),memory.end(),"00");
    }




#include <bits/stdc++.h>
using namespace std;
#include "Memory.h"

    // constructor to intialize all the cell of the memory with 00
    Memory::Memory(){
        memory.resize(size,"00");
    }
    // to get the cell of a memory
    string Memory::getCell(int address) const {
        if (address >= 0 && address < size) {
            return memory[address];
        }
        return "00";
    }
    // to set a cell of a memory to a specific hexa value
    void Memory::setCell(int address, const string& val) {
        if (address >= 0 && address < size) {
            memory[address] = val;
        }
    }
    // to clear the memory
    void Memory::clear() {
        fill(memory.begin(), memory.end(), "00");
    }





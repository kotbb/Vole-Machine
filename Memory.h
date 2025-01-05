
#ifndef VOLE_MACHINE_MEMORY_H
#define VOLE_MACHINE_MEMORY_H
#include <bits/stdc++.h>
using namespace std;
class Memory {
private:
    vector<string> memory;
    static const int size = 256;

public:
    Memory();
    string getCell(int address) const;

    void setCell(int address, const string &val);
    void clear();

};
#endif //VOLE_MACHINE_MEMORY_H

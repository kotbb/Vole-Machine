
#ifndef VOLE_MACHINE_REGISTER_H
#define VOLE_MACHINE_REGISTER_H
#include <bits/stdc++.h>
using namespace std;
// Register class
class Register {
private:
    vector<string> memory;
    static const int size = 16;

public:
    Register();
    string getCell(int address) const;

    void clear();
    void setCell(int address, string val);

};

#endif //VOLE_MACHINE_REGISTER_H

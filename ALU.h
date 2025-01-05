

#ifndef VOLE_MACHINE_ALU_H
#define VOLE_MACHINE_ALU_H
#include "Register.h"
#include "Memory.h"

class ALU {
public:

    static int hexToDec(const string& hex);
    string floatToBinary(float num);
    static int hexToDec(const char& ch);
    static string decToHex(int decimal);
    string rotateBin(int &dec, int steps);
    float hexToFloat(string hex);
    string decToBin(int dec);
    string OR(int d1,int d2);
    string XOR(int d1,int d2);
    string AND(int d1,int d2);
    void add(int idx1, int idx2, int idx3, Register& reg);
    string addFloat(int id2, int id3, Register& reg);
    //>
    string binTohex(string binStr);
    string convertExplicit(string bin);
    int hexToSecondComp(string hex);
    static bool isDec(const char& hexCh);
    static string hexToBin(string hex);
    static bool isHexaChars(const char& hexCh);
    bool validMemory(string& str);
    bool validInst(string& inst);
    bool isDec(const string &str);
    bool validCounter(int &count);
};

#endif //VOLE_MACHINE_ALU_H

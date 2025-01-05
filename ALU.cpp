#include <bits/stdc++.h>
using namespace std;
#include "ALU.h"

    string ALU::floatToBinary(float num) {
        if (num == 0) return "0";
        // Handle the sign
        string binary = (num < 0) ? "-" : "";
        num = fabs(num);              // return the absolute of the float

        //  Convert the integer part to binary
        int integerPart = static_cast<int>(num);
        string intBinary;
        while (integerPart > 0) {
            intBinary = to_string(integerPart % 2) + intBinary;
            integerPart /= 2;
        }
        binary += (intBinary.empty()) ? "0" : intBinary;

        // Convert the fractional part to binary
        double fractionalPart = num - static_cast<int>(num);
        if (fractionalPart > 0) {
            binary += ".";
            while (fractionalPart > 0) {
                fractionalPart *= 2;
                int bit = static_cast<int>(fractionalPart);
                binary += to_string(bit);
                fractionalPart -= bit;

                // Limit to avoid infinite loop due to precision issues
                if (binary.length() > 8) break; // Limit precision to 8 bits
            }
            return binary;
        }
    }
    string ALU::OR(int d1, int d2) {
        int res = d1 | d2;
        return decToHex(res);
    }
    string ALU::XOR(int d1, int d2) {
        int res = d1 ^ d2;
        return decToHex(res);
    }
    string ALU::AND(int d1, int d2) {
        int res = d1 & d2;
        return decToHex(res);
    }
    string ALU::rotateBin(int &dec, int steps) {
        string binStr = decToBin(dec);
        for (int i = 0; i < steps ; ++i) {
            char ch = binStr[binStr.size()-1];
            binStr = ch + binStr;
            binStr.erase(binStr.size()-1);
        }
        dec = stoi(binStr, nullptr, 2);
        return decToHex(dec);
    }
    // to convert the hexa string into decimal
    int ALU::hexToDec(const string& hex)
    {
         return stoi(hex, nullptr, 16);
    }
    // to convert the hexa char into decimal
    int ALU::hexToDec(const char &ch)
    {
        string hex;
        hex += ch;
        return stoi(hex, nullptr, 16);
    }
    string ALU::convertExplicit(string bin)
    {

        int before = 0,posPoint = 1,sign = 0,expInt;
        string newEx,expStr;
        bool firstPoint = false;
        int n = bin.size()-1;
        if(bin[1] == '0')              // to check if the float bin contains an integer part
            firstPoint = true;
        if(bin[0] == '-')              // to check the sign of the first bit
        {
            n--;
            sign = 1;
        }
        string mantissa;
        if(firstPoint)
        {
            int shift = 0;
            bool check = false;
            // here to get the mintessa
            for (int i = 3; i < bin.size() ; ++i) {
                if(bin[i] == '1')
                {
                    check = true;
                    mantissa += '1';

                }
                else if(!check)
                    shift++;
            }
            while(mantissa.size() < 4)
                mantissa += '0';                   // to fill the mantisaa to 4 bits
            expInt = shift + n;                   // size of the binaries + shift
            bitset <8> expBin(expInt);
            expStr = expBin.to_string();
        }
        else
        {
            // to get the mintessa
            for (int i = 1; i < bin.size() ; ++i) {
                if(bin[i] != '.')
                {
                    mantissa += bin[i];
                    before++;
                }
                else
                {
                    posPoint = i;
                    break;
                }
            }
            mantissa += bin.substr(posPoint+1);
            expInt = before + n;
            bitset<8> expBin(expInt);
            expStr = expBin.to_string();
        }
        bool check = false;
        for (int i = 0; i < 8 ; ++i) {
            if(expStr[i] != '0')
                check = true;
            if(check)
                newEx += expStr[i];
        }
        string resBin;
        resBin += (sign) ? '1' : '0';
        resBin += newEx;
        resBin += mantissa;
        return resBin;
    }
    //convert bin to hex
    string ALU::binTohex(std::string binStr) {
        bitset <8> bin(binStr);
        int dec = bin.to_ulong();
        return decToHex(dec);
    }
    // add float with explicit method
    string ALU::addFloat(int id2, int id3, Register &reg) {
        string hex1 = reg.getCell(id2);
        string hex2 = reg.getCell(id3);
        float f1 = hexToFloat(hex1);
        float f2 = hexToFloat(hex2);
        float result = f1 + f2;                         // the result of the adding the floating of the two hexa
        string resBin = floatToBinary(result);       // convert the float into float binary
        string floatBin = convertExplicit(resBin);  // convert the float binary into 8 bits binary
        return binTohex(floatBin);

    }
    // convert from hex decimal to binary
    string ALU::hexToBin(string hex)
    {
        int dec = hexToDec(hex);
        bitset<8> bin(dec);
        return bin.to_string();
    }
    // to convert the hexa into float number
    float ALU::hexToFloat(string hex) {
        // Convert hexadecimal string to binary
        string bin = hexToBin(hex);

        string signBit = bin.substr(0, 1);             // 1 bit for sign
        string exponentBits = bin.substr(1, 3);        // 3 bits for exponent
        string mantissaBits = bin.substr(4, 4);        // 4 bits for mantissa

        // Convert string bits to integers
        int sign = stoi(signBit, nullptr, 2);
        int exponent = stoi(exponentBits, nullptr, 2);
        int mantissa = stoi(mantissaBits, nullptr, 2);

        // Calculate the floating-point value
        float decimalMantissa = static_cast<float>(mantissa) / 16.0f; // Mantissa scaled by 16
        float finalExponent = pow(2, static_cast<int>(exponent) - 4);// Exponent shifted by 4
        if(sign) sign = -1;
        else sign = 1;
        float result = decimalMantissa * finalExponent * sign; // Apply sign

        return result;
    }
    // convert from decimal to binary
    string ALU::decToBin(int dec)
    {
        bitset<8> bin(dec);
        return bin.to_string();
    }
    // check the valid memory
    bool ALU::validMemory(string &str) {
        if(str.length() > 2)
            return false;
        for(char ch : str)
        {
            if(!isdigit(ch) && !(isHexaChars(ch)))  // to check if it is digit or from the hexa chars
                return false;
        }
        int dec = hexToDec(str);
        if(dec % 2 != 0)   // to check if it is even or odd, it must be even
            return false;
        return true;
    }
    // convert from hexa string into second complement decimal
    int ALU::hexToSecondComp(string hex) {
        string bin = hexToBin(hex);
        int dec = hexToDec(hex);
        if(bin[0] == '1')     // check the sign of the binary
            dec = dec - 256;
        return dec;
    }
    // check the validation of the counter
    bool ALU::validCounter(int &count) {
        if(count < 0 || count > 255 || count % 2 != 0)
            return false;
        return true;
    }
    // convert from decimal to hexa
    string ALU::decToHex(int decimal) {
        if(decimal < 0)
            decimal = decimal + 256;
        stringstream ss;
        ss << hex << uppercase << decimal;
        return ss.str();
    }
    // check the char is a digit
    bool ALU::isDec(const char& hexCh) {

        if(isdigit(hexCh)) return true;
        else
            return false;

    }
    // check if the string contains only digits
    bool ALU::isDec(const string& str) {
        for(char ch : str)
        {
            if(!isdigit(ch)) return false;
        }
        return true;
    }
    // check if the char is from the hexa chars
    bool ALU::isHexaChars(const char& hexCh) {
        string hexaChars = "ABCDEF";
        for(char ch : hexaChars)
        {
            if(hexCh == ch)
                return true;
        }
        return false;
    }

    void ALU::add(int idx1, int idx2, int idx3, Register &reg) {
        int sum = hexToSecondComp(reg.getCell(idx2)) + hexToSecondComp(reg.getCell(idx3));
        reg.setCell(idx1, decToHex(sum));
    }
    // check the validation of the instruction
    bool ALU::validInst(string &inst)
    {
        if(inst.size() != 4)    // if the size < 4, it's not valid
            return false;
        if(inst == "0000")
            return true;
        string validChars = "0123456789ABCDEF";
        bool validOp = false;
        // this check the validation of the opCode
        for(int i = 1 ; i < validChars.size() - 2; i++)
        {
            if(inst[0] == validChars[i])
                validOp = true;
        }
        if(!validOp)
            return false;
        // check the validation of the R,X,Y
        for (int i = 1; i <= 3 ; ++i) {
            bool validRes = false;
            for (char ch : validChars) {
                if(inst[i] == ch)
                    validRes = true;
            }
            if(!validRes)
                return false;
        }
        return true;
    }


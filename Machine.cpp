#include <bits/stdc++.h>
using namespace std;

#include "Machine.h"

    // load the program with a file of inputs
    void Machine::loadProgramFile() {
        while(true)
        {
            string filename;
            cout << "Enter filename:";
            cin >> filename;
            ifstream file(filename);
            if(!file.is_open())           // check if the file isn't valid
            {
                cout << "Invalid filename..\n";
                continue;
            }
            string line;
            int address = 10,c = 0;       // begin the program at the memory 10
            while (getline(file, line) && address < 256) {
                if(line.size() != 4)         // check if the size of instruction less than 4
                {
                    cout << "Invalid Instruction: size less than 4 at line:" << c << endl;
                    continue;
                }
                // divide the instruction into two parts and fill each part to two corresponding memories
                string op1,op2;
                op1 = line.substr(0,2);
                op2 = line.substr(2,2);
                memory.setCell(address, op1);
                address++;
                if(address < 256)
                    memory.setCell(address, op2);
                address++;
                c++;
            }
            break;
        }
    }
    // to clear the counter of the program
    void Machine::clearCounter() {
        processor.clearCount();
    }
    // load an instruction and fill it to a specific memory
    void Machine::loadInstruction() {
        while (true) {
            string inst;
            cout << "Enter the instruction:";
            cin >> inst;
            if (!processor.validInstruction(inst)) {   // check the validation of the instruction
                cout << "Invalid instruction...\n";
                continue;
            }
            string mem;
            cout << "Enter the memory you want to put the instruction:";
            cin >> mem;
            if (!processor.validMemory(mem)) {         // check the validation of the memory
                cout << "Invalid Memory...\n";
                continue;
            }
            int address = processor.convertMem(mem);  // converts the hexa address into decimal
            // divide the instruction
            string op1 = inst.substr(0,2);
            string op2 = inst.substr(2,2);
            // check if the memory is 0 to value at the console
            if(address == 0)
                processor.setExpectedOut(op1);
            else
                memory.setCell(address,op1);
            address++;
            if(address < 256)
                memory.setCell(address,op2);
            break;
        }
    }
    // show the state of the machine with some details
    void Machine::outputState() {
        processor.displayStatus(memory);
    }
    // input the counter if he wants to specify a counter to begin the program with
    void Machine::loadCounter() {
        string counter;
        cout << "Please enter the number of counter you want:";
        cin >> counter;
        processor.setCounter(counter);
    }
    // this functions runs the program and give some choices to know how to run the program
    void Machine::runProgram() {
        while(true)
        {
            string choice;
            cout << "Enter what you want:\n"
                    "1. Run until halt.\n"
                    "2. Run one cycle.\n"
                    "3. Load the memory address you want to perform the instruction\n";
            cin >> choice;
            if(choice == "1")
            {
                processor.untilHalt(memory);
            }
            else if (choice == "2")
            {
                processor.runNextStep(memory);
                break;
            }
            else if(choice == "3")
            {
                while(true)
                {
                    string memoryChoice;
                    // the memory must be even to ensure that the program runs correctly
                    cout << "Enter the address you want to fetch (it must be even hexa number)\n";
                    cin >> memoryChoice;
                    if(!processor.validMemory(memoryChoice))
                    {
                        cout << "Invalid Memory (it must be even hexa number)\n"
                                "Note: Size of memory = 256\n";
                        continue;
                    }
                    else
                    {
                        while(true)
                        {
                            // here to make the program begin with the memory you input
                            processor.setMemAddress(memoryChoice);
                            string ch;
                            // choice if you want to run the program until there is halt or this memory only
                            cout << "1. Until halt\n"
                                    "2. this memory only\n";
                            cin >> ch;
                            if(ch == "1")
                                processor.untilHalt(memory);
                            else if (ch == "2")
                                processor.runNextStep(memory);
                            else
                            {
                                cout << "Invalid choice...\n";
                                continue;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            else
            {
                cout << "Invalid Choice\n";
                continue;
            }
            break;
        }
        // to print the state of the machine after every run of the program
       outputState();
    }
    // clear the memory
    void Machine::clearMemory() {
        memory.clear();
    }
    // clear the register
    void Machine::clearRegister() {
        processor.clearRegister();
    }



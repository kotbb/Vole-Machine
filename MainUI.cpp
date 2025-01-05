
#include <bits/stdc++.h>
using namespace std;

#include "MainUI.h"

    // the main menu that the user can interface with the machine
    void MainUI::DisplayMenu() {
        cout << "**************** Main Menu ****************\n"
         "1. Enter the counter you want to begin with\n"
         "2. Load instructions from a file\n"
         "3. Enter an instruction and set it to a specific memory\n"
         "4. Run the Program\n"
         "5. Display State\n"
         "6. Clear memory\n"
         "7. Clear register\n"
         "8. Clear counter\n"
         "9. Exit\n";
    }
    // to input the choice of the user
    void  MainUI::inputChoice() {
        string choice;
        while (true) {
            DisplayMenu();
            cout << "Enter choice:";
            cin >> choice;
            // load the counter that he wants to begin the program with
            if(choice == "1")
            {
                machine.loadCounter();
            }
            // load the file that has inputs and fill them to the memory
            else if (choice == "2")
            {
                machine.loadProgramFile();
            }
            // load one instruction and specify it to a memory
            else if(choice == "3")
            {
                machine.loadInstruction();
            }
            // runs the program
            else if(choice == "4")
                machine.runProgram();

            // if the user want to display the result and the state of the machine
            else if(choice == "5")
                machine.outputState();

            // to clear the memory
            else if(choice == "6")
            {
                machine.clearMemory();
                cout << "Memory cleared.\n";
            }
            // to clear the register
            else if(choice == "7")
            {
                machine.clearRegister();
                cout << "Register cleared.\n";
            }
            else if(choice == "8")
            {
                machine.clearCounter();
                cout << "Counter cleared.\n";
            }
            // to exit the program
            else if(choice == "9")
            {
                cout << "Exiting the program\n"
                        "Hava a nice time.";
                return;
            }
            else
                cout << "Invalid choice!" << endl;

        }
    }






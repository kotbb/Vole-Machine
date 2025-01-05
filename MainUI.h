
#ifndef VOLE_MACHINE_MAINUI_H
#define VOLE_MACHINE_MAINUI_H
#include "Machine.h"
#include "CPU.h"
#include "CU.h"

// MainUI class
class MainUI {
private:
    Machine machine;

public:

    void DisplayMenu();
    void inputChoice();

};


#endif //VOLE_MACHINE_MAINUI_H

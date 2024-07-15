// inscount.cpp
#include "pin.H"
#include <iostream>
#include <fstream>

std::ofstream OutFile;

// The running count of instructions is kept here
UINT64 icount = 0;

// This function is called before every instruction is executed
VOID docount() { icount++; }

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    OutFile.setf(std::ios::showbase);
    OutFile << "Count " << icount << std::endl;
    OutFile.close();
}

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    // Insert a call to docount before every instruction, no arguments are passed
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
}

// This function is called when the application starts
VOID Start()
{
    OutFile.open("inscount.out");
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char *argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) {
        return 1;
    }

    Start();

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}
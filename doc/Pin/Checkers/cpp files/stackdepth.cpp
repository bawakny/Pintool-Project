
#include "pin.H"
namespace WINDOWS
{
#include<Windows.h>
}
#include<stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>


std::ofstream OutFile;

double maxDepth = 0;
/* ==================================================================== */
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "stackdepth.csv", "specify trace file name");

/* ==================================================================== */
INT32 Usage()
{
    cerr <<
        "This tool prints stacks maximum depth.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


VOID MaxDepth(REG esp1){
	static REG base=esp1;
		
	 if(base-esp1 > maxDepth){
		 maxDepth=base-esp1;
	 }
	
}


VOID Instruction(INS ins, VOID *v){
	
	
	INS_InsertCall(ins,IPOINT_BEFORE, (AFUNPTR)MaxDepth, IARG_REG_VALUE, REG_ESP, IARG_END);
	
	
}


/* =============================- Instrumentation routines -============================== */
   


VOID Fini(INT32 code, VOID *v)
{

	
	OutFile<<maxDepth << endl;
	
    OutFile.close();
}

/* ===================================================================== */

int main(int argc, char *argv[])
{
    
    //PIN_InitSymbols();
    if( PIN_Init(argc,argv) )   return Usage();
  	   
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.open(KnobOutputFile.Value().c_str());
	INS_AddInstrumentFunction(Instruction, 0);  
    PIN_AddFiniFunction(Fini, 0);
	
    // Never returns
    PIN_StartProgram();
    
    return 0;
}




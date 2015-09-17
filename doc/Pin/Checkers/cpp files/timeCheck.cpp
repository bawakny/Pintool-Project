/*
 *
 * 		PinTool for Measuring runtime 
 *
 */

#include "pin.H"
namespace WINDOWS
{
#include<Windows.h>
}
#include <iostream>
#include <iomanip>
#include <fstream>


std::ofstream TraceFile;

WINDOWS::DWORD WINAPI before,after;


/* ==================================================================== */
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "timeCheck.csv", "specify file name");

/* ==================================================================== */
INT32 Usage()
{
    cerr <<
        "This tool calculate runtime in seconds .\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}

/* ===================================================================== */

VOID Start (VOID *v)
{
	before= WINDOWS::GetTickCount();

}
	
/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
	
	after= WINDOWS::GetTickCount();
	TraceFile<<(after-before)/1000<<"."<<(after-before)%1000<<endl;
	TraceFile.close();
}

/* ===================================================================== */

int main(int argc, char *argv[])
{
    
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )   return Usage();
  	   
    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
   
    PIN_AddFiniFunction(Fini, 0);
	PIN_AddApplicationStartFunction(Start, 0);
	
    // Never returns
    PIN_StartProgram();
    
    return 0;
}




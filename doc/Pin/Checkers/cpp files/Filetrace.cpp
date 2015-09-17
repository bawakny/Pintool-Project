/*
 *
 * 		PinTool for Tracing CreateFiles 
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
int fileCount =0;
/* ==================================================================== */
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "fileTrace.csv", "specify trace file name");

/* ==================================================================== */
INT32 Usage()
{
    cerr <<
        "This tool produces a trace of calls to CreateFile.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


 /* =====================- Add filename to the tracing file -============================== */
VOID AddToFile(
		    char * lpFunctionName,
			WINDOWS::PVOID lpFileName,
			WINDOWS::DWORD dwDesiredAccess,
			WINDOWS::DWORD dwShareMode,
			WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			WINDOWS::DWORD dwCreationDisposition,
			WINDOWS::DWORD dwFlagsAndAttributes,
			WINDOWS::HANDLE hTemplateFile
		) 
{

	char buffer[1024];
	wcstombs(buffer, (wchar_t *)lpFileName, sizeof(buffer));
	if ((dwCreationDisposition == 1)||(dwCreationDisposition== 2))		fileCount++;
	
	++fileCount;
	 
}


/* =============================- Instrumentation routines -============================== */
   
VOID Image(IMG img, VOID *v)
{
    // Walk through the symbol table.

	
    
    for (SYM symbl = IMG_RegsymHead(img); SYM_Valid(symbl); symbl = SYM_Next(symbl))
    {
        string FuncName = PIN_UndecorateSymbolName(SYM_Name(symbl), UNDECORATION_NAME_ONLY);

       
        
            RTN allocRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(symbl));
            
            if (RTN_Valid(allocRtn))
            {
                RTN_Open(allocRtn);
                 if (FuncName == "CreateFileA"){
                RTN_InsertCall(allocRtn, IPOINT_BEFORE, (AFUNPTR)AddToFile,
                               IARG_ADDRINT, "CreateFileA",
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
							   IARG_END);}

                else if (FuncName == "CreateFileW"){
					RTN_InsertCall(allocRtn, IPOINT_BEFORE, (AFUNPTR)AddToFile,
								IARG_ADDRINT, "CreateFileW",
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
							   IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
							   IARG_END);}

                RTN_Close(allocRtn);
            }
        }
	
	
}

/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
	TraceFile <<fileCount << endl;  
    TraceFile.close();
}

/* ===================================================================== */

int main(int argc, char *argv[])
{
    
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )   return Usage();
  	   
    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
      
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);
	
    // Never returns
    PIN_StartProgram();
    
    return 0;
}




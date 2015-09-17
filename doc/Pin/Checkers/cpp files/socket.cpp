/*
 *
 * 		PinTool for Socket issues 
 *
 */

#include "pin.H"
namespace WINDOWS
{
#include<Windows.h>
#include<WinSock2.h>
}

#include <iostream>
#include <iomanip>
#include <fstream>


std::ofstream SocketCheck;
int counter;

/* ==================================================================== */
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "SocketCheck.csv", "specify  file name");

/* ==================================================================== */
INT32 Usage()
{
    cerr <<
        "This tool checks if a socket has been created or handeld.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


 /* =====================- socket related functions -============================== */


VOID socketData(char * FunctionName,
			   WINDOWS::SOCKET s,
			   WINDOWS::LPWSABUF lpBuffers,
			   WINDOWS:: DWORD dwBufferCount,
			   WINDOWS:: LPDWORD lpNumberOfBytesSent,
			   WINDOWS:: DWORD dwFlags,
			   WINDOWS:: LPWSAOVERLAPPED lpOverlapped,
			   WINDOWS:: LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{

	
	counter+=(int)(*lpNumberOfBytesSent);
	

	
}



/* =============================- Instrumentation routines -============================== */
   
VOID Image(IMG img, VOID *v)
{
    // Walk through the symbol table.
	
    
    for (SYM symbl = IMG_RegsymHead(img); SYM_Valid(symbl); symbl = SYM_Next(symbl))
    {
        string FuncName = PIN_UndecorateSymbolName(SYM_Name(symbl), UNDECORATION_NAME_ONLY);

       
        
		if (FuncName == "WSASend"){
            RTN allocRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(symbl));
            
            if (RTN_Valid(allocRtn))
            {
                RTN_Open(allocRtn);
				RTN_InsertCall(allocRtn, IPOINT_AFTER , (AFUNPTR)socketData,
								IARG_ADDRINT, "WSASend",
								IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
								IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
								IARG_END);
				RTN_Close(allocRtn);
			}
       }


		
	
	
	
	}
}
/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
	
	SocketCheck<<counter<<endl;
	
	SocketCheck.close();
}

/* ===================================================================== */

int main(int argc, char *argv[])
{
	counter=0;
    
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )   return Usage();
  	
    // Write to a file since cout and cerr maybe closed by the application
    SocketCheck.open(KnobOutputFile.Value().c_str());
     
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);
	
    // Never returns
    PIN_StartProgram();
    
    return 0;
}




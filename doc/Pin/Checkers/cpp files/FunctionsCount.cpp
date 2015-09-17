/*
 *
 * 		PinTool for Counting Functions. 
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
#include <sstream>
#include <string>
 #include <algorithm>     
#include <vector> 



std::ofstream TraceFile;
 

 
std::vector<string> functions;  
std::vector<string>::iterator it;

	/* ==================================================================== */
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "FunctionsCount.csv", "specify trace file name");

/* ==================================================================== */
INT32 Usage()
{
    cerr <<
		"This tool Counts Functions.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}
/* ==================================================================== */


/* ===================================================================== */


VOID Image(IMG img, VOID *v)
{

	if (IMG_Valid(img) && IMG_IsMainExecutable(img)){



		for (SYM symbl = IMG_RegsymHead(img); SYM_Valid(symbl); symbl = SYM_Next(symbl))
		{
			string FuncName = PIN_UndecorateSymbolName(SYM_Name(symbl), UNDECORATION_NAME_ONLY);
			it = find (functions.begin(), functions.end(), FuncName);

			if (it == functions.end())	functions.push_back(FuncName); 
			
		}
	}
}

/* ===================================================================== */


VOID Fini(INT32 code, VOID *v)
{
	TraceFile<<functions.size()<<endl;
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

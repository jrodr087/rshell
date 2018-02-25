#ifndef __PROGRAMCALL__
#define __PROGRAMCALL__
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <features.h>
#include "filename.h"
using namespace std;
class ProgramCall {
    public:
      ProgramCall(char* programName, char** argumentList, int argumentCount, string conjunction, Filename* in, Filename* out);
      ProgramCall();
      ProgramCall(const ProgramCall& other);
      virtual ~ProgramCall();
      void SetConjunctionType(string conj);
      char* GetProgramName();
      char** GetArgumentList();
      int GetArgumentCount();
      string GetConjunctionType();
      bool CheckIfInternalProgram(int* status);
      virtual bool CheckIfQueue();
      virtual void runQueue(int* status);
      Filename* inputRedir;
      Filename* outputRedir;
    private:
      string conjunction;
      char* progName;
      char** argList;
      int argCount;
};

#endif

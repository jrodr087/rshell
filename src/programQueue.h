#ifndef __PROGRAMQUEUE__
#define __PROGRAMQUEUE__

#include <stdio.h>
#include <unistd.h>
//#define _GNU_SOURCE
#include <fcntl.h>
#include <queue>
#include <sys/wait.h>
#include "programCall.h"

class ProgramQueue : public ProgramCall{
    public:
      ProgramQueue();
      ~ProgramQueue();
      ProgramQueue(const ProgramQueue& other);
      void AddtoQueue(ProgramCall*);
      char* GetCurrentProgramName();
      char** GetCurrentArgumentList();
      void Dequeue();
      bool CheckIfQueue();
      void runQueue(int* status);
    //private:
      std::queue<ProgramCall*> progQueue;
      
};

#endif

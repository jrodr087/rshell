#include <iostream>
#include <string>
#include "programCall.h"
#include <cstring>
using namespace std;

ProgramCall::ProgramCall(char* programName, char** argumentList, int argumentCount, string conjunction, Filename* in, Filename* out){
  progName = programName;
  argList = argumentList;
  argCount = argumentCount;
  this->conjunction = conjunction;
  inputRedir = in;
  outputRedir = out;
  
}
ProgramCall::ProgramCall () {
  progName = NULL;
  argList = NULL;
  argCount = 0;
  conjunction = ";";
  inputRedir = NULL;
  outputRedir = NULL;
}

ProgramCall::~ProgramCall(){
  // if (argCount){
     //delete progName;
     //delete argList;
   //}
   if (progName != NULL){
    delete[] progName;
    progName = NULL;
   }
   if (inputRedir != NULL){
    delete inputRedir;
   }
   if (outputRedir != NULL){
    delete outputRedir;
   }
   if (argList != NULL){
    int i;
    for (i = 0; argList[i] != '\0'; i++){
      delete[] argList[i];
      argList[i] = NULL;
    }
    delete[] argList;
    argList = NULL;
   }
}
/*ProgramCall::ProgramCall(const ProgramCall& other){
  argList = new char* [argCount];
  memcpy(argList, other.argList, argCount);
  for (int i = 0; other.argList[i] != '\0'; i++){
    for (int j = 0; true; i++){
      if (other.argList[i][j] == '\0'){
        argList[i] = new char [j+1];
        memcpy(argList[i], other.argList[i], j+1);
        if (i == 0){
          progName = new char[j+1];
          memcpy(progName, other.argList[i], j+1);
        }
      }
    }
  }
}
ProgramCall& ProgramCall::operator= (const ProgramCall& other){
  if (this != &other){
    this(other);
  }
}*/
void ProgramCall::SetConjunctionType(string conj){
  conjunction = conj;
}

char* ProgramCall::GetProgramName(){
  return progName;
}

char** ProgramCall::GetArgumentList(){
  return argList;
}
string ProgramCall::GetConjunctionType(){
  return conjunction;
}
int ProgramCall::GetArgumentCount() {
  return argCount;
}
bool ProgramCall::CheckIfQueue() {
  return false;
}
void ProgramCall::runQueue(int* status) {
  
}

bool ProgramCall::CheckIfInternalProgram(int* status) {
  struct stat buf;
  
  if (!strcmp(progName, "exit")){
    cout << "goodbye" << endl;
    exit(1);
  }
  else if (!strcmp(progName, "test")){
    if (argCount >= 2 && argCount < 4) {
      if (argCount == 2) {
        if ( stat( argList[1], &buf) == 0){
        *status = 0;
        cout << "(True)" << endl;
        }
        else {
        *status = -1;
        cout << "(False)" << endl;
        }
      }
      else if (!strcmp(argList[1], "-e")){
        if ( stat( argList[2], &buf) == 0){
          *status = 0;
          cout << "(True)" << endl;
        }
        else {
          *status = -1;
          cout << "(False)" << endl;
        }
      }
      else if (!strcmp(argList[1], "-f")){
        if ( stat( argList[2], &buf) != 0){
          *status = -1;
          cout << "(False)" << endl; 
        }
        else if ( buf.st_mode & S_IFREG) {
          *status = 0;
          cout << "(True)" << endl;
        }
        else {
          *status = -1;
          cout << "(False)" << endl;
        }
      }
      else if (!strcmp(argList[1], "-d")){
        if ( stat( argList[2], &buf) != 0){
          *status = -1;
          cout << "(False)" << endl; 
        }
        else if ( buf.st_mode & S_IFDIR) {
          *status = 0;
          cout << "(True)" << endl;
        }
        else {
          *status = -1;
          cout << "(False)" << endl;
        }
      }
      else {
        cout << "(False)" << endl;
        *status = -1;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

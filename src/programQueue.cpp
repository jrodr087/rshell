#include <iostream>
#include "programQueue.h"
#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

ProgramQueue::ProgramQueue(){
  queue<ProgramCall*> progQueue;
}
ProgramQueue::~ProgramQueue(){
  while (!progQueue.empty()){
    delete progQueue.front();
    Dequeue();
  }
}
/*ProgramQueue::ProgramQueue(const ProgramQueue& other){
  
}*/
void ProgramQueue::AddtoQueue(ProgramCall* toAdd){
  progQueue.push(toAdd);
}
bool ProgramQueue::CheckIfQueue(){
  return true;
}
char* ProgramQueue:: GetCurrentProgramName(){
  return progQueue.front() -> GetProgramName();
}

char** ProgramQueue:: GetCurrentArgumentList() {
  return progQueue.front() -> GetArgumentList();
}

void ProgramQueue:: Dequeue() {
  progQueue.pop();
}

void ProgramQueue:: runQueue(int* status) {
  pid_t pid;
  string output;
  
  while (!progQueue.empty()){
    int pipefd[2];
    int pipein[2];
    //cout << progQueue.front()->GetConjunctionType() << endl;
    if (!progQueue.front()->CheckIfQueue()){
      if (progQueue.front()->inputRedir != NULL){
        string fn = progQueue.front()->inputRedir->GetFilename();
        ifstream ifile(fn.c_str());
        if (!ifile.is_open()){
           cout << "could not open input file" << endl;
           return;
        } 
        output = "";
        string data((istreambuf_iterator<char>(ifile)), istreambuf_iterator<char>());
        output = data;
        ifile.close();
      }
      if (pipe(pipefd) == -1){
        perror("pipe");
        exit(1);
      }
      if (pipe(pipein) == -1){
        perror("pipe");
        exit(1);
      }
      //cout << "pipe created" << endl;
      if (!(progQueue.front() -> CheckIfInternalProgram(status))){
        if ((pid = fork()) < 0){
          perror("fork failed");
          exit(1);
        }
        else if (pid == 0) {
          close(pipein[1]);
          if (output != ""){
            dup2(pipein[0], STDIN_FILENO);
          }
          close(pipein[0]);
          close(pipefd[0]);
          if (progQueue.front()->GetConjunctionType() == "|" || progQueue.front()->outputRedir != NULL){
            dup2(pipefd[1], STDOUT_FILENO);
          }
          close(pipefd[1]);
          if (execvp(progQueue.front() -> GetProgramName(), 
          progQueue.front() -> GetArgumentList()) < 0 ){
            perror("executing program failed");
            exit(1);
          }
        }
        else {
          close(pipein[0]);
          //if (progQueue.front()->GetConjunctionType() == "|"){
          write(pipein[1], output.c_str(), output.length());
          //}
          close(pipein[1]);
          while(wait(status) != pid){}
          close(pipefd[1]);
          output = "";
          char buf[2];
          while (read(pipefd[0], buf, 1) > 0){
            buf[1] = '\0';
            output += buf;
          }
          close(pipefd[0]);
         // wait();
          //while(wait(status)!= pid){}
        }
        
      }
    }
    else{
      progQueue.front()->runQueue(status);
    }
    if (*status != 0){
         if (progQueue.front()->GetConjunctionType() == "&&"){
            while (!progQueue.empty() && progQueue.front()->GetConjunctionType() == "&&"){ 
               ProgramCall* temp = progQueue.front();
               Dequeue();
               if (!temp->CheckIfQueue()){
                 delete temp;
               }
            }
         }
      }
      else{
         if (progQueue.front()->GetConjunctionType() == "||"){
            while (!progQueue.empty() && progQueue.front()->GetConjunctionType() == "||"){
               ProgramCall* temp = progQueue.front();
               Dequeue();
               if (!temp->CheckIfQueue()){
                 delete temp;
               }
            }
         }
      }
      
        if (progQueue.front()->outputRedir != NULL){
        fstream file;
        if (progQueue.front()->outputRedir -> GetRedir() == ">"){
          file.open(progQueue.front()->outputRedir->GetFilename().c_str(), ios::out | ios::trunc);
          file << output;
          file.close();
        }
        else {
          file.open(progQueue.front()->outputRedir->GetFilename().c_str(), ios::out | ios::app);
          file << output;
          file.close();
        }
      }
      else if (progQueue.front()->GetConjunctionType() == "|"){
       // cout << "saving output" << endl;
      }
      else{
        cout << output;
        output = "";
      }
      if (!progQueue.empty()){
        ProgramCall* temp = progQueue.front();
        Dequeue();
        if (!temp->CheckIfQueue()){
          delete temp;
        }
      }
    }
}

      
        

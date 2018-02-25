#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include "programCall.h"
#include "programQueue.h"
#include "filename.h"

using namespace std;
ProgramQueue* parseInput(string input);
void runMenu();
void deleteComment(string& input);
void addToQueue(vector<string> &arg_v, ProgramQueue* progQueue, string conjType, Filename* in, Filename* out); ///stub for later helper
bool countParenthesis(string input);
int main(){
   runMenu();//just runs the menu
}
  
void runMenu(){
   while(1){//only way to get outta here is to input "quit"
      cout << "$ ";
      string input;
      int status = 0;
      getline(cin, input);
      deleteComment(input);
      if (countParenthesis(input)){
         ProgramQueue* finishedQueue;
         finishedQueue = parseInput(input);
         if (finishedQueue != 0){
           finishedQueue->runQueue(&status);
           delete finishedQueue;
         }
      }
      else{
         cout << "Syntax error: imbalanced amount of parenthesis or test brackets" << endl;
      }
   }
}

ProgramQueue* parseInput(string input){//parses the input so our program can understand user
   bool input_empty = false;
   ProgramQueue* progQueue = new ProgramQueue();
   int curr_index = 0;
   /*curr_index = input.find('#');
   if (curr_index != -1){//finds comment and removes everything after it
      input = input.substr(0, curr_index);//removes comment
   }*/ //depreciated ccomment deleter
   curr_index = input.find_first_not_of(' ');//find index of first nonspace
   if (curr_index == -1){// if there is no input, return empty progQueue
      return progQueue;
   }
   else if (curr_index != 0){//if there are leading spaces before input
      input = input.substr(curr_index, input.size() - curr_index);//removes 
      //leading whitespace
      curr_index = 0;
   }
   while(!input_empty){// while the input still has more to be read
      bool conjunction_found = false;
      vector<string> arg_v;
      string conjunction = ";";
      Filename* inputRedir = NULL;
      Filename* outputRedir = NULL;
      while(!conjunction_found){ // while we have not found a && || or ;
         int top = input.find(" ", curr_index);//find the top of the curr arg
        /* if (top == -1){//if there is no space then 
         //the end of the string is the top of the arg
            if (input.substr(curr_index, input.size() - curr_index) != "]"){
               arg_v.push_back(
               input.substr(curr_index, input.size() - curr_index));//add arg 
               //to container
            }
            input_empty = true;//we're empty
            conjunction_found = true;
         }
         else{//otherwise cut the argument from the input*/
            string temp_arg = "";
            if (top != -1){
              temp_arg = input.substr(curr_index, top - curr_index);
            }
            else{
              temp_arg = input.substr(curr_index, input.size() - curr_index);
            }
            if (temp_arg == "&&" || temp_arg == "||" || temp_arg == "|"){//if it's a conjunction
               conjunction_found = true;//we're done with this loop
               conjunction = temp_arg;
               curr_index = input.find_first_not_of(" ", top);//find the beginning of the next argument
            }
            else if (temp_arg == "<" || temp_arg == ">" || temp_arg == ">>"){//redirection
              string fn = ""; //filename string
              curr_index = input.find_first_not_of(" ", top);//snip filename
              if (curr_index == -1){
                cout << "Syntax error: filename must follow redirection" << endl;
                return NULL;
              }
              top = input.find(" ", curr_index);
              if (top != -1){
                fn = input.substr(curr_index, top - curr_index);
              }
              else{
                fn = input.substr(curr_index, input.size() - curr_index);
              }
              if (temp_arg == "<"){
                if (inputRedir != NULL){
                  cout << "Syntax error: only use one input redirection at a time please" << endl;
                  return NULL;
                }
                inputRedir = new Filename(fn, temp_arg);
              }
              else{
                if (outputRedir != NULL){
                  cout << "Syntax error: only use one output redirection at a time please" << endl;
                  return NULL;
                }
                outputRedir = new Filename(fn, temp_arg);
              }
              goto skipInputParsing;
            }
            else{//otherwise
               if (temp_arg == ""){
                 conjunction_found = true;
                 input_empty = true;
                 break;
               }
               if (temp_arg.at(0) == '\"'){
                 int endQuote = input.find('\"', curr_index + 1);
                 if (endQuote == -1){
                   temp_arg = input.substr(curr_index+1, input.size() - curr_index-1);
                 }
                 else{
                   temp_arg = input.substr(curr_index+1, endQuote -curr_index-1);
                   top = endQuote+1;
                 }
                 goto skipOperatorParsing;
               }
               if (temp_arg.at(0) == '('){ // parse in parenthesis
                 if (arg_v.size() != 0){ // if there are iarguments before this then error
                   cout << "Syntax Error: precedence operators () must come after a connector && || ; or at the beginning of an input" << endl;
                  return NULL;
                 }
                 int endParenthesis = 0;
                 int startPCount = 0;
                 for (unsigned int i = curr_index+1; i < input.size(); i++){//finds the correct end for this parentehsis
                   if (input.at(i) == '\"'){
                    i = input.find('\"', i+1);
                   }
                   if (input.at(i) == '('){
                     startPCount++;
                   }
                   else if (input.at(i) == ')'){
                     if (startPCount == 0){
                       endParenthesis = i;
                       break;
                     }
                     startPCount--;
                   }
                 }
                 string newIn = input.substr(curr_index + 1, endParenthesis-curr_index-1);
                 ProgramQueue* newQueue = parseInput(newIn);
                 if (newQueue == NULL){
                   return NULL;
                 }
                 top = input.find_first_not_of(" ", endParenthesis);
                 newQueue->SetConjunctionType(conjunction);
                 progQueue->AddtoQueue(newQueue);
                 goto skipInputParsing;
                 cout << "this should never output" << endl;
               }
               if (temp_arg.at(temp_arg.size()-1) == ';'){//check for ; conj.
                  conjunction_found = true;
                  temp_arg = temp_arg.substr(0,temp_arg.size() - 1);
               }
               while (temp_arg.size() > 1 && (temp_arg.at(temp_arg.size()-1) == ')' || temp_arg.at(temp_arg.size()-1) == ']')){
                  temp_arg = temp_arg.substr(0, temp_arg.size() -1);
               }
               if (temp_arg.size() != 0 && temp_arg.at(0) == '['){ //check for brackets for test
                  temp_arg = "test";
                  curr_index++;
               }
              
               if (temp_arg == "]" || temp_arg == ")"){
                 //curr_index++;
               }
               else{
skipOperatorParsing:
                 arg_v.push_back(temp_arg);// add argument to container
               }
skipInputParsing:
               curr_index = input.find_first_not_of(" ", top);//find next arg
            }
            if (curr_index == -1){// if there is no next argument
               conjunction_found = true;
               input_empty = true;//the input is empty
            } 
     }
     if (arg_v.size() != 0){
       addToQueue(arg_v, progQueue, conjunction, inputRedir, outputRedir);
     }
   }
   return progQueue;
}
void addToQueue(vector<string> &arg_v, ProgramQueue* progQueue, string conjType, Filename* in, Filename* out){
   if (arg_v.at(0) == ""){
     return;
   }
   char* progName = new char [arg_v.at(0).size()+1]; 
   strcpy(progName, arg_v.at(0).c_str());
   char** arglist = new char* [arg_v.size()+1];
   for (unsigned int i = 0; i < arg_v.size(); i++){
       arglist[i] = new char [arg_v.at(i).size()+1];
       strcpy(arglist[i], arg_v.at(i).c_str());
   }
   arglist[arg_v.size()] = 0;
   ProgramCall* progCall = new ProgramCall(progName, arglist, arg_v.size(), conjType, in, out);
   progQueue->AddtoQueue(progCall);
}
bool countParenthesis(string input){ // returns true if input has equal amount of parenthesis
   int startPCount = 0;
   int endPCount = 0;
   int startBCount = 0;
   int endBCount = 0;
   for (int i = 0; static_cast<unsigned int>(i) < input.size() && i != -1; i++){
      if (input.at(i) == '\"'){
        i = input.find('\"', i+1);
      }
      else if (input.at(i) == '('){
         startPCount++;
      }
      else if (input.at(i) == ')'){
         endPCount++;
      }
      else if (input.at(i) == '['){
        startBCount++;
      }
      else if (input.at(i) == ']'){
        endBCount++;
      }
   }
   if (startPCount == endPCount && startBCount == endBCount){
      return true;
   }
   return false;
}
void deleteComment(string &input){
  int loc = 0;
  bool foundCom = false;
  while (!foundCom){
    foundCom = true;
    loc = input.find("#", loc);
    if (loc == -1) {
      return;
    }
    for (int i = 0; (i < loc && loc != -1); i = input.find_first_not_of(' ', i)){
      if (input.at(i) == '\"'){
        int end = input.find("\"", i+1);
        if (end == -1){
          return;
        }
        if (end > loc){
          foundCom = false;
          break;
        }
        i = end + 1;
      }
      i = input.find(' ', i);
    }
  loc++;
  }
  input = input.substr(0, loc-1);
}

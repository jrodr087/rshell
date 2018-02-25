#include <string>
#include "filename.h"

using namespace std;
//fnString
//redirType
Filename::Filename(){ fnString = ""; redirType = "";}

Filename::Filename(string fn, string rdt){
  fnString = fn;
  redirType = rdt;
}
Filename::~Filename(){}
void Filename::SetFilename(string fn){
  fnString = fn;
}
string Filename::GetFilename(){
  return fnString;
}

void Filename::SetRedir(string rdt){
  redirType = rdt;
}
string Filename::GetRedir(){
  return redirType;
}

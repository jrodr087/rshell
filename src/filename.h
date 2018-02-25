#ifndef __FILENAME_H__
#define __FILENAME_H__
#include <string>

using namespace std;

class Filename{
  private:
    string fnString; // name of the filename, e.g: test.txt
    string redirType; //type of redirection, e.g: "<", ">", ">>"
  public:
    Filename();
    Filename(string fn, string rdt);
    ~Filename();
    void SetFilename(string fn);
    string GetFilename();
    void SetRedir(string redir);
    string GetRedir();

};
#endif

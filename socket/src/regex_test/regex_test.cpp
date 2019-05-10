// regex_search example
#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>
 
 using namespace std;
int main(){
   string str = "GET /index.html HTTP/1.1";

  
    string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.].*)?) HTTP/1";
    regex e(pattern,std::regex_constants::basic);
    smatch m;
    regex_search(str,m,e);

    //std::regex_error();

    if (m.size() > 0) 
    {
      printf(" m1:%s, m2,m2:%s",m[1],m[2]);
    }
    else
    {
      printf("regex_search error");
    }
 
  // std::string s ("this subject has a submarine as a subsequence");
  // std::smatch m;
  // std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
 
  // std::cout << "Target sequence: " << s << std::endl;
  // std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
  // std::cout << "The following matches and submatches were found:" << std::endl;
 
  // while (std::regex_search (s,m,e)) {

  // }
}

 #if 0
int main ()
{
 

  if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
    std::cout << "string literal matched\n";
 
  std::string s ("subject");
  std::regex e ("(sub)(.*)");
  if (std::regex_match (s,e))
    std::cout << "string object matched\n";
 
  if ( std::regex_match ( s.begin(), s.end(), e ) )
    std::cout << "range matched\n";
 
  std::cmatch cm;    // same as std::match_results<const char*> cm;
  std::regex_match ("subject",cm,e);
  std::cout << "string literal with :" << cm.size() << " matches\n";
 
  std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
  std::regex_match (s,sm,e);
  std::cout << "string object with " << sm.size() << " matches\n";
 
  std::regex_match ( s.cbegin(), s.cend(), sm, e);
  std::cout << "range with " << sm.size() << " matches\n";
 
  // using explicit flags:
  std::regex_match ( "subject", cm, e, std::regex_constants::match_default );
 
  std::cout << "the matches were: ";
  for (unsigned i=0; i<sm.size(); ++i) {
    std::cout << "[" << sm[i] << "] ";
  }
 
  std::cout << std::endl;
 
  return 0;
}

#endif
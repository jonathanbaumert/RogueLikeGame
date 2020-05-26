#include <iostream>

#include "string327.h"

using namespace std;

int main(int argc, char *argv[])
{
  string327 s;

  cout << s << endl;

  s = "Happy Halloween";

  cout << s << endl;

#if 0
  s += "!  And Thanksgiving is less than a month away!";

  cout << s << endl;

  cout << s[6] << endl;
  s[15] = ',';            // This
  cout << s << endl;
  s.operator[](15) = '.'; // And this are exactly the same!
  cout << s << endl;

  //  string327 t(s);
#endif
  string327 t = s;  // This calls the copy constructor, not the = operator.

  //  operator<<(cout.operator<<("t = "), t).operator<<(endl);
  cout << "t = " << t << endl;

  return 0;
}

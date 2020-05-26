#include <iostream>

#include "header.h"

using namespace std;

void cpp_function(const char *s)
{
  c_function(s);
}

ostream *return_cout()
{
  return &cout;
}

void use_cout(ostream *o)
{
  *o << "Using the pointer that I got from C!";
}

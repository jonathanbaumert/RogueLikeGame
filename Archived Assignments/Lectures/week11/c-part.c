#include <stdio.h>

#include "header.h"

int main(int argc, char *argv[])
{
  ostream *o;

  cpp_function("Hello World!");

  o = return_cout();
  use_cout(o);

  return 0;
}

void c_function(const char *s)
{
  printf("%s\n", s);
}

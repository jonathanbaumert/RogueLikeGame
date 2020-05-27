#include <cstring>
#include <cstdlib>
#include <iostream>

#include "string327.h"

string327::string327()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  str = (char *) malloc(1);
  str[0] = '\0';
}

string327::string327(const char *s)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  str = strdup(s);
}

string327::string327(const string327 &s)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  str = strdup(s.str);
}

string327::~string327()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  free(str);
}

string327 string327::operator+(const string327 &s)
{
  string327 out;

  std::cout << __PRETTY_FUNCTION__ << std::endl;

  out.str = (char *) realloc(out.str, strlen(str) + strlen(s.str) + 1);
  strcpy(out.str, str);
  strcat(out.str, s.str);

  return out;
}

string327 &string327::operator+=(const string327 &s)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  str = (char *) realloc(str, strlen(str) + strlen(s.str) + 1);
  strcat(str, s.str);

  return *this;
}

string327 &string327::operator=(const char *s)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  free(str);
  str = strdup(s);

  return *this;
}

string327 &string327::operator=(const string327 &s)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  free(str);
  str = strdup(s.str);

  return *this;
}

char &string327::operator[](const int index)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return str[index];
}

std::istream &operator>>(std::istream &i, const string327 &s)
{
  // This is broken.  Fixing it is left as an exercise for the reader.
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return i >> s.str;
}

std::ostream &operator<<(std::ostream &o, const string327 &s)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return o << s.c_str();
}

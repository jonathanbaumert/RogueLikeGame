#ifndef STRING327_H
# define STRING327_H

class string327 {
 private:
  char *str;
 public:
  string327();
  string327(const char *s);
  string327(const string327 &s);
  ~string327();
  int length()
  {
    return strlen(str);
  }
  const char *c_str()
  {
    return str;
  }

  int operator<(const string327 &s)
  {
    return strcmp(str, s.str) < 0;
  }

  int operator<=(const string327 &s)
  {
    return strcmp(str, s.str) <= 0;
  }

  int operator>(const string327 &s)
  {
    return strcmp(str, s.str) > 0;
  }

  int operator>=(const string327 &s)
  {
    return strcmp(str, s.str) >= 0;
  }

  int operator==(const string327 &s)
  {
    return strcmp(str, s.str) == 0;
  }

  int operator!=(const string327 &s)
  {
    return strcmp(str, s.str) != 0;
  }


  string327 operator+(const string327 &s);
  string327 &operator+=(const string327 &s); //Returns a reference so that 
                                             //returned string can be calling
                                             //string
  string327 &operator=(const char *s);
  string327 &operator=(const string327 &s);

  char &operator[](const int index);

  operator const char *();

};

#endif


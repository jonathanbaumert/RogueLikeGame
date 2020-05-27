#ifndef STRING327_H
# define STRING327_H

# include <cstring>

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
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strlen(str);
  }
  const char *c_str() const
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return str;
  }

  int operator<(const string327 &s)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strcmp(str, s.str) < 0;
  }

  int operator<=(const string327 &s)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strcmp(str, s.str) <= 0;
  }

  int operator>(const string327 &s)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strcmp(str, s.str) > 0;
  }

  int operator>=(const string327 &s)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strcmp(str, s.str) >= 0;
  }

  int operator==(const string327 &s)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strcmp(str, s.str) == 0;
  }

  int operator!=(const string327 &s)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return strcmp(str, s.str) != 0;
  }


  string327 operator+(const string327 &s);
  string327 &operator+=(const string327 &s); //Returns a reference so that 
                                             //returned string can be calling
                                             //string
  string327 &operator=(const char *s);
  string327 &operator=(const string327 &s);

  char &operator[](const int index);

  operator const char *()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return str;
  }

  friend std::istream &operator>>(std::istream &i, const string327 &s);
};

std::ostream &operator<<(std::ostream &o, const string327 &s);

#endif


string327::string327()
{
  str = (char *) malloc(1);
  str[0] = '\0';
}

string327::string327(const char *s)
{
  str = strdup(s);
}

string327::string327(const string327 &s)
{
  str = strdup(s.str);
}

string327::~string327()
{
  free(str);
}

string327 string327::operator+(const string327 &s)
{
  string327 out;

  out.str = (char *) realloc(out.str, strlen(str) + strlen(s.str) + 1);
  strcpy(out.str, str);
  strcat(out.str, s.str);

  return out;
}

string327 &string327::operator+=(const string327 &s)
{
  str = (char *) realloc(str, strlen(str) + strlen(s.str) + 1);
  strcat(str, s.str);

  return *this;
}

string327 &string327::operator=(const char *s)
{
  free(str);
  str = strdup(s);

  return *this;
}

string327 &string327::operator=(const string327 &s)
{
  free(str);
  str = strdup(s.str);

  return *this;
}


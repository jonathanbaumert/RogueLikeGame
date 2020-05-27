#include <iostream>

using namespace std;

void cswap(int *a, int *b)
{
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

void cppswap(int &a, int &b)
{
  int tmp;

  tmp = a;
  a = b;
  b = tmp;
}

int main(int argc, char *argv[])
{
  int x = 5;
  int y = 7;

  int *p;

  p = &x;
  *p = 8;
  p = &y;
  *p = 10;

  const int &r = x;

  r = 12;
  

  cout << x << " " << y << endl;

  cswap(&x, &y);

  cout << x << " " << y << endl;

  cppswap(x, y);

  cout << x << " " << y << endl;

  return 0;
}

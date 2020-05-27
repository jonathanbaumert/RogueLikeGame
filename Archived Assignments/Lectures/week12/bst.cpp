#include <cstdlib>
#include <time.h>

#include "bst.h"

template <class T>
inline T& max(T &x, T &y)
{
  return x > y ? x : y;
}

#define max(x, y) (x > y ? x : y)

int main(int argc, char *argv[])
{
  bst<int> b;
  int i;

  srand(time(NULL));

  try {
    b.min();
  }
  catch (int i) {
    cout << i << endl;
  }
  catch (const char *s) {
    cout << s << endl;
  }
  catch (...) {
    cout << "Caught an exception" << endl;
  }

  for (i = 0;i < 100; i++) {
    b.insert(rand());
  }

  b.insert(10);

  b.print_in_order(cout);

  cout << endl;

  cout << b.find(10) << " " << b.find(-1) << endl;

  bst<bst<int> > t;

  t.insert(b);

  return 0;
}

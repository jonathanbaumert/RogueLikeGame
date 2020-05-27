#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool greater_than_65(int i)
{
  return i > 65;
}

bool greater_than_23(int i)
{
  return i > 23;
}

class greater_than {
private:
  int value;
public:
  greater_than(int i) : value(i) {}
  bool operator()(int i) { return i > value; }
};

int main(int argc, char *argv[])
{
  int i;
  greater_than gt17(17);
  /*
  for (i = 0; i < 100; i++) {
    if (greater_than(17)(i)) {
      cout << i << " ";
    }
  }
  cout << endl;
  */

  vector<int> v;
  vector<int>::iterator vi;

  for (i = 0; i < 100; i++) {
    v.push_back(i);
  }

  for (vi = v.begin();
       (vi = find_if(vi, v.end(), gt17)) != v.end();
        vi++) {
    cout << *vi << " ";
  }
  cout << endl;

  for (vi = v.begin();
       (vi = find_if(vi, v.end(), greater_than_23)) != v.end();
        vi++) {
    cout << *vi << " ";
  }
  cout << endl;

  return 0;
}

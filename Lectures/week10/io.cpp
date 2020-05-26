#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
  ifstream f("input_file.txt");
  int i;
  string s;

  i = f.get();

  //Reading the first line, one character at a time
  cout << i << endl;
  cout << (char) i << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.get() << endl;
  //consume newline
  f.get();

  //Read second line, one character at a time, every character twice
  cout << (char) f.peek() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.peek() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.peek() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.peek() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.peek() << endl;
  cout << (char) f.get() << endl;
  cout << (char) f.peek() << endl;
  cout << (char) f.get() << endl;
  f.get();

  //Read line 3, consume newline but don't add it to stream
  getline(f, s);
  cout << s << endl;
  cout << f.peek() << endl;
  f.get(); // Consumes newline on blank line
  //Read line 5
  getline(f, s);
  cout << s << endl;

  //Read 'line' from line 6
  f >> s;
  cout << s << endl;
  //Consume space and read '6'
  f >> s;
  cout << s << endl;

  //read newline
  cout << f.get() << endl;
  //read EOF
  cout << f.get() << endl;
  cout << f.get() << endl;


  vector<int> v;

  cout << endl;
  for (i = 0; i < 100; i++) {
    v.push_back(i);
  }

  for (i = 0; i < 100; i++) {
    cout << v[i] << endl;
  }

  cout << endl;

  vector<int>::iterator it;

  // begin() returns iterator referencing first item in container
  // end() returns an iterator that occurs after the container (not in!)
  for (it = v.begin(); it != v.end(); it++) {
    // Overload dereference operator to get item referenced by iterator
    cout << *it << endl;
  }

  cout << endl;

  for (i = 0; i < (int) v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;

  return 0;
}

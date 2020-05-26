#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class shape {
public:
  int color;
  virtual double area() = 0;
  virtual double perimeter() = 0;
  virtual ~shape() {}
  //Uninitialized use!
  int get_color() { return color; }
  void set_color(int c = 0) { color = c; }
};

ostream &operator<<(ostream &o, shape &s)
{
  return o << "Color is " << s.get_color() << " " 
           << s.area() << endl << s.perimeter();
}

class circle : public shape {
private:
  double radius;
public:
  circle(double r) : radius(r) {}
  double area()
  {
    cout << "Circle area" << endl;
    return M_PI * radius * radius;
  }
  double perimeter()
  {
    cout << "Circle perimeter" << endl;
    return 2 * M_PI * radius;
  }
  ~circle() {}
};

class rectangle : public shape {
private:
  double s1, s2;
public:
  rectangle(double s1, double s2) : s1(s1), s2(s2) {}
  virtual double area()
  {
    cout << "Rectangle area" << endl;
    return s1 * s2;
  }
  virtual double perimeter()
  {
    cout << "Rectangle perimeter" << endl;
    return 2 * s1 + 2 * s2;
  }
  virtual ~rectangle() {}
};

class square : public rectangle {
public:
  square(double side) : rectangle(side, side) {}
};

int main(int argc, char *argv[])
{
  shape *s = new rectangle(2, 4);
  rectangle r(5, 7);
  square sq(8);
  circle c(5);
  shape &src = c;
  shape &srr = r;

  srand(time(NULL));

  cout << *s << endl;
  cout << r << endl;
  cout << sq << endl;
  cout << c << endl;
  cout << src << endl;
  cout << srr << endl;

  shape *sa[10];
  int i;
  int d;

  cout << "--------------------------------------------------" << endl;

  for (i = 0; i < 10; i++) {
    d = rand() % 3;
    if (d == 0) {
      sa[i] = new square(i);
    } else if (d == 1) {
      sa[i] = new rectangle(i, i / 2);
    } else {
      sa[i] = new circle(i);
    }
  }

  for (i = 0; i < 10; i++) {
    square *squar;

    squar = dynamic_cast<square *>(sa[i]);

    if (squar) {
      cout << "I'm a square!" << endl;
    }
    cout << *sa[i] << endl;
    delete sa[i];
  }  
  

  delete s;

  return 0;
}

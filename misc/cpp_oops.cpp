/**
 * Problem: C++ Advanced OOPS (See: https://www3.ntu.edu.sg/home/ehchua/programming/cpp/cp6_Inheritance.html )
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define debug(x) cout << #x << " : " << x << endl;

class Point {
protected:
  int x, y;

public:
  Point(int x = 0, int y = 0): x(x), y(y) {}

  int getX() const {
    return x;
  }
  int getY() const {
    return y;
  }

  void setX(int x) {
    this->x = x;
  }

  void setY(int y) {
    this->y = y;
  }

  void setXY(int x, int y) {
    setX(x);
    setY(y);
  }

  // void dump() const {
  virtual void dump() const {     // virtual allows overriding by subclass for superclass
    cout << "Point: (" << x << ", " << y << ")" << endl;
  }

  // virtual void getInfo() const {};
  virtual void getInfo() const = 0; // pure virtual func (abstract)
};

class MovablePoint: public Point {
protected:
  int speedX, speedY;

public:
  MovablePoint(int x, int y, int sx = 0, int sy = 0): Point(x, y), speedX(sx), speedY(sy) {}

  int getSpeedX() const {
    return speedX;
  }

  int getSpeedY() const {
    return speedY;
  }

  void setSpeedX(int sx) {
    speedX = sx;
  }

  void setSpeedY(int sy) {
    speedY = sy;
  }

  void setSpeedXY(int sx, int sy) {
    setSpeedX(sx);
    setSpeedY(sy);
  }

  void dump() const {
    Point::dump();
    cout << "+\tSpeed: (" << speedX << ", " << speedY << ")" << endl;
  }

  void move() {
    x += speedX;
    y += speedY;
  }

  void getInfo() const {
    cout << "Type: " << typeid(*(this)).name() << "\n+\t";
    dump();
  }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cout << "**** Checking inheritance:" << endl;

  MovablePoint mp1(11, 12, 13, 14);   // subclass instance
  Point &p1 = mp1;                    // superclass type reference (alias) to subclass instance

  mp1.dump();                 // subclass method run
  p1.dump();                  // superclass method run if not virtual

  mp1.move();                 // subclass method
  mp1.dump();

  cout << "\n**** Checking polymorphism (virtual overriding):" << endl;

  // p1.move();              // superclass reference cannot run this subclass method since a superclass doesn't have this method
  p1.dump();                 // subclass overridden method is run even for superclass because of virtual

  // Point p2 = MovablePoint(1, 2, 3, 4);
  // p2.dump();                 // virtual has no effect in case of explicit constructor. Superclass method is run

  cout << "\n**** Checking Types:" << endl;

  cout << typeid(p1).name() << endl;
  cout << typeid(mp1).name() << endl;
  // cout << typeid(p2).name() << endl;

  cout << "\n***** Checking abstract classes (pure virtual functions):" << endl;
  mp1.getInfo();
  p1.getInfo();

  // Point p3(3, 5);        // abstract class can't be instantiated
  // p3.dump();

  return 0;
}

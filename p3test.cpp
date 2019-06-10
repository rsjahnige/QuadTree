#include "QTQuad.h"
#include "Point.h"
#include "BBox.h"
#include <iostream>
using namespace std;

int main()
{
  QTQuad newQuad;
  Point pt1(0,0);
  Point pt2(0,15);
  BBox bounds(pt1, 32);


  newQuad.set(pt1, 0, bounds);


  cout << newQuad.get(pt1, bounds) << endl;

}

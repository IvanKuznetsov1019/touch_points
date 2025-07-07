#include <clocale>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class Point {
 public:
  double x, y;
};

class Circle {
 public:
  double x, y, r;
  Point getCenter() const { return {x, y}; }
};

pair<double, double> getSlopes(const Point& p, const Circle& crcl) {
  double tmp = p.y - crcl.y;
  double b = 8 * tmp * (p.x - crcl.x);
  double a = (8 * p.x * crcl.x) - (4 * crcl.x * crcl.x) - (4 * p.x * p.x) +
             (4 * crcl.r * crcl.r);
  double c = 4 * ((crcl.r * crcl.r) - (tmp * tmp));
  double d = (b * b) - (4 * a * c);
  double s = sqrt(d);
  double k1 = (s - b) / (2 * a);
  double k2 = (-s - b) / (2 * a);
  return {k1, k2};
}

Point getTouchPoint(const Point& p, const Point& center, const double k) {
  double tmp = p.y - center.y - (k * p.x);
  double a = (k * k) + 1;
  double b = ((-2 * center.x) + (2 * k * tmp));
  double x = (-b) / (2 * a);
  double y = (k * (x - p.x)) + p.y;
  return {x, y};
}

double angleBetweenLines(const double k1, const double k2) {
  double angle = abs((k1 - k2) / (1 + k1 * k2));
  return angle;
}

pair<double, double> getCorrectSlopes(const pair<double, double>& cxSlopes,
                                      const pair<double, double>& cvSlopes) {
  vector<double> slopes{cxSlopes.first, cxSlopes.second, cvSlopes.first,
                        cvSlopes.second};
  double minAngle = INFINITY;
  pair<double, double> correctSlopes;
  for (int i = 0; i < 4; i++) {
    if (minAngle > angleBetweenLines(slopes[i % 2], slopes[2 + (i / 2)])) {
      minAngle = angleBetweenLines(slopes[i % 2], slopes[2 + (i / 2)]);
      correctSlopes = make_pair(slopes[i % 2], slopes[2 + (i / 2)]);
    }
  }
  return correctSlopes;
}

void input(Point& cxP, Point& cvP, Circle& crcl) {
  cout << "Введите X Y точки cx:" << endl;
  cin >> cxP.x >> cxP.y;
  cout << "Введите X Y точки cv:" << endl;
  cin >> cvP.x >> cvP.y;
  cout << "Введите X Y центра окружности и радиус R:" << endl;
  cin >> crcl.x >> crcl.y >> crcl.r;
}

void output(const Point& cxTouchPoint, const Point& cvTouchPoint,
            const pair<double, double>& slopes) {
  cout << "cx touch point: (" << cxTouchPoint.x << ',' << cxTouchPoint.y << ")"
       << endl;
  cout << "cv touch point: (" << cvTouchPoint.x << ',' << cvTouchPoint.y << ")"
       << endl;
  cout << "cx k = " << slopes.first << " cv k = " << slopes.second << endl;
}

int main() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  Point cxP, cvP;
  Circle crcl;
  input(cxP, cvP, crcl);
  pair<double, double> cxSlopes = getSlopes(cxP, crcl);
  pair<double, double> cvSlopes = getSlopes(cvP, crcl);
  pair<double, double> correctSlopes = getCorrectSlopes(cxSlopes, cvSlopes);
  Point cxTouchPoint =
      getTouchPoint(cxP, crcl.getCenter(), correctSlopes.first);
  Point cvTouchPoint =
      getTouchPoint(cvP, crcl.getCenter(), correctSlopes.second);
  output(cxTouchPoint, cvTouchPoint, correctSlopes);
  return 0;
}

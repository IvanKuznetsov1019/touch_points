#include <cmath>
#include <iostream>

using namespace std;

pair<double, double> getAngularValues(const double xa, const double ya,
                                      const double xb, const double yb,
                                      const double r) {
  double tmp = ya - yb;
  double b = 8 * tmp * (xa - xb);
  double a = (8 * xa * xb) - (4 * xb * xb) - (4 * xa * xa) + (4 * r * r);
  double c = 4 * ((r * r) - (tmp * tmp));
  double D = (b * b) - (4 * a * c);
  double s = sqrt(D);
  double k1, k2;
  k1 = (s - b) / (2.0f * a);
  k2 = (-s - b) / (2.0f * a);
  return make_pair(k1, k2);
}

pair<double, double> getTouchPoint(const double xa, const double ya,
                                   const double xb, const double yb,
                                   const double r, const double k) {
  double tmp = ya - yb - (k * xa);
  double a = (k * k) + 1;
  double b = ((-2 * xb) + (2 * k * tmp));
  double x = (-b) / (2 * a);
  double y = (k * (x - xa)) + ya;
  return make_pair(x, y);
}

pair<double, double> getCorrectAngularValues(
    const pair<double, double> &cxAngularValues,
    const pair<double, double> &cvAngularValues) {
  double k1, k2;
  if (abs(cxAngularValues.first) != abs(cxAngularValues.second)) {
    k1 = (abs(cxAngularValues.first) < abs(cxAngularValues.second))
             ? cxAngularValues.first
             : cxAngularValues.second;
  } else {
    k1 = (cxAngularValues.first > cxAngularValues.second)
             ? cxAngularValues.first
             : cxAngularValues.second;
  }

  if (abs(cxAngularValues.first) != abs(cxAngularValues.second)) {
    k2 = (abs(cvAngularValues.first) < abs(cvAngularValues.second))
             ? cvAngularValues.first
             : cvAngularValues.second;

  } else {
    k2 = (cvAngularValues.first < cvAngularValues.second)
             ? cvAngularValues.first
             : cvAngularValues.second;
  }
  return make_pair(k1, k2);
}

int main() {
  double cxX, cvX, cxY, cvY, cX, cY, r;
  cxX = -11.5;
  cxY = 0.45;
  cvX = -11.5;
  cvY = -0.08;
  cX = -11.76;
  cY = 0.1;
  r = 0.2;

  cout << "Введите X Y точки cx:" << endl;
  cin >> cxX >> cxY;
  cout << "Введите X Y точки cv:" << endl;
  cin >> cvX >> cvY;
  cout << "Введите X Y центра окружности и радиус R:" << endl;
  cin >> cX >> cY >> r;

  pair<double, double> cxAngularValues = getAngularValues(cxX, cxY, cX, cY, r);
  pair<double, double> cvAndularValues = getAngularValues(cvX, cvY, cX, cY, r);
  pair<double, double> correctAngularValues =
      getCorrectAngularValues(cxAngularValues, cvAndularValues);
  pair<double, double> cxTouchPoint =
      getTouchPoint(cxX, cxY, cX, cY, r, correctAngularValues.first);
  pair<double, double> cvTouchPoint =
      getTouchPoint(cvX, cvY, cX, cY, r, correctAngularValues.second);

  cout << "cx touch point: (" << cxTouchPoint.first << ','
       << cxTouchPoint.second << ")" << endl;
  cout << "cv touch point: (" << cvTouchPoint.first << ','
       << cvTouchPoint.second << ")" << endl;
  cout << "cx k = " << correctAngularValues.first
       << " cv k = " << correctAngularValues.second << endl;
  return 0;
}

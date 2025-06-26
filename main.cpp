#include <cmath>
#include <iostream>
#include <map>
#include <utility>

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
                                   const double k) {
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
  map<double, pair<double, double>> angleBetweenLines;
  double tmpK;
  tmpK = abs((cxAngularValues.first - cvAngularValues.first) /
             (1 + (cxAngularValues.first * cvAngularValues.first)));
  angleBetweenLines[tmpK] =
      make_pair(cxAngularValues.first, cvAngularValues.first);

  tmpK = abs((cxAngularValues.first - cvAngularValues.second) /
             (1 + (cxAngularValues.first * cvAngularValues.second)));
  angleBetweenLines[tmpK] =
      make_pair(cxAngularValues.first, cvAngularValues.second);

  tmpK = abs((cxAngularValues.second - cvAngularValues.first) /
             (1 + (cxAngularValues.second * cvAngularValues.first)));
  angleBetweenLines[tmpK] =
      make_pair(cxAngularValues.second, cvAngularValues.first);

  tmpK = abs((cxAngularValues.second - cvAngularValues.second) /
             (1 + (cxAngularValues.second * cvAngularValues.second)));
  angleBetweenLines[tmpK] =
      make_pair(cxAngularValues.second, cvAngularValues.second);

  double minimumAngle = tmpK;
  for (auto [angle, kValues] : angleBetweenLines) {
    if (angle < minimumAngle) {
      minimumAngle = angle;
    }
  }
  return angleBetweenLines[minimumAngle];
}

int main() {
  double cxX, cvX, cxY, cvY, cX, cY, r;

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
      getTouchPoint(cxX, cxY, cX, cY, correctAngularValues.first);
  pair<double, double> cvTouchPoint =
      getTouchPoint(cvX, cvY, cX, cY, correctAngularValues.second);

  cout << "cx touch point: (" << cxTouchPoint.first << ','
       << cxTouchPoint.second << ")" << endl;
  cout << "cv touch point: (" << cvTouchPoint.first << ','
       << cvTouchPoint.second << ")" << endl;
  cout << "cx k = " << correctAngularValues.first
       << " cv k = " << correctAngularValues.second << endl;
  return 0;
}

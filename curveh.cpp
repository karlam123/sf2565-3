#include "curveh.hpp"
Curveh::Curveh(double a1, double b1, double y0, int r) : Curvebase(a1, b1, r), yc(y0){
    length = integrate(a1, b1);
}

double Curveh::xp(double p) const {
    return xy+rev*(p-a);
}
double Curveh::yp(double p) const {
    return yc;
}
double Curveh::dxp(double p) const {
    return rev;
}
double Curveh::dyp(double p) const {
    return 0;
}

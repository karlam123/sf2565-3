#include "curvev.hpp"
#include <iostream>
Curvev::Curvev(double a1, double b1, double x0, int r) : Curvebase(a1, b1, r), xc(x0) {
    length = integrate(a1, b1);
}

// TODO: Check bounds, a < p <b etc..
double Curvev::xp(double p) const {
    return xc;
}
double Curvev::yp(double p) const {
    return xy+rev*(p-a);
}
double Curvev::dxp(double p) const {
    return 0;
}
double Curvev::dyp(double p) const{
    return rev;
}


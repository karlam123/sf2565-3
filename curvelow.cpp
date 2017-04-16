#include "curvelow.hpp"
#include <cmath>
#include <iostream>

Curvelow::Curvelow(double a1, double b1, double c1, int r) : Curvebase(a1, b1, r), c(c1) {
    length = integrate(a1, b1);
}

double Curvelow::xp(double p) const {
    return xy+rev*(p-a);

}
double Curvelow::yp(double p) const {
    p = xp(p);
    if (a <= p && p < c) {
        return 0.5/(1+std::exp(-3*(p+6)));
    } else if (c <= p && p <= b) {
        return 0.5/(1+std::exp(3*p));
    }
    return 0.0;
}

double Curvelow::dxp(double p) const {
    return rev;
}

double Curvelow::dyp(double p) const {
    p = xp(p);
    if ( a <= p && p < c) {
        double tmp1 = (1+std::exp(-3*(p+6)));
        double tmp2 = tmp1-1;
        return 1.5*rev*tmp2/(tmp1*tmp1);
    } else if (c <= p  && p <= b) {
        double tmp1 = (1+std::exp(3*p));
        double tmp2 = tmp1-1;
        return -1.5*rev*tmp2/(tmp1*tmp1);
    }
    return 0.0;
}

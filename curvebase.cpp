#include <cmath>
#include <iostream>
#include "curvebase.hpp"

Curvebase::Curvebase() : a(0.0), b(1.0), rev(1), pmin(a), pmax(b){

}

Curvebase::Curvebase(double a1, double b1, int r) : a(a1), b(b1), rev(r), pmin(a1), pmax(b1) {
    if (b < a) {
        std::cout << "Warning: a = " << a << " should be less than b = " << b << std::endl;
        std::cout << "Will reverse orientation and swap a and b" << std::endl;
        double tmp = b;
        b = a;
        a = tmp;
        rev *= -1;
    }
    if (r==-1) {
        xy = b1;
    } else {
        xy = a1;
    }
}

double Curvebase::x(double s) const {
    //*********Newton's algorithm**************
    double p = a;  //p0
    double h = -(integrate(a,p)-s*length)/fdx(p);
    while (std::fabs(h) > 1e-9) {
        h = -(integrate(a,p)-s*length)/fdx(p);
        p += h;
    }
    //*****************************************
    return xp(p);
}

double Curvebase::y(double s) const {
    //*********Newton's algorithm**************
    double p = a;  //p0
    double h = -(integrate(a,p)-s*length)/fdx(p);
    while (std::fabs(h) > 1e-9) {
        h = -(integrate(a,p)-s*length)/fdx(p);
        p += h;
    }
    //*****************************************
    return yp(p);
}

double Curvebase::fdx(double p) const {
    double x2 = std::pow(dxp(p), 2);
    double y2 = std::pow(dyp(p), 2);
    return std::sqrt(x2+y2);
}


double Curvebase::getRev() const {
    return rev;
}

double Curvebase::integrate(double a1, double b1) const {
    return ASI(a1, b1, 1e-9);
}


// **************Assignment 1 ***************************
double Curvebase::I(const double a1, const double b1) const {
    return (b1-a1)/6*(fdx(a1)+4*fdx((a1+b1)/2)+fdx(b1));
}

double Curvebase::I2(const double a1, const double b1) const {
    const double c = (a1+b1)/2;
    return I(a1,c)+I(c,b1);
}

double Curvebase::ASI(const double a1, const double b1, const double tol) const {
    const double i1 = I(a1,b1);
    const double i2 = I2(a1,b1);
    const double errest = std::fabs(i1-i2);
    if (15*errest < tol) return i2;
    const double c = (a1+b1)/2;
    return ASI(a1,c, tol/2)+ASI(c, b1, tol/2);
}

//****************************************************************

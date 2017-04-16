#include "asi.hpp"
#include <cmath>
#include <iostream>
double I(const double a, const double b, double f(double x));
double I2(const double a, const double b);


double I(const double a, const double b, double f(double x)) {
    return (b-a)/6*(f(a)+4*f((a+b)/2)+f(b));
}
double I2(const double a, const double b, double f(double x)) {
    const double c = (a+b)/2;
    return I(a,c,f)+I(c,b,f);
}

double ASI(double f(double x), const double a, const double b, const double tol) {
    const double i1 = I(a,b,f);
    const double i2 = I2(a,b,f);
    const double errest = std::fabs(i1-i2);
    if (15*errest < tol) return i2;
    const double c = (a+b)/2;
    return ASI(f, a,c, tol/2)+ASI(f, c, b, tol/2);
}

#ifndef CURVEH_HPP
#define CURVEH_HPP
#include "curvebase.hpp"
class Curveh : public Curvebase {
public:
    Curveh(double a1, double b1, double yc, int r=1);
private:
    double yc;  // y coordinate constat in horizontal line
    double xp(double p) const;
    double yp(double p) const;
    double dxp(double p) const;
    double dyp(double p) const;
};
#endif // CURVEH_HPP

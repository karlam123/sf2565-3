#ifndef CURVEV_HPP
#define CURVEV_HPP

#include "curvebase.hpp"
// Class for representing vertical curve

class Curvev : public Curvebase {
public:
    Curvev(double a1, double b1, double x, int r=1);
private:
    double xc; // x coordinate in vertical curve
    double xp(double p) const;
    double yp(double p) const;
    double dxp(double p) const;
    double dyp(double p) const;
};
#endif // CURVEV_HPP

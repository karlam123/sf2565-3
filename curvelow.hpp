#ifndef CURVELOW_HPP
#define CURVELOW_HPP
#include "curvebase.hpp"

// Lower boundary as specified in the assignment

class Curvelow : public Curvebase {
public:
    Curvelow(double a1, double b1, double c1, int r=1);
private:
    double c;
    double xp(double p) const;
    double yp(double p) const;
    double dxp(double p) const;
    double dyp(double p) const;
};
#endif // CURVELOW_HPP

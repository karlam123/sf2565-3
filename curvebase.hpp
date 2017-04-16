#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

class Curvebase {
protected:
    double a;
    double b;
    int rev; // orientation of the curve
    double xy; //where line starts
    double pmin;
    double pmax;

    double length;

    virtual double xp(double p) const = 0;
    virtual double yp(double p) const = 0;
    virtual double dxp(double p) const = 0;
    virtual double dyp(double p) const = 0;

    double fdx(double p) const; // that which we integrate over
    double integrate(double a, double b) const; //arc length integral

public:
    Curvebase(); //constructor
    Curvebase(double a1, double b1, int r=1);
    double x(double s) const; //arc length parametrization
    double y(double s) const; //arc length parametrization
    double getRev() const;  // get the orientation of the curve

private:
    double I(const double a, const double b) const;
    double I2(const double a, const double b) const;
    double ASI( const double a, const double b, const double tol) const;
};
#endif // CURVEBASE_HPP

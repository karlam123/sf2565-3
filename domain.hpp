#ifndef DOMAIN_HPP
#define DOMAIN_HPP
#include "curvebase.hpp"
#include <vector>
#include <array>
class Domain {
public:
    Domain(const Curvebase* s1, const Curvebase* s2,
           const Curvebase* s3, const Curvebase* s4);
    Domain(const Domain&);
    Domain& operator=(const Domain &);
    ~Domain();
    void grid_generation(int m, int n);
    void writeGrid(int m, int n);
    // more members
private:
    const Curvebase *sides[4];
    double rs[4];  // Orientation of the sides
    std::vector<double> x_, y_;
    int m_, n_;
    bool check_consistency();
};
#endif // DOMAIN_HPP


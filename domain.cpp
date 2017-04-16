#include "domain.hpp"
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
double xy(double c, int r);

// Require consistent orientation and that the endpoints meet
// Side 0  must correspond to the x-axis in the unit square
// the rest of the sides must be added in a clockwise order
Domain::Domain(const Curvebase* s1, const Curvebase* s2,
               const Curvebase* s3, const Curvebase* s4) {
    sides[0] = s1;
    sides[1] = s2;
    sides[2] = s3;
    sides[3] = s4;
    for (int i = 0; i < 4; i++) {
        rs[i] = sides[i]->getRev();
    }
    if (check_consistency()==false) {
        sides[0] = sides[1] = sides[2] = sides[3] = nullptr;
    }
    m_ = n_ = 0;
}

Domain::Domain(const Domain& d) :
    m_(d.m_), n_(d.n_) {
    if (m_ > 0) {
            x_ = d.x_;
            y_ = d.y_;  // vector deep copy by default
    }
}

Domain& Domain::operator=(const Domain& d) {
    if (this != &d) {     // Do not copy to itself
        if (m_ == d.m_ && n_ == d.n_) {
            x_ = d.x_;
            y_ = d.y_;
        } else {
            if (m_ > 0) {
                x_.erase(x_.begin(), x_.end());
                y_.erase(y_.begin(), y_.end());
            }
            m_ = d.m_;
            n_ = d.n_;
            if (m_ > 0) {
                x_ = d.x_;
                y_ = d.y_;
            }
        }

    }
    return *this;
}

bool Domain::check_consistency() {
    // Require consistent orientation and that the endpoints meet
    // Side 0  must correspond to the x-axis in the unit square
    // the rest of the sides must be added in a clockwise order


    // Positive orientation
    bool consistent = true;
    for (int i = 0; i < 4; i++) {
        consistent = consistent && (std::fabs((sides[i%4]->x(1)-sides[(i+1)%4]->x(0)))< 1e-5) && (std::fabs(sides[i%4]->y(1) - sides[(i+1)%4]->y(0))<1e-5);
    }
    if (consistent) {
        return consistent;
    }
    // Negative orientation
    consistent = true;
    for (int i = 0; i < 4; i++) {
        consistent = consistent && (std::fabs((sides[i%4]->x(1)-sides[(i-1)%4]->x(0)))< 1e-5) && (std::fabs(sides[i%4]->y(1) - sides[(i-1)%4]->y(0))<1e-5);
    }
    return consistent;
}

void Domain::grid_generation(int m, int n) {
    if (m <= 0 || n <= 0) {
        std::cout << "Cannot generate a grid with m=" << m << " and n=" << n << std::endl;
    } else {
        m_ = n;
        n_ = m;
        x_.resize(m_*n_);
        y_.resize(m_*n_);

        // Fill x_ and y_ with values!
        const double h1 = 1/((double)(m_-1));
        const double h2 = 1/((double)(n_-1));
        double c1 = 0.0;
        double c2 = 0.0;
        double tmpx[8] = {};
        double tmpy[8] = {};
        for (int i = 0; i < m_; i++) {
            for (int j = 0; j < n_; j++) {
                c2 = j*h2;
                c1 = i*h1;

                tmpx[0] = (1-c2)*sides[0]->x(xy(c1, rs[0]));
                tmpx[1] = c2*sides[2]->x(xy(c1, rs[2]));
                tmpx[2] = (1-c1)*sides[1]->x(xy(c2, rs[1]));
                tmpx[3] = c1*sides[3]->x(xy(c2, rs[3]));
                tmpx[4] = -(1-c1)*(1-c2)*sides[0]->x(xy(0, rs[0]));
                tmpx[5] = -c1*c2*sides[2]->x(xy(1, rs[2]));
                tmpx[6] = -c1*(1-c2)*sides[3]->x(xy(0, rs[3]));
                tmpx[7] = -(1-c1)*c2*sides[1]->x(xy(1, rs[1]));

                tmpy[0] = (1-c2)*sides[0]->y(xy(c1, rs[0]));
                tmpy[1] = c2*sides[2]->y(xy(c1, rs[2]));
                tmpy[2] = (1-c1)*sides[1]->y(xy(c2, rs[1]));
                tmpy[3] = c1*sides[3]->y(xy(c2, rs[3]));
                tmpy[4] = -(1-c1)*(1-c2)*sides[0]->y(xy(0, rs[0]));
                tmpy[5] = -c1*c2*sides[2]->y(xy(1, rs[2]));
                tmpy[6] = -c1*(1-c2)*sides[3]->y(xy(0, rs[3]));
                tmpy[7] = -(1-c1)*c2*sides[1]->y(xy(1, rs[1]));

                for (int k =0; k < 8; k++) {
                    x_[i+j*m_] += tmpx[k];
                    y_[i+j*m_] += tmpy[k];
                }
            }
        }
        m_ = m;
        n_ = n;
    }
}

// When doing interpolation, opposite side must have the same orientation
double xy(double c, int r) {
    if (r==1) {
        return c;
    }
    return 1-c;
}
void Domain::writeGrid(int m, int n) {
    grid_generation(m, n);
    if (m > 0 && n > 0) {

        // Code taken from http://stackoverflow.com/a/18015156
        std::ofstream os{"outfile.bin", std::ios::out | std::ios::binary};
        const auto& m1 = (double) m;
        const auto& n1 = (double) n;
        os.write(reinterpret_cast<const char*>(&m1), sizeof(m1));
        os.write(reinterpret_cast<const char*>(&n1), sizeof(n1));
        for (const auto& value : x_) {
            os.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
        for (const auto& value : y_) {
            os.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }

}
Domain::~Domain() {
}

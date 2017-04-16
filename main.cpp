#include <iostream>
#include "curvebase.hpp"
#include "curvev.hpp"
#include "curveh.hpp"
#include "curvelow.hpp"
#include "domain.hpp"
using namespace std;

int main()
{
    // Test of task 3

    const Curvev *c0 = new Curvev(0, 3, -10, 1);
    const Curveh *c1 = new Curveh(-10, 5, 3, 1);
    const Curvev *c2 = new Curvev(0, 3, 5, -1);
    const Curvelow *c3 = new Curvelow(-10,5,-3, -1);
    Domain d = Domain(c3, c0, c1, c2);  // Anticlockwise order
    d.writeGrid(50, 20);

    delete c0, c1, c2, c3;

    return 0;
}

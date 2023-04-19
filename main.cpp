#include "LinearProgramming.h"

int main() {
    int con = 5;
    int var = 2;
    LinearProgramming lp(con, var);

    float constraints[][3] = {
        {1, 0, 4},
        {0, 2, 12},
        {3, 2, 18},
        {-1, 0, 0},
        {0, -1, 0}
    };
    for (int i = 0; i < con; ++i) {
        lp.setConstraint(i, constraints[i]);
    }
    lp.checkFeasibility();
    lp.bindingPlanes();

    return 0;
}

#ifndef LINEAR_PROGRAMMING_H
#define LINEAR_PROGRAMMING_H

#include <iostream>
#include <iomanip>
#include <cmath>

class LinearProgramming {
public:
    LinearProgramming(int con, int var);
    void setConstraint(int index, const float constraint[]);
    void checkFeasibility();
    void bindingPlanes();

private:
    void display(float a[], int k);
    void comb(int s[], int k, int fix);
    void fixComb(int s[], int noOfElmts, int fixpos);
    void intChange(int& a, int& b);
    void copyArray(int a[], int b[]);
    void del(int a[], int d);
    void displayMat(int r, int c);
    void solve(int k, int b[]);
    void feasibility();
    bool isFeasible(float* asoln);
    void bindingPlanesHelper(int index[]);

    const int m = 20;
    const int n = 20;
    int s[20];
    int con;
    int var;
    float equ[20][20];
    float soln[20][20];
    int row = 0;
    bool flag = false;
};

#endif // LINEAR_PROGRAMMING_H

#include "LinearProgramming.h"
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;


LinearProgramming::LinearProgramming(int con, int var) : con(con), var(var), row(0), flag(false) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            equ[i][j] = 0;
        }
    }
}

void LinearProgramming::setConstraint(int index, const float constraint[]) {
    s[index]=index+1;
    s[index+1]='\0';
    for (int j = 0; j <= var; ++j) {
        equ[index + 1][j] = constraint[j];
    }
}

void LinearProgramming::checkFeasibility() {
    displayMat(con+1,var+1);
    comb(s, var, 0);
    feasibility();
}

void LinearProgramming::bindingPlanes() {
    bindingPlanesHelper(s);
}

void LinearProgramming::comb(int s[], int k, int fix) {
    int a[10];
    copyArray(s, a);
    if (k == fix) {
        solve(k, a);
    } else {
        comb(a, k, fix + 1);
        for (; a[k] != '\0';) {
            del(a, fix + 1);
            comb(a, k, fix + 1);
        }
    }
}

void LinearProgramming::solve(int k, int b[]) {
    int u = k;
    int v = k + 1;
    float a[m][n], ak, al;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= k; j++) {
            a[i][j] = equ[b[i]][j];
        }
    }

    for (int i = 0; i < u; i++) {
        if (a[i][i] == 0) {
            for (int k = i + 1; k < u; k++) {
                if (a[k][i] != 0) {
                    for (int j = 0; j < v; j++) {
                        a[u][j] = a[k][j];
                        a[k][j] = a[i][j];
                        a[i][j] = a[u][j];
                    }
                    break;
                }
            }
        }

        if (a[i][i] == 0) {
            return;
        }

        ak = a[i][i];

        for (int j = 0; j < v; j++) {
            a[i][j] *= 1 / ak;
        }

        for (int k = 0; k < u; k++) {
            if (k == i) {
                continue;
            }
            al = a[k][i];
            for (int j = 0; j < v; j++) {
                a[k][j] += -al * a[i][j];
            }
        }
    }

    for (int j = 0; j < u; j++) {
        if (abs(a[j][v - 1]) < 0.001) {
            a[j][v - 1] = 0;
        }
        soln[row][j] = a[j][v - 1];
    }

    row++;
}


void LinearProgramming::copyArray(int a[], int b[]) {
    int k;
    for (int i = 0; a[i] != '\0'; i++) {
        b[i] = a[i];
        k = i + 1;
    }
    b[k] = '\0';
}

void LinearProgramming::del(int a[], int d) {
    for (int t = d - 1; a[t] != '\0'; t++) {
        a[t] = a[t + 1];
    }
}

void LinearProgramming::intChange(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void LinearProgramming::feasibility() {
  int numsoln = row;
  cout << "There are overall " << row << " corner point solutions.\n";
  for (int i = 0; i < numsoln; i++) {
    if (isFeasible(soln[i])) {
      cout << "(";
      for (int j = 0; j < var; j++) {
        cout << soln[i][j];
        if (j != var - 1)
          cout << ",";
      }
      cout << ") : is feasible corner point\n";
    } else {
      cout << "\t\t\t\t (";
      for (int j = 0; j < var; j++) {
        cout << soln[i][j];
        if (j != var - 1)
          cout << ",";
      }
      cout << ") : is not feasible corner point \n";
    }
  }
}
bool LinearProgramming::isFeasible(float* asoln) {
    float remain[m];
    for (int i = 0; i < con; i++) {
        remain[i] = 0;
        for (int j = 0; j < var; j++)
            remain[i] = remain[i] + equ[i + 1][j] * asoln[j];
        remain[i] -= equ[i + 1][var];
        if (remain[i] > 0) return false;
    }
    return true;
}

void LinearProgramming::bindingPlanesHelper(int index[]) {
    row = 0;
    for (int i = 1; i <= con; i++) {
        cout << "\n the plane " << i;
        fixComb(index, var, i);
        int numsoln = row;
        for (int j = 0; j < numsoln; j++) {
            if (isFeasible(soln[j])) {
                flag = true;
            }
        }
        if (flag) cout << " touches the feasible region";
        else cout << " does not touch the feasible region ";
        row = 0;
        flag = false;
    }
}

void LinearProgramming::fixComb(int s[], int noofelmts, int fixpos) {
    intChange(s[0], s[fixpos - 1]);
    comb(s, noofelmts, 1);
}

void LinearProgramming::displayMat(int r, int c) {
    cout << "Problem consists of " <<var<<" variables and "<<con<<" constraints"<< endl;
    for (int i = 1; i < r; i++) {
        cout << "\t";
        display(equ[i], c);
        cout << endl;
    }
}

void LinearProgramming::display(float a[], int c) {
    char sym ='+';
    for (int j = 0; j < c; j++) {
        if (j == c - 1) 
            cout <<setw(6)<<"≤";
        cout << setw(4)<<a[j] ;
        
    }
}

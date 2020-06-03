//Vandermode行列をmersenne_twiser.hを用いて作成し、それをLU分解して固有値を求めたものと厳密解とを比べるプログラム
#include <iostream>
#include <math.h>
#include "mersenne_twister.h"
#define double long double
using namespace std;
int main() {
    int n = 30;
    int seed = 12345;
    int i, j, k, l;
    double sum1, sum2;
    double V[n][n], L[n][n], U[n][n];
    double b[n], x[n], y[n];
    //Vandermonde行列の作成
    init_genrand(seed);
    for(i = 0; i<n; i++){
        V[i][1] = genrand_real3();
    }
    for(i=0; i<n; i++){
        for(j=0; j<n ; j++){
            L[j][i] = 0.0;
            U[j][i] = 0.0;
            if(i==0){
                V[j][0] = 1;
            }else if(i==1){
                continue;
            }else{
                V[j][i] = V[j][i-1]*V[j][1];
            }
        }
    }
    //完成
    //L行列とU行列のの導出
    for(i=0; i<n; i++){
        L[i][i] = 1.0;
    }
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(i<=j){
                sum1 = 0.0;
                for(k=0; k<i; k++){
                    sum1 += L[i][k]*U[k][j];
                }
                U[i][j] = V[i][j] - sum1;
            }else{
                sum2 = 0.0;
                for(l=0; l<j; l++){
                    sum2 += L[i][l]*U[l][j];
                }
                L[i][j] = (V[i][j]-sum2)/U[j][j];
            }
        }
    }
    double det = 1.0;
    for (int m = 0; m < n ; ++m) {
        det = det*U[m][m]*L[m][m];
    }
    cout << det << endl;

    double true_ans = 1.0;
    for(i=0; i<n ; i++){
        for(j=0; j<n; j++){
            if(i>=j){
                continue;
            }
            true_ans = true_ans*(V[j][1]-V[i][1]);
        }
    }
    cout << true_ans << endl;

    cout << "誤差は" << abs(true_ans - det)/true_ans << "です." << endl;

}

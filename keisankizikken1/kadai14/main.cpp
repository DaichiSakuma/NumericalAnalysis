#include <iostream>
#include <math.h>
#include <algorithm>
#include<fstream>
#include <chrono>
using namespace std;
int main() {
    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    start = std::chrono::system_clock::now(); // 計測開始時間
    //２次元ラプラス方程式をヤコビ法で解くプログラム
    //境界条件はu(0, y) = sin(2πy), u(1, y) = sin(πy), u(x, 0) = u(x, 1) = 0.0
    double delta_l = 0.002; //グリッド幅
    double ll = 1;
    int l = int(ll/delta_l);

    double phi1[l+1][l+1];
    double phi2[l+1][l+1];//temp用
    for (int i1 = 0; i1 < l+1 ; ++i1){
        for (int i = 0; i < l+1 ; ++i) {
            phi1[i1][i] = 0;
            phi2[i1][i] = 0;
            if(i==0){
                phi1[i1][0] = sin(2.0*M_PI*i1*delta_l);
            }
            if(i==l){
                phi1[i1][l] = sin(M_PI*i1*delta_l);
            }
        }
    }
    double phi3[l+1][l+1];
    double phi4[l+1][l+1];
    double last_delta = 0.0001;//収束条件

    double delta = 1.0;
    while(delta > last_delta){
        double max_delta = 0;
        for (int i = 0; i < l+1; ++i) {
            for (int j = 0; j < l+1 ; ++j) {
                if( i==0 || j==0 || i==l || j==l){
                    phi2[i][j] = phi1[i][j];
                }else{
                    phi2[i][j] = 0.25*(phi1[i+1][j]+phi1[i][j+1]+phi1[i-1][j]+phi1[i][j-1]);
                }
            }
        }
        for (int k = 0; k < l+1 ; ++k) {
            for (int i = 0; i < l+1 ; ++i) {
                max_delta = max(max_delta, abs(phi1[k][i]-phi2[k][i]));
            }
        }
        delta = max_delta;
        for (int m = 0; m < l+1; ++m) {
            for (int i = 0; i < l+1 ; ++i) {
                phi3[i][m] = phi1[i][m];
                phi4[i][m] = phi2[i][m];
                phi1[i][m] = phi4[i][m];
                phi2[i][m] = phi3[i][m];
            }
        }
    }
    /*
    for (int n = 0; n < l+1 ; ++n) {
        for (int i = 0; i < l+1 ; ++i) {
            cout << phi1[n][i] << " ";
        }

    }
    */

    ofstream outputfile("grid0002.txt");
    for (int k1 = 0; k1 < l+1 ; ++k1) {
        for (int i = 0; i < l+1; ++i) {
            outputfile << i*delta_l << " " << k1*delta_l << " " << phi1[k1][i] << endl;
        }

    }
    outputfile.close();
    end = std::chrono::system_clock::now();  // 計測終了時間
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
    cout << "かかった時間は" << elapsed << "msです" << endl;


}
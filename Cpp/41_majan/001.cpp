#include <bits/stdc++.h>
using namespace std;

double f(int i, double r, double r_ave){
    double rtn = r + 10.0 - 4*i + (r_ave-r)*3/800;
    return rtn;
}

int main(){
    srand(time(NULL));
    int n, m;
    cin >> n >> m;
    double r_ave = 0;
    vector<double> v;
    for(int i = 0; i < n; i++){
        double r = 0;
        for(int j = 0; j < m; j++){
            r = f(rand()%4+1, r, r_ave);
        }
        v.push_back(r);
    }
    for(double i : v){
        cout << i << endl;
    }
}
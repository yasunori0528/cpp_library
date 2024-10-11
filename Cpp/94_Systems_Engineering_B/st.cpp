// Simplex Tableau

#include <bits/stdc++.h>
using namespace std;

struct simplex{
    vector<double> obj;//目的関数
    vector<vector<double>> sub;//条件式 sub[i][0] = Σ(sub[i][j]*x_j)
    vector<double> base;
    vector<double> theta;
    vector<double> d;
    //基底変数n個,変数m個,式l個,
    simplex(){
        ;
    }
    simplex(int n, int m, int l){
        obj.resize(m+1,0);
        sub.resize(l,vector<double>(m+1));
        base.resize(l);
        theta.resize(l);
        d.resize(m+1);
    }
};

int INF = 1<<30;
int n, m, l;
vector<simplex> v(1);

void input(){
    cin >> n >> m >> l;
    v[0] = simplex(n,m,l);
    for(int i = 1; i <= n; i++){
        cin >> v[0].obj[i];
    }
    for(int i = 0; i < l; i++){
        for(int j = 0; j <= m; j++){
            cin >> v[0].sub[i][j];
        }
    }
    for(int i = 0; i < l; i++){
        v[0].base[i] = i+1+n;
    }
    for(int j = 0; j <= m; j++){
        v[0].d[j] = v[0].obj[j];
        double min_j = -1;
        double min_dj = 0;
        for(int i = 0; i < n; i++){
            int base_i = v[0].base[i];
            v[0].d[j] -= v[0].obj[base_i]*v[0].sub[i][base_i];
        }
        if(min_dj > v[0].d[j]){
            min_j = j;
            min_dj = v[0].d[j];
        }

    }
    return;
}

void calc(int a){
    if(a > 10) return;

    int min_j = -1;
    double min_dj = 0;
    for(int j = 0; j <= m; j++){
        v[a].d[j] = v[a].obj[j];
        for(int i = 0; i < l; i++){
            int base_i = v[a].base[i];
            v[a].d[j] -= v[a].obj[base_i]*v[a].sub[i][j];
        }
        if(min_dj > v[a].d[j]){
            min_j = j;
            min_dj = v[a].d[j];
        }
    }
    if(min_j < 0) return;
    int new_base = min_j;
    int min_i = -1;
    double min_theta_i = INF;
    for(int i = 0; i < l; i++){
        v[a].theta[i] = v[a].sub[i][0]/v[a].sub[i][new_base];
        if(min_theta_i > v[a].theta[i]){
            min_i = i;
            min_theta_i = v[a].theta[i];
        }
    }
    v.push_back(simplex(n,m,l));
    v[a+1].obj = v[a].obj;
    for(int j = 0; j <= m; j++){
        v[a+1].sub[min_i][j] = v[a].sub[min_i][j] / v[a].sub[min_i][new_base];
    }
    for(int i = 0; i < l; i++){
        if(i == min_i) continue;
        for(int j = 0; j <= m; j++){
            v[a+1].sub[i][j] = v[a].sub[i][j] - v[a].sub[i][new_base]*v[a+1].sub[min_i][j];
        }
    }
    v[a+1].base = v[a].base;
    v[a+1].base[min_i] = new_base;

    calc(a+1);
}

void output(){
    cout << "minimize ";
    bool b = false;
    for(int i = 0; i <= m; i++){
        if(v[0].obj[i] == 0) continue;
        if(b) cout << " + ";
        else b = true;
        cout << v[0].obj[i] << "*x_" << i;
    }
    cout << endl;
    cout << "subject to" << endl;
    for(int i = 0; i < l; i++){
        b = false;
        for(int j = 1; j <= m; j++){
            if(v[0].sub[i][j] == 0) continue;
            if(b) cout << " + ";
            else b = true;
            cout << v[0].sub[i][j] << "*x_" << j;
        }
        cout << " = " << v[0].sub[i][0] << endl;
    }
    cout << endl;

    int sz = v.size();
    for(int a = 0; a < sz; a++){
        for(int i = 0; i < l; i++){
            cout << v[a].obj[v[a].base[i]] << ", ";
            cout << "x_" << v[a].base[i] << ", ";
            for(int j = 0; j <= m; j++){
                cout << v[a].sub[i][j] << ", ";
            }
            if(a != sz-1) cout << v[a].theta[i];
            cout << endl;
        }
        cout << ", v_j-z_j, ";
        b = false;
        for(int j = 0; j <= m; j++){
            if(b) cout << ", ";
            else b = true;
            cout << v[a].d[j];
        }
        cout << "\n" << endl;
    }

    cout << "min z = " << -v[sz-1].d[0] << ", when ";
    for(int i = 0; i < l; i++){
        if(v[sz-1].base[i] > n) continue;
        cout << "x_" << v[sz-1].base[i] << " = " << v[sz-1].sub[i][0] << ", ";
    }
    cout << endl;
}

int main(){
    input();
    calc(0);
    output();
    return 0;
}

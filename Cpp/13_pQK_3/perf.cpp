#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

double time_start;
double time_1;
double time_now;
double time_interval;

double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

void printTime(){
    time_now = calcTime();
    time_1 = calcTime();
    //cout << time_now - time_start << "[ms]" << endl;
    int t =  round((time_now - time_start)/1000);
    string s = to_string(t+1000000).substr(1);
    cout << s << "[s]" << endl;
}

bool printTime(double t){
    time_now = calcTime();
    if(time_now - time_1 >= t){
        printTime();
        return 1;
    }
    return 0;
}

template <typename T>
bool chmax(T &a, const T& b) {
  if (a < b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
  if (a > b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

int MAX_N = 64;
vector<vector<int64_t>> v_comb(MAX_N, vector<int64_t>(MAX_N,0));
int64_t comb(int n, int m){
    if(n < 0) return 0;
    if(n == 0 && m == 0) return 1;
    if(n == 0) return 0;
    if(m < 0 || n < m) return 0;
    if(v_comb[n][m]) return v_comb[n][m];
    int64_t rtn = comb(n-1,m-1)+comb(n-1,m);
    v_comb[n][m] = rtn;
    return rtn;
}


int n;
double d = 1;

vector<vector<pair<int,int>>> result;

vector<double> x_min;
vector<double> x_max;

void input(){
    cin >> n;
    result.resize(n,vector<pair<int,int>>(n));
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            int x, y;
            cin >> x >> y;
            result[i][j] = {x,y};
            result[j][i] = {y,x};
        }
    }
    x_min.resize(n,INFINITY);
    x_max.resize(n,-INFINITY);
    x_min[0] = 0;
    x_max[0] = 0;
}

void calc(){
    vector<int> v;
    for(int i = 0; i < n; i++){
        v.push_back(i);
    }

    do{
        double r = 1;
        for(int i = 0; i < 2; i++){
            r *= result[v[i+1]][v[i]].first;
            r /= result[v[i+1]][v[i]].second;
            chmin(x_min[v[i+1]],400*log10(r));
            chmax(x_max[v[i+1]],400*log10(r));
        }
        for(int i : v) cout << i << " "; cout << endl;
    }while(next_permutation(v.begin()+1,v.end()));

    cout << fixed << setprecision(4);
    for(int i = 0; i < n; i++){
        cout << x_min[i] << " " << x_max[i] << endl;
    }

    double p_max = -INFINITY;
    vector<double> ans;
    vector<double> loop_now = x_min;
    while(1){
        //for(double i : loop_now) cout << i << " "; cout << endl;
        double p = 0;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                int wij, lij;
                tie(wij,lij) = result[i][j];
                p += log10(comb(wij+lij,wij));
                p += wij/400.0*(loop_now[i]-loop_now[j]);
                p -= (wij+lij)*log10(pow(10,(loop_now[i]-loop_now[j])/400.0)+1);
            }
        }
        if(chmax(p_max,p)) ans = loop_now; 
        bool b = false;
        for(int i = 0; i < n; i++){
            if(loop_now[i] > x_max[i]-d) continue;
            loop_now[i] += d;
            for(int j = 0; j < i; j++){
                loop_now[j] = x_min[j];
            }
            b = true;

            //if(i == 0) cout << loop_now[i] << endl;
            break;
        }
        if(!b) break;
    }

    for(int i : ans) cout << i << endl;
}

int main(){
    input();
    calc();
}
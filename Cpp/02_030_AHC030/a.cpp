#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

//!時間取得
double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}
double timeStart;
double timeNow;
double timeLimit = 2950;

random_device seed_gen;
mt19937 engine(seed_gen());
double rand_double(double l, double r){
    return l + engine() * (r - l) / UINT32_MAX;
}
int rand_int(int l, int r){
    return l + engine()%(r - l);
}

int N, M;
double eps;
vector<vector<int>> P;

bool debug;
vector<int> d_debug;
vector<int> v_debug;
vector<double> e_debug;


int pair_to_int(int x, int y){
    return x * N + y;
}

pair<int,int> int_to_pair(int z){
    return {z/N, z%N};
}

void input(){
    cin >> N >> M >> eps;
    P.resize(M);
    for(int i = 0; i < M; i++){
        int d; cin >> d;
        P[i].resize(d);
        for(int j = 0; j < d; j++){
            int x, y;
            cin >> x >> y;
            P[i][j] = pair_to_int(x, y);
        }
    }

    if(debug){
        d_debug.resize(M);
        for(int i = 0; i < M; i++){
            int x, y;
            cin >> x >> y;
            d_debug[i] = pair_to_int(x, y);
        }
        v_debug.resize(N*N);
        for(int i = 0; i < N*N; i++){
            cin >> v_debug[i];
        }
        e_debug.resize(2*N*N);
        for(int i = 0; i < 2*N*N; i++){
            cin >> e_debug[i];
        }
    }
}

int interactive(bool b, vector<int> v, int query_cnt){
    if(b) cout << "a ";
    else cout << "q ";

    int d = v.size();
    cout << d;

    for(auto x : v){
        auto [i, j] = int_to_pair(x);
        cout << ' ' << i << ' ' << j;
    }
    cout << endl;

    if(b) return 0;

    int rtn;
    if(debug){
        int sumv = 0;
        for(auto x : v){
            sumv += v_debug[x];
        }

        double sigma = 0;
        double mu = sumv;
        if(d > 1){
            sigma = sqrt(d * eps * (1 - eps));
            mu = (d - sumv) * eps + sumv * (1 - eps);
        }

        rtn = max(0.0, round(sigma * e_debug[query_cnt] + mu));
        //cout << "intract: " << sigma << " * " << e_debug[query_cnt] << " + " << mu << " -> " << rtn << endl;
    }
    else{
        cin >> rtn;
    }
    
    return rtn;
}

int interactive_rect(int u, int d, int l, int r, int query_cnt){
    bool b = false;
    vector<int> v;
    for(int i = u; i < d; i++){
        for(int j = l; j < r; j++){
            v.push_back(pair_to_int(i, j));
        }
    }
    return interactive(b, v, query_cnt);
}

double rect_value(int x, int y){
    double sigma = sqrt(eps * (1 - eps) * y);
    double p = x;
    return p;
}

string hex_str = "0123456789abcdef";
void color(int v, int s, int u, int d, int l, int r){
    //cout << v << " " << s << " " << u << " " << d << " " << l << " " << r << endl;
    if(s == 0) return;
    int a = max(0, min(255, 255 * v / s));

    string code;
    code.push_back(hex_str[a/16]);
    code.push_back(hex_str[a%16]);
    code = code + code + code;
    code = "#" + code;

    for(int i = u; i < d; i++){
        for(int j = l; j < r; j++){
            cout << "#c " << i << " " << j << " " << code << endl;
        }
    }
}

void calc(){
    int v_all = 0;
    for(auto p : P) v_all += p.size();
    priority_queue<tuple<double,int,int,int,int,int>> q;
    q.push({rect_value(v_all, N * N), v_all, 0, N, 0, N});
    
    vector<int> ans;
    int v_now = 0;
    for(int i = 0; i < 2*N*N && q.size() && v_now < v_all;){
        auto [ignore, vsum, u, d, l, r] = q.top();
        q.pop();
        //cout << "pop: " << vsum << " " << u << " " << d << " " << l << " " << r << endl;
        /*if(vsum == 0 && (d - u) * (r - l) <= 2){
            continue;
        }*/
        int u1, d1, l1, r1;
        int u2, d2, l2, r2;
        if(d - u > r - l){
            u1 = u;
            d1 = u2 = u + (d - u) / 2;
            d2 = d;

            l1 = l2 = l;
            r1 = r2 = r;
        }
        else{
            u1 = u2 = u;
            d1 = d2 = d;

            l1 = l;
            r1 = l2 = l + (r - l) / 2;
            r2 = r;
        }

        //cout << u1 << " " << d1 << " " << l1 << " " << r1 << endl;
        //cout << u2 << " " << d2 << " " << l2 << " " << r2 << endl;

        int area1 = (d1 - u1) * (r1 - l1);
        int area2 = (d2 - u2) * (r2 - l2);
        int vsum1 = interactive_rect(u1, d1, l1, r1, i); i++;
        int vsum2;
        if(1 || area2 == 1){
            vsum2 = interactive_rect(u2, d2, l2, r2, i); i++;
        }
        else{
            vsum2 = vsum - vsum1;
        }

        //cout << area1 << " " << area2 << endl;

        if(area1 > 1) {
            //cout << "push: " << vsum1 << " " << u1 << " " << d1 << " " << l1 << " " << r1 << endl;
            q.push({rect_value(vsum1, area1), vsum1, u1, d1, l1, r1});
        }
        else if(vsum1) {
            ans.push_back(pair_to_int(u1, l1));
            v_now += vsum1;
        }

        if(area2 > 1) {
            q.push({rect_value(vsum2, area2), vsum2, u2, d2, l2, r2});            
            //cout << "push: " << vsum2 << " " << u2 << " " << d2 << " " << l2 << " " << r2 << endl;
        }
        else if(vsum2) {
            ans.push_back(pair_to_int(u2, l2));
            v_now += vsum2;
        }

        if(debug){
            //color(vsum1, area1, u1, d1, l1, r1);
            //color(vsum2, area2, u2, d2, l2, r2);
        }
    }

    interactive(true, ans, 0);
}

int main(){
    debug = false;
    input();
    timeStart = calcTime();
    calc();
}

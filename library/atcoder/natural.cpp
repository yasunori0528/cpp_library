#include <bits/stdc++.h>
using namespace std;

int64_t floor(int64_t x, int64_t y){
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    int64_t r = x%y;
    r = (r+y)%y;
    return (x-r)/y;
}

int64_t ceil(int64_t x, int64_t y){
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    int64_t r = x%y;
    r = (r+y)%y;
    if(r) x += y-r;
    return x/y;
}

int64_t modulo(int64_t x, int64_t y){
    assert(y != 0);
    int64_t r = x % y;
    if(r < 0) r += abs(y);
    return r;
}

int64_t floor(int64_t x, int64_t p, int64_t r){
    int64_t y = (x%p+p)%p;
    if(r <= y) return x - y + r;
    return x - y - p + r;
}

int64_t ceil(int64_t x, int64_t p, int64_t r){
    int64_t y = (x%p+p)%p;
    if(y <= r) return x - y + r;
    return x - y + p + r;
}

int64_t round(int64_t x, int64_t p, int64_t r){
    int64_t a = floor(x, p, r);
    int64_t b = ceil(x, p, r);
    if(x - a < b - x) return a;
    return b;
}

int log_int(int64_t x){
    if(x == 1) return 0;
    return log_int(x/2)+1;
}

int64_t sqrt_int(int64_t x){
    if(x < 1) return 0;
    if(x < 4) return 1;
    int64_t l = 1<<(log_int(x)/2);
    int64_t r = l*2;
    while(r-l > 1){
        int64_t m = (l+r)/2;
        if(m*m <= x) l = m;
        else r = m;
    }
    return l;
}

vector<vector<int64_t>> comb_v;

int64_t comb(int64_t x, int64_t y){
    if(comb_v[x][y] >= 0) return comb_v[x][y];
    if(x < 0) return 0;
    if(y < 0 || x < y) return 0;
    if(y == 0) return 1;
    if(x == y) return 1;
    int64_t rtn = comb(x-1,y-1)+comb(x-1,y);
    comb_v[x][y] = rtn;
    return rtn;
}

void init_comb(int64_t n){
    comb_v.resize(n+1, vector<int64_t>(n+1,-1));
}

int main(){
    srand(time(NULL));
    int N; cin >> N;
    for(int i = 0; i < N; i++){
        int x = rand()%100+1;
        int p = rand()%100+1;
        int r = rand()%p;
        cout << x << " " << p << " " << r << endl;
        cout << floor(x, p, r) << " " << round(x, p, r) << " " << ceil(x, p, r) << endl;
        cout << endl;
    }
}
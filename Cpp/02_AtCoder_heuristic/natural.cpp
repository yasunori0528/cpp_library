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

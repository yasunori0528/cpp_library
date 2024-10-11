#include <bits/stdc++.h>
using namespace std;

//!時間取得
double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}
double timeStart;
double timeNow;
double timeLimit = 1950;

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


void input(){
}

void calc(){
    int x, y;
    x = y = 3;
    cout << x << " " << y << endl;
}

void output(){
}

int main(){
    input();
    timeStart = calcTime();
    srand(time(NULL));
    //cout << "A" << endl;
    calc();
    //cout << "A" << endl;
    output();
    return 0;
}

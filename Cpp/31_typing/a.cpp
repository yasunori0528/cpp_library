#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

//!時間取得
double calcTime()
{
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9);
}

vector<vector<string>> keyboard_layout = {
    {
        "1234567890-^ ",
        "qwertyuiop@[ ",
        "asdfghjkl;:] ",
        "zxcvbnm,./\\  ",
    },
    {
        "!\"#$%&'() =~|",
        "QWERTYUIOP`{ ",
        "ASDFGHJKL+*} ",
        "ZXCVBNM<>?_  "
    }
};

int main(){
    srand(time(NULL));

    int X, Y; cin >> X >> Y;
    int P = 2;
    int Q = 4;
    int R = 13;
    int N; cin >> N;
    vector<int> A(N);//[0,2)
    for(auto &i : A) cin >> i;
    int M; cin >> M;
    vector<int> B(M);//[0,4)
    for(auto &i : B) cin >> i;
    int L; cin >> L;
    vector<int> C(L);//[0,13)
    for(auto &i : C) cin >> i;

    deque<char> s;
    while(s.size() < X*Y){
        char c = keyboard_layout[A[rand()%N]][B[rand()%M]][C[rand()%L]];
        if(c <= 32) continue;
        s.push_back(c);
    }
    
    double t0 = calcTime();
    while(s.size()){
        for(int i = 0; i < X && i < s.size(); i++) cout << s[i];
        cout << endl;
        string t; cin >> t;
        for(char c : t) if(s.size() && c == s[0]) s.pop_front();
    }
    double t_sum = calcTime() - t0;
    cout << t_sum << "[s]" << endl;
    cout << X * Y * 60 / t_sum << "[kpm]" << endl;
}
#include <bits/stdc++.h>
using namespace std;

using state = uint64_t;//本数,点差+512,BULL,15,16,17,18,19,20

string mark_symbol = "-/XO";
vector<int> number = {20,19,18,17,16,15,25};
int over_kill = 200;

int darts(state &s){
    return s >> 38;
}

int score(state &s){
    return (s >> 28 & 1023) - 512;
}

int mark(state &s, int pl, int num){
    return s >> (4*num+2*pl) & 3;
}

void print(state &s){
    int d = darts(s);

    int pl = d/3;
    int dt = d%3;
    int sc = score(s);
    vector<int> first(7);
    vector<int> second(7);
    for(int i = 0; i < 7; i++){
        first[i] = mark(s, 0, i);
        second[i] = mark(s, 1, i);
    }

    cout << "pl: " << pl << endl;
    cout << "dt: " << dt << endl;
    cout << "sc: " << sc << endl;
    for(int i = 0; i < 7; i++){
        cout << mark_symbol[first[i]] << mark_symbol[second[i]] << endl;
    }
}

void hit(state &s, int num, int cnt){
    int d = darts(s);
    int pl = d/3;
    int sc = score(s);
    int fi = mark(s, 0, num);
    int se = mark(s, 1, num);

    if(pl == 0) fi += cnt;
    else se += cnt;
    if(sc < over_kill && fi > 3 && se < 3) {
        sc += (fi - 3) * number[num];
        fi = 3;
    }
    else if(sc > -over_kill && se > 3 && fi < 3){
        sc -= (se - 3) * number[num];
        se = 3;
    }

    d += 1;
    if(d == 6) d = 0;

    s &= ~(uint64_t(7)<<38);
    s |= uint64_t(d)<<38;
    s &= ~(uint64_t(1023)<<28);
    s |= uint64_t(sc+512)<<28;
    s &= ~(uint64_t(3)<<(4*num));
    s |= uint64_t(fi)<<(4*num);
    s &= ~(uint64_t(3)<<(4*num+2));
    s |= uint64_t(se)<<(4*num+2);
}

int main(){
    srand(time(NULL));
    state s = uint64_t(1)<<37;
    print(s);
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 3; j++){
            int num = rand()%7;
            int cnt = rand()%4;
            hit(s, num, cnt);
            cout << number[num] << " * " << cnt << endl;
        }
        print(s);
    }
}

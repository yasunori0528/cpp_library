#include <bits/stdc++.h>
using namespace std;

struct rubik{
    int sz;
    vector<int> corner;
    //vector<int> edge;
    //vector<int> center;

    rubik(int n){
        sz = n;
        corner.resize(8);
        for(int i = 0; i < 8; i++){
            corner[i] = 3*i;
        }
    }
    
    void f(){
        int tmp = corner[0];
        corner[0] = corner[2]/3*3+(corner[2]+2)%3;
        corner[2] = corner[3]/3*3+(corner[3]+1)%3;
        corner[3] = corner[1]/3*3+(corner[1]+2)%3;
        corner[1] = tmp/3*3+(tmp+1)%3;
    }
    void l(){
        int tmp = corner[0];
        corner[0] = corner[4]/3*3+(corner[4]+1)%3;
        corner[4] = corner[6]/3*3+(corner[6]+2)%3;
        corner[6] = corner[2]/3*3+(corner[2]+1)%3;
        corner[2] = tmp/3*3+(tmp+2)%3;
    }
    void u(){
        int tmp = corner[0];
        corner[0] = corner[1];
        corner[1] = corner[5];
        corner[5] = corner[4];
        corner[4] = tmp;
    }
    void f2(){
        f();
        f();
    }
    void l2(){
        l();
        l();
    }
    void u2(){
        u();
        u();
    }
    void inv_f(){
        f();
        f();
        f();
    }
    void inv_l(){
        l();
        l();
        l();
    }
    void inv_u(){
        u();
        u();
        u();
    }
};

bool operator==(const rubik x, const rubik y){
        return (x.sz == y.sz && x.corner == y.corner);
    }
bool operator<(const rubik x, const rubik y){
    if(x.sz != y.sz){
        return x.sz < y.sz;
    }
    return x.corner < y.corner;
}

int main(){
    rubik r(2);
    for(int i = 0; i < 8; i++){
        cin >> r.corner[i];
    }

    queue<rubik> q;
    q.push(rubik(2));
    map<rubik,pair<int,string>> mp;
    mp[rubik(2)] = {0, ""};

    int cnt = 0;
    while(!q.empty()){
        auto pos = q.front();
        q.pop();
        cnt++;
        if(cnt%1000 == 0) cout << cnt << endl;
        if(pos == r){
            cout << mp[pos].second << endl;
            return 0;
        }
        auto i = pos;

        string s = mp[pos].second;
        char c;
        if(s.size()) c = s[s.size()-2];
        
        if(c != 'F'){
            i.f();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "F1";
                q.push(i);
            }
            i.f();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "F2";
                q.push(i);
            }
            i.f();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "F3";
                q.push(i);
            }
            i.f();
        }
        
        if(c != 'L'){
            i.l();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "L1";
                q.push(i);
            }
            i.l();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "L2";
                q.push(i);
            }
            i.l();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "L3";
                q.push(i);
            }
            i.l();
        }
        
        if(c != 'U'){
            i.u();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "U1";
                q.push(i);
            }
            i.u();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "U2";
                q.push(i);
            }
            i.u();
            if(!mp.count(i)){
                mp[i] = mp[pos];
                mp[i].first++;
                mp[i].second += "U3";
                q.push(i);
            }
            i.u();
        }
        
    }
}
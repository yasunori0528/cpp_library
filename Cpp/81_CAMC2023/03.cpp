//3(1)
#include <bits/stdc++.h>
using namespace std;

map<vector<int>,int> grundy;

void cutx(vector<int> &v, int x, int a){
    vector<int> l = v;
    vector<int> r = v;
    int cntl = 0;
    int cntr = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] > x) {
            l[i] = x;
            r[i] = v[i]-x;
        }
        else{
            l[i] = v[i];
            r[i] = 0;
        }
        cntl += l[i];
        cntr += r[i];
    }
    if(cntl < cntr) v = r;
    else if(cntl > cntr) v = l;
    else if(a) v = l;
    else v = r;
}

void cuty(vector<int> &v, int y, int a){
    vector<int> u;
    vector<int> d;
    int cntu = 0;
    int cntd = 0;
    for(int i = 0; i < y; i++){
        u.push_back(v[i]);
        cntu += v[i];
    }
    for(int i = y; i < v.size(); i++){
        d.push_back(v[i]);
        cntd += v[i];
    }
    if(cntu < cntd) v = d;
    else if(cntu > cntd) v = u;
    else if(a) v = u;
    else v = d;
}

void calc(vector<int> v){
    if(grundy.count(v)) return;
    int w = v[0];
    int h = v.size();
    set<int> s;
    for(int i = 1; i < w; i++){
        vector<int> vil = v;
        cutx(vil,i,1);
        calc(vil);
        s.insert(grundy[vil]);
        vector<int> vir = v;
        cutx(vir,i,0);
        s.insert(grundy[vir]);
    }
    for(int i = 1; i < h; i++){
        vector<int> viu = v;
        cuty(viu,i,1);
        calc(viu);
        s.insert(grundy[viu]);
        vector<int> vid = v;
        cuty(vid,i,0);
        s.insert(grundy[vid]);
    }

    {
        int i = 0;
        while(1){
            if(!s.count(i)){
                grundy[v] = i;
                return;
            }
            i++;
        }
    }
}

int main(){
    grundy[{1}] = 0;

    vector<int> v(20,20);
    calc(v);

    for(auto w : grundy){
        if(w.second) continue;
        cout << w.second << " : ";
        cout << w.first[0] << "*" << w.first.size();
        cout << endl;
    }
}
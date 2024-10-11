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

map<string,pair<int,int>> result;

int MAX_N = 32;
struct state{
    int n;
    vector<vector<int>> cnt_vv;
    vector<int> cnt_v;
    vector<bool> participation;
    vector<int> point;
    vector<set<int>> room;
    vector<pair<double,string>> history;

    state(int x){
        n = MAX_N;
        cnt_vv.resize(n,vector<int>(n,0));
        cnt_v.resize(n,0);
        participation.resize(n,false);
        point.resize(n,0);
        room.resize(n);
        for(int i = 0; i < x; i++){
            room[0].insert(i);
        }
    }

    void start(int a, int i, int j){
        if(!room[0].count(i) || !room[0].count(j)){
            cout << "The match cannot start." << endl;
            return;
        }
        if(room[a].size() > 0){
            cout << "This room is in use." << endl;
            return;
        }
        cnt_vv[i][j]++;
        cnt_vv[j][i]++;
        cnt_v[i]++;
        cnt_v[j]++;
        room[0].erase(i);
        room[0].erase(j);
        room[a].insert(i);
        room[a].insert(j);
        participation[i] = true;
        participation[j] = true;

        string s = "start_" + to_string(a) + "_" + to_string(i) + "_" + to_string(j);
        double t = calcTime();
        history.push_back({t,s});
    }

    void finish(int a, string r){
        if(room[a].size() != 2){
            cout << "No matches in this room." << endl;
            return;
        }

        vector<int> v;
        for(int i : room[a]){
            v.push_back(i);
            room[0].insert(i);
        }
        room[a].clear();

        point[v[0]] += result[r].first;
        point[v[1]] += result[r].second;
        string s = "finish_" + to_string(a) + "_" + r;
        double t = calcTime();
        history.push_back({t,s});
    }

    void in(int i){
        room[0].insert(i);
        string s = "in_" + to_string(i);
        double t = calcTime();
        history.push_back({t,s});
    }
    void out(int i){
        room[0].erase(i);
        string s = "out_" + to_string(i);
        double t = calcTime();
        history.push_back({t,s});
    }

    void calc(){
        cout << "calculated" << endl;
    }

    void output_result(){
        for(int i = 0; i < n; i++){
            if(participation[i]){
                cout << i << " " << point[i] << endl;
            }
        }
    }

    void output_history(){
        for(auto p : history){
            cout << p.first << " " << p.second << endl;
        }
    }
};

vector<state> record;

int main(){
    int n; cin >> n;
    record.push_back(state(n));

    int m; cin >> m;
    for(int i = 0; i < m; i++){
        string s;
        int x;
        int y;
        cin >> s >> x >> y;
        result[s] = {x,y};
    }

    int sz = record.size();
    while(1){
        state st = record[sz-1];
        string s; cin >> s;

        if(s == "undo"){
            record.pop_back();
            sz--;
            continue;
        }
        if(s == "calc"){
            st.calc();
            continue;
        }
        if(s == "result"){
            st.output_result();
            continue;
        }
        if(s == "history"){
            st.output_history();
            continue;
        }

        if(s == "start"){
            int a, i, j;
            cin >> a >> i >> j;
            st.start(a,i,j);
        }
        else if(s == "fin"){
            int a;
            string r;
            cin >> a >> r;
            st.finish(a,r);
        }
        else if(s == "in"){
            int i;
            cin >> i;
            st.in(i);
        }
        else if(s == "out"){
            int i;
            cin >> i;
            st.out(i);
        }
        record.push_back(st);
        sz++;
    }
}
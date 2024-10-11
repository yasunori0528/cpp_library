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
double timeLimit;

template<typename T>
void printv(vector<T> &v){
    bool b = false;
    for(auto i : v){
        if(b) cout << " ";
        else b = true;
        cout << i;
    }
    cout << endl;
}

template <typename T>
bool chmin(T &a, const T& b) {
    if (a > b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

int N, M;
vector<vector<int>> Binput;
vector<int> V; // V[i] : iの上にある箱をV[i]個右の山に移し、iを運び出す。
vector<pair<int,int>> BestV;
int BestScore = 1001002003;
void input(){
    cin >> N >> M;
    Binput.resize(M, vector<int>(N/M));
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N/M; j++){
            cin >> Binput[i][j];
            Binput[i][j]--;
        }
    }
}

void calc_greed(int r){
    int score = 0;
    auto B = Binput;

    vector<pair<int,int>> Bpos(N);
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N/M; j++){
            Bpos[B[i][j]] = {i, j};
        }
    }

    vector<pair<int,int>> Move;
    for(int b = 0; b < N; b++){
        auto[i, x] = Bpos[b];
        vector<pair<int,int>> sz(M);
        for(int k = 0; k < M; k++){
            if(k == i) sz[k] = {201, k};
            else sz[k] = {B[k].size(), k};
        }
        sort(sz.begin(), sz.end());
        int j = sz[0].second;
        for(int k = 0; k < M-1; k++){
            if(rand()%r){
                j = sz[k].second;
                break;
            }
        }

        if(x == B[i].size()-1){
            Move.push_back({-1, -1});
            B[i].pop_back();
            continue;
        }
        for(int k = x+1; k < B[i].size(); k++){
            int c = B[i][k];
            if(k == x+1){
                Move.push_back({c, j});
            }
            B[j].push_back(c);
            Bpos[B[j][B[j].size()-1]] = {j, B[j].size()-1};
        }
        score += B[i].size()-x-1 +1;
        while(B[i].size() > x){
            B[i].pop_back();
        }
        /*cout << "----" << b << "----" << endl;
        for(auto k : B){
            for(auto l : k){
                cout << l << " ";
            }
            cout << endl;
        }*/
    }
    if(chmin(BestScore, score)) {
        BestV = Move;
        //cout << BestScore << endl;
    }
}

void calc(){
    V.clear();
    V.resize(N);
    for(int i = 0; i < N; i++){
        V[i] = rand()%(M-1)+1;
    }

    int score = 0;
    auto B = Binput;

    vector<pair<int,int>> Bpos(N);
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N/M; j++){
            Bpos[B[i][j]] = {i, j};
        }
    }

    vector<pair<int,int>> Move;
    for(int b = 0; b < N; b++){
        auto[i, x] = Bpos[b];
        int j = (i + V[b])%M;
        if(x == B[i].size()-1){
            Move.push_back({-1, -1});
            B[i].pop_back();
            continue;
        }
        for(int k = x+1; k < B[i].size(); k++){
            int c = B[i][k];
            if(k == x+1){
                Move.push_back({c, j});
            }
            B[j].push_back(c);
            Bpos[B[j][B[j].size()-1]] = {j, B[j].size()-1};
        }
        score += B[i].size()-x-1 +1;
        while(B[i].size() > x){
            B[i].pop_back();
        }
        /*cout << "----" << b << "----" << endl;
        for(auto k : B){
            for(auto l : k){
                cout << l << " ";
            }
            cout << endl;
        }*/
    }
    if(chmin(BestScore, score)) BestV = Move;
}

void output(){
    for(int i = 0; i < N; i++){
        auto[x, y] = BestV[i];
        if(y != -1) cout << x+1 << " " << y+1 << endl;
        cout << i+1 << " " << 0 << endl;
    }
    //cout << BestScore << endl;
}

int main(){
    input();
    timeStart = calcTime();
    timeLimit = 1990;
    //timeLimit *= 18;
    srand(time(NULL));
    //cout << "A" << endl;
    calc_greed(2001002003);
    //while(calcTime() < timeStart + timeLimit) calc_greed(rand()%3+2);
    output();
    return 0;
}

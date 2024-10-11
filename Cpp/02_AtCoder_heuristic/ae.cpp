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
vector<pair<int,int>> V;
vector<pair<int,int>> temp_move;
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

int prev_score = 1001002003;
int calc_score(vector<pair<int,int>> &v){
    temp_move.clear();
    int score = 0;
    auto B = Binput;

    vector<pair<int,int>> Bpos(N);
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N/M; j++){
            Bpos[B[i][j]] = {i, j};
        }
    }

    for(auto[b, j] : v){
        auto[i, x] = Bpos[b];
        if(j == 0){
            if(B[i].size() > x+1){
                temp_move.push_back({B[i][x+1], })
            }
        }
    }
}

void calc(){
    V.clear();
    V.resize(N);
    for(int i = 0; i < N; i++){
        V[i] = {i, 0};
    }
    while(calcTime() < timeStart + timeLimit){
        auto Vnext = V;
        int x, y, z;
        x = rand()%Vnext.size();
        int ymin;
        for(int i = x; i < Vnext.size(); i++){
            auto[j, k] = Vnext[i];
            if(k == 0){
                ymin = j;
                break;
            }
        }
        y = rand()%(N-ymin)+ymin;
        z = rand()%M;
        Vnext.push_back({0,0});
        for(int i = Vnext.size()-1; i > x; i--){
            Vnext[i] = Vnext[i-1];
        }
        Vnext[x] = {y, z};
        int score = calc_score(Vnext);
        if(score < prev_score) V = Vnext;
        if(chmin(BestScore, score)) BestV = temp_move;
    }
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
    calc();
    output();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

random_device seed_gen;
mt19937 engine(seed_gen());

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

vector<pair<int,int>> dir = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}};
string stone = "-ox";

struct state{

private:
    int sz;
    int turn;
    int fin;
    vector<vector<int>> board;

public:
    state(){
        sz = 15;
        turn = 0;
        fin = -1;
        board = vector(sz, vector<int>(sz, -1));
    }

    int size(){
        return sz;
    }
    int get_turn(){
        return turn;
    }
    int get_fin(){
        return fin;
    }

    bool move(int i, int j){
        if(fin != -1 || i < 0 || sz <= i || j < 0 || sz <= j || board[i][j] != -1) return false;

        board[i][j] = turn % 2;

        int u = i-4;
        int d = i+4;
        int l = j-4;
        int r = j+4;

        for(int k = 0; k < 4; k++){
            auto[dx, dy] = dir[k];
            int temp = 0;
            for(int l = -4; l <= 4; l++){
                int x = i + l * dx;
                int y = j + l * dy;
                int z;
                if(0 <= x && x < sz && 0 <= y && y < sz) z = board[x][y];
                else z = -1;

                if(z == turn % 2) temp++;
                else temp = 0;

                if(temp == 5) fin = turn % 2;

            }
        }

        turn++;
        return true;
    }

    void print(){
        cout << "turn : " << turn << endl;
        cout << "fin : " << fin << endl;
        for(int i = 0; i < sz; i++){
            for(int j = 0; j < sz; j++){
                cout << stone[board[i][j]+1];
            }
            cout << endl;
        }
        cout << endl;
    }
};

int N = 0;
vector<tuple<state,int,int>> V;
vector<vector<int>> G;

void sub_search(){
    vector<int> v = {0};
    
}

void search(){
    V.push_back({state(), 0, 0});
    G.push_back({});

    while(1){
        sub_search();
    }
}

int main(){
}

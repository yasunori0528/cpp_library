#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dir = {
    {1,0},{1,1},{0,1},{-1,1},
    {-1,0},{-1,-1},{0,-1},{1,-1}
};
vector<vector<int>> board0(17,vector<int>(17,0));

void init_board0(){
    for(int i = 0; i < 17; i++){
        board0[0][i] = 3;
        board0[16][i] = 3;
        board0[i][0] = 3;
        board0[i][16] = 3;
    }
}

struct position {
    int turn;
    vector<vector<int>> board;
    position(){
        turn = 0;
        board = board0;
    }
};

position marge(position b, int i, int j){
    auto rtn = b;
    if(rtn.board[i][j]){
        rtn.turn = -1;
    }
    else {
        rtn.board[i][j] = 1<<(rtn.turn&1);
        rtn.turn++;
    }
    return rtn;
}

bool find5(position p, int i, int j){
    if(p.board[i][j] != 1<<(p.turn^1)) return 0;
    for(int i = 0; i < 4; i++){
        int a = 0;
        {
            int dx = dir[i][0];
            int dy = dir[i][1];
            int x = i+dx;
            int y = j+dy;
            while(p.board[x][y] == 1<<(p.turn^1)){
                a++;
                x += dx;
                y += dy;
            }
        }
        {
            int dx = dir[i+4][0];
            int dy = dir[i+4][1];
            int x = i+dx;
            int y = j+dy;
            while(p.board[x][y] == 1<<(p.turn^1)){
                a++;
                x += dx;
                y += dy;
            }
        }
        if(a >= 5) return 1;
    }
    return 0;
}

int main(){
    init_board0();
}
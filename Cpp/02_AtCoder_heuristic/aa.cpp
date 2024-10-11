#include <bits/stdc++.h>
using namespace std;

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

//!時間取得
double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}
double timeStart;
double timeNow;
double timeLimit;

bool debug_input = false;
bool debug_output = false;

vector<vector<int>> dir = {{1,0}, {0,1}, {-1,0}, {0,-1}};
int N;
vector<string> H;
vector<string> V;
vector<vector<int>> D;

//マス(i, j) : D[i][j], 壁 : -2, ブロックの仕切り : -1, 何もないマスの境界 : 0 
vector<vector<int>> Room;

vector<pair<int,int>> Block;
vector<tuple<int,int,int,int>> BlockArea;
vector<vector<pair<int,int>>> BlockContact;//BlockContact[i][j] : iとjは(xi,yi,xj,yj)で隣接している
vector<vector<int>> BlockGraph;
vector<int> BlockSolution;
vector<int> BlockCnt;

vector<pair<int,int>> Square;
vector<vector<int>> SquareGraph;
vector<int> SquareSolution;
vector<int> SquareCnt;

map<int,char> mp_output;

void randInput(){
    timeStart = calcTime();
    N = rand()%21 + 20;
    int w = rand()%N + 1;
    while(1){
        H.clear();
        H.resize(N-1);
        V.clear();
        V.resize(N);
        for(int l = 0; l < w; l++){
            int d = rand()%4;
            int i = rand()%N;
            int j = rand()%(N-1);
            int k = rand()%(N/2-2)+3;
            if(d%2) swap(i, j);
        }
    }
}

void input(){
    cin >> N;
    timeStart = calcTime();
    H.resize(N-1);
    V.resize(N);
    D.resize(N, vector<int>(N));

    for(auto &i : H) cin >> i;
    
    for(auto &i : V) cin >> i;
    
    for(auto &i : D) for(auto &j : i) cin >> j;
}

void separate_room(){
    Room.resize(2*N+1, vector<int>(2*N+1, 0));

    //盤の四方
    for(int i = 0; i < 2*N+1; i++){
        Room[i][0] = -2;
        Room[i][2*N] = -2;
        Room[0][i] = -2;
        Room[2*N][i] = -2;
    }

    //D
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Room[2*i+1][2*j+1] = D[i][j];
        }
    }

    //H
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N; j++){
            //(i, j) と (i+1, j) の間
            if(H[i][j] == '0') continue;
            Room[2*i+2][2*j+0] = -2;
            Room[2*i+2][2*j+1] = -2;
            Room[2*i+2][2*j+2] = -2;
        }
    }

    //V
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N-1; j++){
            //(i, j) と (i, j+1) の間
            if(V[i][j] == '0') continue;
            Room[2*i+0][2*j+2] = -2;
            Room[2*i+1][2*j+2] = -2;
            Room[2*i+2][2*j+2] = -2;
        }
    }

    for(int i = 0; i < 2*N+1; i += 2){
        for(int j = 2; j < 2*N+1; j++){
            if(Room[i][j] != 0) continue;
            if(Room[i][j-2] >= 0) continue;
            if(Room[i][j-1] >= 0) continue;
            if(Room[i][j-2] == -1 && Room[i][j-1] == -2) continue;
            Room[i][j] = -1;
        }
        for(int j = 2*N-2; j >= 0; j--){
            if(Room[i][j] != 0) continue;
            if(Room[i][j+2] >= 0) continue;
            if(Room[i][j+1] >= 0) continue;
            if(Room[i][j+2] == -1 && Room[i][j+1] == -2) continue;
            Room[i][j] = -1;
        }
    }

    for(int j = 0; j < 2*N+1; j += 2){
        for(int i = 2; i < 2*N+1; i++){
            if(Room[i][j] != 0) continue;
            if(Room[i-2][j] >= 0) continue;
            if(Room[i-1][j] >= 0) continue;
            if(Room[i-2][j] == -1 && Room[i-1][j] == -2) continue;
            Room[i][j] = -1;
        }
        for(int i = 2*N-2; i >= 0; i--){
            if(Room[i][j] != 0) continue;
            if(Room[i+2][j] >= 0) continue;
            if(Room[i+1][j] >= 0) continue;
            if(Room[i+2][j] == -1 && Room[i+1][j] == -2) continue;
            Room[i][j] = -1;
        }
    }

    if(debug_output){
        cout << "Room" << endl;
        for(int i = 0; i < 2*N+1; i++){
            for(int j = 0; j < 2*N+1; j++){
                int x = Room[i][j];
                if(x > 0) cout << "o";
                else if(x == 0) cout << ".";
                else if(x == -1) cout << "x";
                else if(x == -2) cout << "#";
            }
            cout << endl;
        }
        cout << endl;
    }


}

void calc_block(){
    Block.clear();
    BlockArea.clear();
    BlockContact.clear();
    BlockGraph.clear();

    vector<vector<int>> B(2*N+1, vector<int>(2*N+1, -1));
    int temp = 0;
    for(int i = 0; i < 2*N+1; i++){
        for(int j = 0; j < 2*N+1; j++){
            if(Room[i][j] < 0) B[i][j] = Room[i][j];
            else if(B[i-1][j] >= 0) B[i][j] = B[i-1][j];
            else if(B[i][j-1] >= 0) B[i][j] = B[i][j-1];
            else {
                B[i][j] = temp;
                temp++;
            }
        }
    }

    if(debug_output){
        cout << "B" << endl;
        for(int i = 0; i < 2*N+1; i++){
            for(int j = 0; j < 2*N+1; j++){
                if(0 <= B[i][j] && B[i][j] < 10) cout << 0;
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    Block.resize(temp);
    BlockArea.resize(temp, make_tuple(100,-1,100,-1));
    //cout << "calc_block_area" << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            auto &[dirty, size] = Block[B[2*i+1][2*j+1]];
            dirty += D[i][j];
            size ++;

            auto &[u, d, l, r] = BlockArea[B[2*i+1][2*j+1]];
            chmin(u, i);
            chmax(d, i);
            chmin(l, j);
            chmax(r, j);
            //cout << B[2*i+1][2*j+1] << " ";
        }
        //cout << endl;
    }
    //cout << endl;

    if(debug_output){
        cout << "Block" << endl;
        for(auto &[dirty, size] : Block){
            cout << dirty << " " << size << endl;
        }
        cout << endl;

        cout << "BlockArea" << endl;
        for(auto &[u, d, l, r] : BlockArea){
            cout << u << " " << d << " " << l << " " << r << endl;
        }
        cout << endl;
    }

    vector<set<int>> BlockGraphSet(temp);
    BlockContact.resize(temp, vector<pair<int,int>> (temp, make_pair(-1,-1)));

    //cout << "calc_BlockArea" << endl;
    for(int i = 0; i < temp; i++){
        auto[u, d, l, r] = BlockArea[i];
        //cout << i << " " << d << " " << r << endl;
        BlockContact[i][i] = make_pair(d*N+r, d*N+r);
    }
    //cout << endl;
    for(int i = 0; i < 2*N+1; i++){
        for(int j = 0; j < 2*N+1; j++){
            if(B[i][j] != -1) continue;
            int u = B[i-1][j];
            int d = B[i+1][j];
            int l = B[i][j-1];
            int r = B[i][j+1];
            if(u >= 0 && d >= 0 && u != d){
                BlockGraphSet[u].insert(d);
                BlockGraphSet[d].insert(u);
                int uu = (((i-1)-1)/2) * N + ((j-1)/2);
                int dd = (((i+1)-1)/2) * N + ((j-1)/2);
                BlockContact[u][d] = make_pair(uu, dd);
                BlockContact[d][u] = make_pair(dd, uu);
            }
            if(l >= 0 && r >= 0 && l != r){
                BlockGraphSet[l].insert(r);
                BlockGraphSet[r].insert(l);
                int ll = ((i-1)/2) * N + (((j-1)-1)/2);
                int rr = ((i-1)/2) * N + (((j+1)-1)/2);
                BlockContact[l][r] = make_pair(ll, rr);
                BlockContact[r][l] = make_pair(rr, ll);
            }
        }
    }

    if(debug_output){
        cout << "BlockContact" << endl;
        for(int i = 0; i < temp; i++){
            for(int j = 0; j < temp; j++){
                auto [x, y] = BlockContact[i][j];
                if(x != -1){
                    cout << x/N << " " << x%N << " " << y/N << " " << y%N << endl;
                }
            }
        }
        cout << endl;
    }

    BlockGraph.resize(temp);
    for(int i = 0; i < temp; i++){
        for(int j : BlockGraphSet[i]){
            BlockGraph[i].push_back(j);
        }
    }

    if(debug_output){
        cout << "BlockGraph" << endl;
        for(int i = 0; i < temp; i++){
            cout << i << ":";
            for(int j : BlockGraph[i]){
                cout << " " << j;
            }
            cout << endl;
        }
        cout << endl;
    }
}

void calc_block_first_solution_sub(int v, int p){
    //cout << v << endl;
    BlockSolution.push_back(v);
    BlockCnt[v]++;
    for(int i : BlockGraph[v]){
        if(i == p) continue;
        if(BlockCnt[i] > 0) continue;
        calc_block_first_solution_sub(i, v);
        BlockSolution.push_back(v);
        BlockCnt[v]++;
        //cout << v << endl;
    }
    BlockSolution.push_back(v);
    BlockCnt[v]++;
}

void calc_block_first_solution(){
    BlockCnt.clear();
    BlockSolution.clear();

    BlockCnt.resize(BlockGraph.size(), 0);
    calc_block_first_solution_sub(0, -1);

    if(debug_output){
        cout << "BlockFirstSolution" << endl;
        for(int i : BlockSolution){
            cout << i << " ";
        }
        cout << endl;
        cout << endl;
    }
}

void calc_square(){
    Square.clear();
    SquareGraph.clear();

    Square.resize(N*N);
    SquareGraph.resize(N*N);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Square[i*N+j] = {D[i][j], 1};
        }
    }

    if(debug_output){
        cout << "Square" << endl;
        for(auto &[dirty, size] : Square){
            cout << dirty << " " << size << endl;
        }
        cout << endl;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int v = i*N+j;
            if(i < N-1){
                int u = (i+1)*N+j;
                if(Room[2*i+2][2*j+1] != -2){
                    SquareGraph[v].push_back(u);
                    SquareGraph[u].push_back(v);
                }
            }
            if(j < N-1){
                int u = i*N+(j+1);
                if(Room[2*i+1][2*j+2] != -2){
                    SquareGraph[v].push_back(u);
                    SquareGraph[u].push_back(v);
                }
            }
        }
    }

    if(debug_output){
        cout << "SquareGraph" << endl;
        for(int i = 0; i < N*N; i++){
            cout << i << ":";
            for(int j : SquareGraph[i]){
                cout << " " << j;
            }
            cout << endl;
        }
        cout << endl;
    }
}

void calc_square_first_solution(){
    SquareSolution.clear();
    SquareCnt.clear();

    SquareCnt.resize(N*N, 0);
    int x_in = 0;
    int y_in = 0;
    for(int k = 0; k < BlockSolution.size(); k++){
        auto [u, d, l, r] = BlockArea[BlockSolution[k]];
        int x_out = 0;
        int y_out = 0;
        int x_in_next_block, y_in_next_block;

        if(k < BlockSolution.size()-1){
            auto[z_out, z_in] = BlockContact[BlockSolution[k]][BlockSolution[k+1]];
            if(debug_output){
                cout << "Block" << BlockSolution[k] << " " << BlockSolution[k+1] << endl;
            }
            x_out = z_out/N;
            y_out = z_out%N;
            x_in_next_block = z_in/N;
            y_in_next_block = z_in%N;
        }

        if(debug_output) cout << x_in << " " << y_in << "->" << "[" << u << ", " << d << "]*[" << l << ", " << r << "]" << "->" << x_out << " " << y_out << endl;
        if(debug_output) cout << "(x_in, y_in) -> (u, y_in)" << endl;
        for(int i = x_in; i > u; i--){
            SquareSolution.push_back(i*N+y_in);
            SquareCnt[i*N+y_in]++;
            if(debug_output) cout << i << " " << y_in << endl;
        }
        if(debug_output) cout << "(u, y_in) -> (u, l)" << endl;
        for(int j = y_in; j > l; j--){
            SquareSolution.push_back(u*N+j);
            SquareCnt[u*N+j]++;
            if(debug_output) cout << u << " " << j << endl;
        }
        if(debug_output) cout << "(u, l) -> (d, r)" << endl;
        for(int i = u; i <= d; i++){
            if((i-u)%2 == 0){
                for(int j = l; j <= r; j++){
                    SquareSolution.push_back(i*N+j);
                    SquareCnt[i*N+j]++;
                    if(debug_output) cout << i << " " << j << endl;
                }
            }
            else{
                for(int j = r; j >= l; j--){
                    SquareSolution.push_back(i*N+j);
                    SquareCnt[i*N+j]++;
                    if(debug_output) cout << i << " " << j << endl;
                }
            }
        }
        //(d, l) -> (d, r)
        if((d-u)%2 == 1){
            for(int j = l; j <= r; j++){
                SquareSolution.push_back(d*N+j);
                SquareCnt[d*N+j]++;
                if(debug_output) cout << d << " " << j << endl;
            }
        }

        if(debug_output) cout << "(d, r) -> (x_out, r)" << endl;
        for(int i = d-1; i >= x_out; i--){
            SquareSolution.push_back(i*N+r);
            SquareCnt[i*N+r]++;
            if(debug_output) cout << i << " " << r << endl;
        }
        if(debug_output) cout << "(x_out, r) -> (x_out, y_out)" << endl;
        for(int j = r-1; j >= y_out; j--){
            SquareSolution.push_back(x_out*N+j);
            SquareCnt[x_out*N+j]++;
            if(debug_output) cout << x_out << " " << j << endl;
        }
        x_in = x_in_next_block;
        y_in = y_in_next_block;
    }

    if(debug_output){
        cout << "SquareSolution" << endl;
        for(int i : SquareSolution){
            cout << i/N << " " << i%N << endl;
        }
        cout << endl;
    }
}

void annealing(vector<pair<int,int>> &B, vector<vector<int>> &G, vector<int> &S){
    ;
}

void calc(){
    separate_room();
    calc_block();
    calc_block_first_solution();
    //annealing(Block, BlockGraph, BlockSolution);
    calc_square();
    calc_square_first_solution();
    //annealing(Square, SquareGraph, SquareSolution);
}

void output(){
    mp_output[-N] = 'U';
    mp_output[N] = 'D';
    mp_output[-1] = 'L';
    mp_output[1] = 'R';
    string s;
    for(int i = 0; i < SquareSolution.size()-1; i++){
        int z1 = SquareSolution[i];
        int z2 = SquareSolution[i+1];
        s.push_back(mp_output[z2-z1]);
    }
    cout << s << endl;
}

int main(){
    srand(time(NULL));
    debug_input = false;
    debug_output = false;
    timeLimit = 1990;
    timeLimit *= 18;

    if(debug_input){
        for(int i = 0; i < 100; i++){
            randInput();
            calc();
            output();
        }
    }
    else{
        input();
        calc();
        output();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct matrix{
    int row;
    int column;
    vector<vector<T>> v;
    matrix(){
        ;
    }
    matrix(int r, int c){
        row = r;
        column = c;
        v = vector<vector<T>>(r, vector<T>(c, 0));
    }

    matrix<T> operator*(matrix<T> A){
        matrix<T> rtn(row, A.column);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < A.column; j++){
                for(int k = 0; k < column; k++){
                    rtn.v[i][j] += v[i][k]*A.v[k][j];
                }
            }
        }
        return rtn;
    }

    matrix<T> pow(int64_t n){
        matrix<T> rtn(row, column);
        if(n == 0){
            for(int i = 0; i < row; i++){
                rtn.v[i][i] = 1;
            }
            return rtn;
        }
        if(n == 1){
            rtn.v = v;
            return rtn;
        }
        rtn = pow(n/2);
        rtn = rtn*rtn*pow(n%2);
        return rtn;
    }

    void print(){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                cout << v[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }
};

int main(){
    matrix<int> A(2,2);
    A.v = {{1,1},{0,1}};
    A = A.pow(10000000);
    A.print();
}
#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

vector<string> no_duplication_1(int l, int r){
    vector<string> rtn;
    for(int d = l; d < r; d++){
        vector<int> loop(9, 0);
        for(int i = 9 - d; i < 9; i++) loop[i] = 1;
        do{
            string s;
            for(int i = 8; i >= 0; i--) if(loop[i]) s.push_back(alphabet[i + 1]);
            rtn.push_back(s);
        }while(next_permutation(loop.begin(), loop.end()));
    }
    return rtn;
}

vector<string> allow_duplication_2(int l, int r){
    vector<string> rtn;
    for(int d = l; d < r; d++){
        vector<int> loop(d, 10);
        bool b = true;
        while(b){
            string s;
            for(int i = 0; i < d; i++) s.push_back(alphabet[loop[i]]);
            rtn.push_back(s);
            //cout << s << endl;

            b = false;
            for(int i = d - 1; i >= 0; i--){
                if(loop[i] == 13) continue;
                loop[i]++;
                for(int j = d - 1; j > i; j--) loop[j] = 10;
                b = true;
                break;
            }
        }
    }
    return rtn;
}

int main(){
    auto v = no_duplication_1(2, 5);
    auto w = allow_duplication_2(2, 5);
    vector<string> x = {"1", "J"};

    int a = v.size();
    int b = w.size();
    int c = x.size();
    cout << a << " " << b << " " << c << endl;

    vector<tuple<int64_t,int,int,int>> D;
    for(int i = 1; i <= a; i++){
        for(int j = 1; j <= b; j++){
            for(int k = 1; k <= c; k++){
                D.push_back({int64_t(i)*j*k, i, j, k});
            }
        }
    }
    sort(D.begin(), D.end());

    
}

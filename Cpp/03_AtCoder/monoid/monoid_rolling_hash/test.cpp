#include <bits/stdc++.h>
using namespace std;

#include "../../rand/rand.cpp"
#include "monoid_rolling_hash.cpp"

int main(){
    for(int i = 0; i < 1001002003; i++){
        if((i & 0x3FF) == 0) cout << "i : " << i << endl;
        init_rh_base(1010);
        int N = engine() % 100 + 1;
        string S = rnd<string>(N);
        set<uint64_t> A;
        //cout << N << endl;
        //cout << S << endl;
        for(int j = 0; j < 10000; j++){
            vector<monoid_rolling_hash> v(N);
            for(int k = 0; k < N; k++){
                v[k] = monoid_rolling_hash(S[k]);
            }
            //for(auto k : v) cout << k.val << " ";
            //cout << endl;
            for(int k = N - 1; k >= 1; k--){
                int x = engine() % k;
                //cout << "C " << x << endl;
                v[x] = v[x] * v[x + 1];
                //cout << "A" << endl;
                for(int h = x + 1; h < k; h++) v[h] = v[h + 1];
                //cout << "B" << endl;
                v.pop_back();
            }
            A.insert(v[0].val);
        }
        if(A.size() > 1){
            cout << S << endl;
            for(auto j : A) cout << j << " ";
            cout << endl;
        }
    }
}
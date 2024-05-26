#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "pqk_lib/pqk_all.cpp"

int main(){
    for(int d = 1; d < 7; d++){
        vector<int> loop(d, 0);
        bool b = true;
        while(b){
            string s;
            for(int i = 0; i < d; i++) s.push_back(alphabet[10 + loop[i]]);
            s.push_back('1');
            if(miller_rabin(str_to_int(s))) cout << s << endl;
            b = false;
            for(int i = d - 1; i >= 0; i--){
                if(loop[i] < 3){
                    loop[i]++;
                    for(int j = i + 1; j < d; j++) loop[j] = 0;
                    b = true;
                    break;
                }
            }
        }
    }
}
//XXXA

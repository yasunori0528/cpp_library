#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    for(int looop = 0; looop < 100000000; looop++){
        vector<string> vec_s(3);
        for(int i = 0; i < 3; i++){
            vector<char> vec_c(10);
            char k = 'a';
            for(char &c : vec_c){
                c = k;
                k++;
            }
            for(int j = 0; j < 10; j++){
                int rd = rand()%(10-j);
                int cnt = 0;
                for(char & c : vec_c){
                    if(c != 'x') {
                        if(cnt == rd){
                            vec_s[i].push_back(c);
                            c = 'x';
                            break;
                        }
                        else cnt++;
                    }
                }
            }
        }
        string s1, s2, s3;
        s1 = vec_s[0];
        s2 = vec_s[1];
        s3 = vec_s[2];
        //cout << s1 << "_" << s2 << "_" << s3 << "_";
        string S = s1+s2+s3;
        map<char,char> g;
        for(char c : S){
            if(!g.count(c)) g[c] = 'x';
        }
        int n = g.size();
        if(n > 10) ;//cout << "UNSOLVABLE" << endl;
        else{
            vector<char> vec(10);
            for(int i = 0; i < 10; i++) vec[i] = '0'+i;
            if(n < 10) for(int i = 0; i < 10-n; i++) g['A'+i] = 'x';
            int64_t ans1 = -1;
            int64_t ans2 = -1;
            int64_t ans3 = -1;
            do{
                int i = 0;
                for(auto & p : g){
                    p.second = vec[i];
                    i++;
                }

                string n1_str = s1;
                string n2_str = s2;
                string n3_str = s3;
                for(char & c : n1_str) c = g[c];
                for(char & c : n2_str) c = g[c];
                for(char & c : n3_str) c = g[c];
                if(n1_str[0] != '0' && n2_str[0] != '0' && n3_str[0] != '0'){
                    int64_t n1 = stoll(n1_str);
                    int64_t n2 = stoll(n2_str);
                    int64_t n3 = stoll(n3_str);
                    if(n1+n2 == n3) {
                        //cout << n1 << "_" << n2 << "_" << n3 << "\n";
                        ans1 = n1;
                        ans2 = n2;
                        ans3 = n3;
                    }
                }
            }while(next_permutation(vec.begin(),vec.end()));
            if(ans1 == -1) ;//cout << "UNSOLVABLE" << endl;
            else {
                cout << s1 << "_" << s2 << "_" << s3 << "_" << ans1 << "_" << ans2 << "_" << ans3 << "\n";
            }
        }
    }
}
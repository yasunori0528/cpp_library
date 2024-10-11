#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin >> s;
    for(int i = 0; i < 26; i++){
        string t = s;
        for(char &c : t){
            if(c == '_') continue;
            if(c+i <= 'Z') c += i;
            else c += i-26;
        }
        cout << t << endl;
    }
}
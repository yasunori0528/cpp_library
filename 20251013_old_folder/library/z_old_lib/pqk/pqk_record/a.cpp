#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

struct action {
    char draw;
    string play_unassign;
    string play_assign;
    string penalty;

    action(string s) {
        if(s[0] == '(') {
            s = s.substr(1);
            s.pop_back();
            draw = '_';
            penalty = s;
            return;
        }
        if(s[0] == 'D') {
            draw = s[2];
            s = s.substr(4);
        }
        if(s[0] == '%') {
            return;
        }
        for(size_t i = 0; i < s.size(); i++) {
            if(s[i] == '[' || s[i] == '#') {
                s = s.substr(0, i);
                break;
            }
        }
        for(size_t i = 0; i < s.size(); i++) {
            if(s[i] == ',') {
                penalty = s.substr(i+3);
                penalty.pop_back();
                s = s.substr(0, i);
                if(penalty.size() == 0) penalty = "_";
            }
        }
        vector<size_t> part;
        for(size_t i = 0; i < s.size(); i++) {
            if(s[i] == '|') part.push_back(i);
        }
        part.push_back(s.size());

        play_unassign = s.substr(0, part[0]);
        play_assign = play_unassign;
        {
            size_t i = 0;
            size_t j = 1;
            while(i < s.size() && j < part.size()) {
                if(play_assign[i] == 'X') {
                    play_assign[i] = s[part[j]-1];
                    i++;
                    j++;
                }
                else {
                    i++;
                }
            }
        }
    }

    void print() {
        cout << draw << "," << play_unassign << "," << play_assign << "," << penalty;
    }
};

int main() {
    int n = 1000;
    vector<string> V(n);
    for(auto &s : V) {
        cin >> s;
        action a(s);
        //cout << s << " -> ";
        a.print();
        cout << endl;
    }
}
//数譜の変換

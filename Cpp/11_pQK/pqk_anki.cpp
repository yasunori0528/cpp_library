#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

vector<char> card = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
vector<string> command = {"anki", "input", "update", "end"};

map<char,int> chartoint;
void calc_chartoint(){
    for(int i = 0; i < 10; i++){
        chartoint['0'+i] = i;
    }
    chartoint['T'] = 10;
    chartoint['J'] = 11;
    chartoint['Q'] = 12;
    chartoint['K'] = 13;
}
Bint strtoint(string s){
    int n = s.size();
    if(n == 1){
        return chartoint[s[0]];
    }
    Bint rtn = strtoint(s.substr(0,n-1));
    char i = chartoint[s[n-1]];
    if(i < 10) rtn = 10*rtn+i;
    else rtn = 100*rtn+i;
    return rtn;
}

bool num_or_com(string s){
    bool rtn = true;
    int n = s.size();
    for(int i = 0; i < n; i++){
        char c = s[i];
        bool b = false;
        if(i == 0 && c == '-') b = true;
        for(char d : card){
            if(c == d) {
                b = true;
                break;
            }
        }
        if(!b){
            rtn = false;
            break;
        }
    }
    return rtn;
}

vector<int> card_pri = {9,8,7,6,5,4,3,2,1,0,13,12,11,10};
string sort_91KT(string s){
    vector<pair<int,char>> vp;
    for(char c : s){
        vp.push_back(make_pair(card_pri[chartoint[c]],c));
    }
    sort(vp.begin(),vp.end());
    string rtn;
    for(auto vpi : vp){
        rtn.push_back(vpi.second);
    }
    return rtn;
}

void shuffle_queue(queue<pair<string,string>> &q){
    vector<tuple<int,string,string>> v;
    while(q.size() > 0){
        pair<string,string> qi = q.front();
        q.pop();
        string s, t;
        tie(s,t) = qi;
        v.push_back(make_tuple(rand(),s,t));
    }
    sort(v.begin(),v.end());
    for(auto vi : v){
        string s, t;
        tie(ignore,s,t) = vi;
        q.push(make_pair(s,t));
    }
}

int main(){
    srand(time(NULL));
    calc_chartoint();
    int n; cin >> n;
    vector<int> cnt(n);
    for(int i = 0; i < n; i++){
        cin >> cnt[i];
    }
    vector<queue<pair<string,string>>> plist(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < cnt[i]; j++){
            string s, t;
            cin >> s >> t;
            plist[i].push(make_pair(s,t));
        }
    }
    for(int i = 0; i < 45; i++){
        cout << endl;
    }
    cout << "input_command" << endl;
    string com;
    cin >> com;
    int prei = -1;
    while(true){
        if(com == "anki"){
            //cout << n << endl;
            int i = max(prei,0);
            if(plist[i].size() == 0){
                cout << "end:plist[" << i << "]" << endl;
                for(int j = 0; j < n; j++){
                    if(plist[j].size() == 0){
                        //cout << "skip:" << i << endl;
                        continue;
                    }
                    else{
                        i = j;
                        break;
                    }
                }
                cout << "start:plist[" << i << "]" << endl;
            }
            if(prei < i){
                shuffle_queue(plist[i]);
            }
            string s, t;
            tie(s,t) = plist[i].front();
            cout << "?" << s << endl;
            string u;
            bool input_bl = false;
            while(!input_bl){
                cout << "input_answer_or_command" << endl;
                cin >> u;
                if(num_or_com(u)){
                    plist[i].pop();
                    if((u == t) || (u[0] != '-' && t[0] != '-' && strtoint(u) == strtoint(t))){
                        cout << "correct" << endl;
                        if(i == n-1){
                            queue<pair<string,string>> qn;
                            plist.push_back(qn);
                            n++;
                        }
                        plist[i+1].push(make_pair(s,t));
                    }
                    else{
                        cout << "wrong" << endl;
                        cout << t << endl;
                        plist[0].push(make_pair(s,t));
                    }
                    input_bl = true;
                }
                else{
                    for(string comi : command){
                        if(comi == u){
                            com = u;
                            input_bl = true;
                            break;
                        }
                    }
                }
            }
            prei = i;
        }
        else if(com == "input"){
            cout << "input_hand_or_command" << endl;
            string s;
            cin >> s;
            bool com_b = false;
            for(string comi : command){
                if(comi == s){
                    com = s;
                    com_b = true;
                    break;
                }
            }
            if(!com_b){
                string t;
                if(s[0] == '-'){
                    s = s.substr(1);
                    t = sort_91KT(s);
                    s = "-1";
                }
                else{
                    t = sort_91KT(s);
                }
                plist[0].push(make_pair(t,s));
            }            
        }
        else if(com == "end"){
            cout << plist.size() << endl;
            bool bk = false;
            for(auto plisti : plist){
                if(bk) cout << " ";
                else bk = true;
                cout << plisti.size();
            }
            cout << endl;
            for(auto plisti : plist){
                bool bki = false;
                while(plisti.size() > 0){
                    if(bki) cout << " ";
                    else bki = true;
                    pair<string,string> pr = plisti.front();
                    plisti.pop();
                    string s, t;
                    tie(s,t) = pr;
                    cout << s << " " << t;
                }
                cout << endl;
            }
            break;
        }
    }
}
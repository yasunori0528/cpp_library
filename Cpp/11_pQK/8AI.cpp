#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

map<char,int> operator+(map<char,int> x, map<char,int> y){
    map<char,int> z;
    for(auto p : x){
        char c;
        int i;
        tie(c,i) = p;
        z[c] += i;
    }
    for(auto p : y){
        char c;
        int i;
        tie(c,i) = p;
        z[c] += i;
    }
    return z;
}
map<char,int> operator-(map<char,int> x, map<char,int> y){
    map<char,int> z;
    for(auto p : x){
        char c;
        int i;
        tie(c,i) = p;
        z[c] += i;
    }
    for(auto p : y){
        char c;
        int i;
        tie(c,i) = p;
        z[c] -= i;
    }
    for(auto p : z){
        char c;
        int i;
        tie(c,i) = p;
        if(i < 0) z[c] = 0;
    }
    return z;
}

queue<char> operator+(queue<char> x, queue<char> y){
    while(y.size()){
        x.push(y.front());
        y.pop();
    }
    return x;
}

void clear(queue<char> &q){
    queue<char> empty;
    swap(q,empty);
}

int map_size(map<char,int> x){
    int rtn = 0;
    for(auto ci : x){
        rtn += ci.second;
    }
    return rtn;
}

//x in y
bool include_map(map<char,int> x, map<char,int> y){
    if(map_size(x-y) == 0) return true;
    return false;
}

//n^a%p
Bint powmod(Bint n, Bint a, Bint p){
    if(a == 0) return 1;
    n %= p;
    Bint b = a/2;
    Bint c = a%2;
    Bint nb = powmod(n, b, p);
    Bint rtn = 1;
    if(c) rtn = n;
    rtn = (rtn*nb*nb)%p;
    return rtn;
}

bool MRpt(Bint n){
    //cout << "MRpt_" << n << endl;
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n%2 == 0) return false;

    int k = 100;

    Bint s = n-1;
    int e = 0;
    //n-1 = s*2^e
    while(s%2 == 0){
        s /= 2;
        e++;
    }
    //cout << n << "=" << s << "*2^" << e << endl;

    for(int i = 0; i < k; i++){
        Bint a = rand()%(n-3)+2;
        //cout << "ai : " << a << endl;
        Bint as = powmod(a,s,n);
        bool c = false;
        if(as == 1 || as == n-1) c = true;
        Bint asj = as;
        for(int j = 1; j < e; j++){
            asj = asj*asj%n;
            if(asj == n-1) c = true;
        }
        if(!c) return false;
    }
    return true;
}

vector<char> card;
void calc_card(){
    for(int i = 0; i < 10; i++){
        card.push_back('0'+i);
    }
    card.push_back('T');
    card.push_back('J');
    card.push_back('Q');
    card.push_back('K');
    card.push_back('X');
}
map<char,int> char_to_int;
void calc_char_to_int(){
    for(int i = 0; i <= 14; i++){
        char_to_int[card[i]] = i;
    }
}
Bint str_to_int(string s){
    if(s.size() == 0){
        return 0;
    }
    if(s.size() == 1){
        return char_to_int[s[0]];
    }
    char c = s[s.size()-1];
    s.pop_back();
    int i = char_to_int[c];
    Bint n = str_to_int(s);
    if(i < 10) n = 10*n+i;
    else n = 100*n+i;
    return n;
}
int Bint_to_int(Bint n){
    int rtn = 0;
    for(int i = 30; i >= 0; i--){
        if(n%((int)pow(2,i+1))/((int)pow(2,i))){
            rtn = 2*rtn+1;
        }
        else{
            rtn = 2*rtn;
        }
    }
    return rtn;
}
string to_string(Bint n){
    if(n < 10) return to_string(Bint_to_int(n));
    string s;
    int i = Bint_to_int(n%10);
    //cout << "to_string_" << i << endl;
    s = to_string(n/10)+card[i];
    return s;
}
Bint pow(Bint n, Bint a, int d){
    //cout << n << "," << a << "," << d << endl;
    string s = to_string(n);
    //cout << "s : " << s << endl;
    Bint n_d = s.size()*a;
    //cout << "n_d : " << n_d << endl;
    if(n_d > d) return -1;
    Bint rtn = 1;
    for(int i = 0; i < a; i++){
        rtn *= n;
    }
    return rtn;
}

map<char,int> str_to_map(string s){
    map<char,int> x;
    for(char c : s){
        for(char cd : card){
            if(c == cd){
                x[c]++;
            }
        }
    }
    return x;
}
queue<char> str_to_queue(string s){
    queue<char> q;
    for(char c : s){
        for(char cd : card){
            if(c == cd){
                q.push(c);
            }
        }
    }
    return q;
}
vector<map<char,int>> hand;
queue<char> deck;
queue<char> field;
string field_top;
bool rr = true;
int num_of_deck, num_of_pl, num_of_hand;
vector<tuple<string,vector<char>,bool>> play_log;

int hand_size(int pl){
    int rtn = map_size(hand[pl]);
    return rtn;
}

void shuffle(int d){
    vector<char> dk;
    for(int i = 0; i < 4*d; i++){
        for(char c : card){
            if((c == 'X' && i%2) || c == '0'){
                continue;
            }
            dk.push_back(c);
        }
    }
    for(int i = 0; i < 54*d; i++){
        int j = rand()%(54*d-i);
        deck.push(dk[j]);
        for(int k = j; k < 54*d-i-1; k++){
            dk[k] = dk[k+1];
        }
        dk.pop_back();
    }
}

void draw(int pl){
    if(deck.size()){
        char c = deck.front();
        deck.pop();
        hand[pl][c]++;
    }
}

void draw(int pl, char &d){
    if(deck.size()){
        char c = deck.front();
        d = c;
        deck.pop();
        hand[pl][c]++;
    }
}
    
void output_hand(int pl){
    map<char,int> hand_pl = hand[pl];
    for(char c : card){
        int cn = hand_pl[c];
        for(int i = 0; i < cn; i++){
            cout << c;
        }
    }
    cout << endl;
}

void output_deck(){
    auto d = deck;
    while(d.size()){
        char c = d.front();
        d.pop();
        cout << c;
    }
    cout << endl;
}

bool playable(string s, vector<char> x_c, int pl){
    if(s == "%") return true;
    map<char,int> s_map = str_to_map(s);
    if(!include_map(s_map,hand[pl])){
        //cout << "A" << endl;
        return false;
    }

    int i_x = 0;
    for(int i = 0; i < s.size(); i++){
        if(x_c.size() <= i_x) break;
        char c = s[i];
        if(c == 'X'){
            s[i] = x_c[i_x];
            i_x++;
        }
    }
    int i_equal = -1;
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        if(c == '=') {
            i_equal = i;
            break;
        }
    }
    if(i_equal == -1 && (s.size() != field_top.size() && field_top.size() != 0)) {
        //cout << "B" << endl;
        return false;
    }
    if(i_equal != -1 && (i_equal != field_top.size() && field_top.size() != 0)) {
        //cout << "C" << endl;
        return false;
    }
    Bint n;
    if(i_equal == -1) n = str_to_int(s);
    else n = str_to_int(s.substr(0,i_equal));
    //cout << "__" << n << endl;
    Bint field_top_int = str_to_int(field_top);
    bool cmp_b = true;
    if(i_equal > 0){
        string p_s = s.substr(i_equal);
        vector<vector<string>> p_v;
        for(char c : p_s){
            if(c == '=' || c == '*'){
                p_v.push_back(vector<string>(1,""));
            }
            else if(c == '^'){
                p_v[p_v.size()-1].push_back("");
            }
            else{
                p_v[p_v.size()-1][p_v[p_v.size()-1].size()-1].push_back(c);
            }
        }
        for(auto p_v_i : p_v){
            bool bk = false;
            for(auto p_v_ij : p_v_i){
                if(p_v_ij[0] == '0' || str_to_int(p_v_ij) < 2){
                    cmp_b = false;
                    bk = true;
                    break;
                }
            }
            if(bk) break;
        }
    }
    if(!cmp_b) {
        //cout << "D" << endl;
        return false;
    }
    if(field_top_int == 0) {
        //cout << "E" << endl;
        return true;
    }
    if(field_top_int != n && ((field_top_int < n) == rr)) {
        //cout << "F" << endl;
        return true;
    }
    return false;
}

bool bool_p_v(vector<vector<string>> p_v){
    for(auto p_vi : p_v){
        //cout << "\"" << p_vi[0] << "\"" << endl;
        Bint p_vi0 = str_to_int(p_vi[0]);
        //cout << p_vi0 << endl;
        if(!MRpt(p_vi0)) {
            return false;
        }
    }
    return true;
}

Bint calc_p_v(vector<vector<string>> p_v){
    bool b = true;
    for(auto &p_vi : p_v){
        if(p_vi.size() > 1){
            b = false;
            Bint p_vi_r = str_to_int(p_vi[p_vi.size()-1]);
            Bint p_vi_r_ = str_to_int(p_vi[p_vi.size()-2]);
            //cout << p_vi_r_ << "," << p_vi_r << endl;
            Bint p_vi_r_2 = pow(p_vi_r_,p_vi_r,num_of_deck*72);
            //cout << p_vi_r_2 << endl;
            if(p_vi_r_2 < 0) return -1;
            p_vi[p_vi.size()-2] = to_string(p_vi_r_2);
            p_vi.pop_back();
        }
    }
    if(b){
        Bint rtn = 1;
        for(auto &p_vi : p_v){
            Bint p_vi0 = str_to_int(p_vi[0]);
            if(p_vi0 < 0) return -1;
            rtn *= p_vi0;
        }
        return rtn;
    }
    return calc_p_v(p_v);
}

void play(string s, vector<char> x_c, int &pl){
    string s_ = s;
    bool b;
    if(s == "%"){
        cout << ">>>p" << pl << " : " << s << endl;
        pl = (pl+1)%num_of_pl;
        deck = deck+field;
        clear(field);
        field_top = "";
        b = true;
    }
    else{
        map<char,int> s_map = str_to_map(s);
        queue<char> s_queue = str_to_queue(s);
        queue<char> c_queue;
        queue<char> p_queue;
        int i_equal = -1;
        for(int i = 0; i < s.size(); i++){
            char c = s[i];
            if(c == '='){
                i_equal = i;
                break;
            }
        }
        if(i_equal > 0){
            c_queue = str_to_queue(s.substr(0,i_equal));
            p_queue = str_to_queue(s.substr(i_equal));
        }

        int s_map_size = map_size(s_map);
        int i_x = 0;
        for(char &c : s){
            if(x_c.size() <= i_x) break;
            if(c == 'X'){
                c = x_c[i_x];
                i_x++;
            }
        }
        if(i_equal == -1){
            //cout << s << endl;
            Bint n = str_to_int(s);
            //cout << n << endl;
            if(s == "X" || n == 57){
                cout << ">>>p" << pl << " : " << s << endl;
                hand[pl] = hand[pl]-s_map;
                deck = deck+field+s_queue;
                clear(field);
                field_top = "";
                b = true;
            }
            else if(n == 1729){
                cout << ">>>p" << pl << " : " << s << endl;
                hand[pl] = hand[pl]-s_map;
                field = field+s_queue;
                field_top = s;
                pl = (pl+1)%num_of_pl;
                rr = !rr;
                b = true;
            }
            else {
                if(MRpt(n)){
                    cout << ">>>p" << pl << " : " << s << endl;
                    hand[pl] = hand[pl]-s_map;
                    field = field+s_queue;
                    field_top = s;
                    pl = (pl+1)%num_of_pl;
                    b = true;
                }
                else{
                    for(int i = 0; i < s_map_size; i++){
                        draw(pl);
                    }
                    cout << ">>>p" << pl << " : " << s << " fail" << endl;
                    deck = deck+field;
                    clear(field);
                    field_top = "";
                    pl = (pl+1)%num_of_pl;
                    b = false;
                }
            }
        }
        else{
            string c_s = s.substr(0,i_equal);
            string p_s = s.substr(i_equal);
            vector<vector<string>> p_v;
            for(char c : p_s){
                if(c == '=' || c == '*'){
                    p_v.push_back(vector<string>(1,""));
                }
                else if(c == '^'){
                    p_v[p_v.size()-1].push_back("");
                }
                else{
                    p_v[p_v.size()-1][p_v[p_v.size()-1].size()-1].push_back(c);
                }
            }
            Bint n = str_to_int(c_s);
            /*cout << "---debug" << endl;
            for(auto p_vi : p_v){
                for(string p_vij : p_vi){
                    cout << p_vij << ",";
                }
                cout << endl;
            }
            cout << "---debug" << endl;*/
            if(bool_p_v(p_v)){
                Bint m = calc_p_v(p_v);
                //cout << "p_v" << m << endl;
                if(n == m){
                    cout << ">>>p" << pl << " : " << s << endl;
                    hand[pl] = hand[pl]-s_map;
                    deck = deck+p_queue;
                    field = field+c_queue;
                    field_top = c_s;
                    pl = (pl+1)%num_of_pl;
                    b = true;
                }
                else{
                    for(int i = 0; i < s_map_size; i++){
                        draw(pl);
                    }
                    cout << ">>>p" << pl << " : " << s << " fail" << endl;
                    deck = deck+field;
                    clear(field);
                    field_top = "";                
                    pl = (pl+1)%num_of_pl;
                    b = false;
                }
            }
            else{
                //cout << "A" << endl;
                for(int i = 0; i < s_map_size; i++){
                    draw(pl);
                }
                deck = deck+field;
                clear(field);
                field_top = "";
                pl = (pl+1)%num_of_pl;
                cout << ">>>p" << pl << " : " << s << " fail" << endl;
                b = false;
            }
        }
        if(x_c.size()) cout << ">>>(" << s_ << ")" << endl;
    }
    play_log.push_back(make_tuple(s_,x_c,b));
}

////////////////////////////////////////////////////////////////
int num_of_cpu;
set<int> cpu_turn;
int court_card(string s){
    int n = 0;
    for(char c : s){
        int i = char_to_int[c];
        if(i >= 10) n++;
    }
    return n;
}
vector<char> card_ = {'9','8','7','6','5','4','3','2','K','Q','J','1','T'};
vector<char> odd_last = {'1', 'J', 'K', '3', '7', '9'};
string max_odd(map<char,int> m){
    string rtn;
    m['K'] += m['X'];
    m['X'] = 0;
    char r;
    bool b = false;
    for(char c : odd_last){
        if(m[c]){
            r = c;
            b = true;
            break;
        }
    }
    if(!b) return "%";
    for(char c : card_){
        int mc = m[c];
        if(r == c) mc--;
        for(int i = 0; i < mc; i++){
            rtn.push_back(c);
        }
    }
    rtn.push_back(r);
    return rtn;
}
string max_odd(map<char,int> m, int n, string &s, vector<char> &x_c){
    return "";
}
void draw_cpu(int pl, char &if_draw){
    if_draw = 'y';
}
void play_cpu(int pl, string &s, vector<char> &x_c){
    int n;
    if(field_top.size()){
        n = field_top.size();
    }
    else{
        n = hand_size(pl);
    }
    max_odd(hand[pl], n, s, x_c);
}
void pqk_cpu(int pl, char &if_draw, string &s, vector<char> &x_c){
    draw_cpu(pl, if_draw);
    play_cpu(pl, s, x_c);
}
////////////////////////////////////////////////////////////////

int main(){
    srand(time(NULL));
    calc_card();
    calc_char_to_int();

    cin >> num_of_deck >> num_of_pl;

    /*cin >> num_of_hand;
    for(int i = 0; i < num_of_pl; i++){
        cin >> num_of_hand;
    }*/

    vector<int> vec_num_of_hand(num_of_pl);
    for(int i = 0; i < num_of_pl; i++){
        cin >> vec_num_of_hand[i];
    }
    
    /*cin >> num_of_cpu;
    for(int i = 0; i < num_of_cpu; i++){
        int cpu_turn_i;
        cin >> cpu_turn_i;
        cpu_turn.insert(cpu_turn_i);
    }*/

    shuffle(num_of_deck);

    hand.resize(num_of_pl);
    for(int i = 0; i < num_of_pl; i++){
        for(char c : card){
            hand[i][c] = 0;
        }
    }
    for(int i = 0; i < num_of_pl; i++){
        for(int j = 0; j < vec_num_of_hand[i]; j++){
            draw(i);
        }
    }

    //for(int i = 0; i < num_of_pl; i++) output_hand(i);
    //output_deck();

    bool game = true;
    int num_of_field = 0;
    int turn = 0;
    while(game){
        cout << "--------------------------------" << endl;
        cout << ">>>turn : player" << turn << endl;
        cout << ">>revolution : ";
        if(rr) cout << "No" << endl;
        else cout << "Yes" << endl;
        cout << ">>>deck : " << deck.size() << endl;
        cout << ">>>field : " << field_top << ", (" << field_top.size() << ")" << endl;
        cout << ">>>hand : ";
        output_hand(turn);
        int pre_turn = turn;

        char if_draw;
        string s;
        vector<char> x_c;

        if(cpu_turn.count(turn)){
            pqk_cpu(turn, if_draw, s, x_c);
        }
        else{
            cout << ">>>draw?_y_or_n" << endl;
            cin >> if_draw;
            while(if_draw != 'y' && if_draw != 'n'){
                cout << ">>>This_is_wrong_input" << endl;
                cin >> if_draw;
            }
            if(if_draw == 'y') {
                char d;
                draw(turn,d);
                cout << ">>>(d = " << d << "), ";
                output_hand(turn);
            }
            cin >> s;
            if(s != "X"){
                for(char c : s){
                    if(c == 'X'){
                        char x_ci;
                        cin >> x_ci;
                        x_c.push_back(x_ci);
                    }
                }
            }
        }
        while(!playable(s,x_c,turn)){
            cout << ">>>This_is_wrong_input" << endl;
            cin >> s;
            x_c.resize(0);
            for(char c : s){
                if(c == 'X'){
                    char x_ci;
                    cin >> x_ci;
                    x_c.push_back(x_ci);
                }
            }
        }
        play(s, x_c, turn);

        if(hand_size(pre_turn) == 0){
            cout << ">>>win : player" << pre_turn << endl;
            game = false;
        }
    }

    /*for(auto tp : play_log){
        string s;
        vector<char> x_c;
        bool b;
        tie(s,x_c,b) = tp;
        cout << s << ",";
        for(char c : x_c) cout << c << ",";
        cout << b << endl;
    }*/
}
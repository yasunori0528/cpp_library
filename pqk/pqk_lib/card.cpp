//カードの種類
//'a'~'n' は 'X' に 0 ~ 13 を代入した状態を指す.
const string alphabet = "0123456789TJQKXabcdefghijklmn";
const string deck = "111122223333444455556666777788889999TTTTJJJJQQQQKKKKXX";

int char_to_int(char c) {
    if('0' <= c && c <= '9') return c - '0';
    else if(c == 'T') return 10;
    else if(c == 'J') return 11;
    else if(c == 'Q') return 12;
    else if(c == 'K') return 13;
    else if(c == 'X') return 14;
    else if('a' <= c || c <= 'n') return c - 'a';
    else assert(false);
    return 0;
}

bool is_symbol(char c) {
    return c == '=' || c == '*' || c == '^';
}

bool is_joker(char c) {
    return c == 'X' || ('a' <= c && c <= 'n');
}

bigint str_to_int(string s) {
    if(s.size() == 0) return 0;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = min(char_to_int(c), 13);
    bigint rtn;

    int d = i < 10 ? 10 : 100;
    rtn = str_to_int(t) * d + i;
    return rtn;
}

string int_to_str(bigint x) {
    string s;
    while(x) {
        s.push_back('0' + x.get_ui() % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

//s = [0-9+*=]*
int max_num_of_face(string s) {
    int i = 0;
    int rtn = 0;
    while(i + 1 < (int)s.size()) {
        if(s[i] == '1' && '0' <= s[i + 1] && s[i + 1] <= '3') {
            rtn++;
            i += 2;
        }
        else i++;
    }
    return rtn;
}

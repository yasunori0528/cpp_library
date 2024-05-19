//カードの種類
//'a'~'n' は 'X' に 0 ~ 13 を代入した状態を指す.
const string alphabet = "0123456789TJQKXabcdefghijklmn";

int char_to_int(char c){
    if('0' <= c && c <= '9') return c - '0';
    else if(c == 'T') return 10;
    else if(c == 'J') return 11;
    else if(c == 'Q') return 12;
    else if(c == 'K') return 13;
    else if(c == 'X') return 14;
    else return c - 'a';
}

bigint str_to_int(string s){
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

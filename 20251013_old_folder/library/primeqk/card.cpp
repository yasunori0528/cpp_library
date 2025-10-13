//カードの種類
//'a'~'n' は 'X' に 0 ~ 13 を代入した状態を指す.
const string ALPHABET = "0123456789TJQKXabcdefghijklmn";
const string DECK = "111122223333444455556666777788889999TTTTJJJJQQQQKKKKXX";
const int NUM_CARD_TYPES = 15;

char int_to_char(int x) {
    assert(0 <= x && x < NUM_CARD_TYPES);
    return ALPHABET[x];
}

int char_to_int(char c) {
    if('0' <= c && c <= '9') return c - '0';
    if(c == 'T') return 10;
    if(c == 'J') return 11;
    if(c == 'Q') return 12;
    if(c == 'K') return 13;
    if(c == 'X') return 14;
    assert(false);
    return 0;
}

char assign(char &c) {
    if('a' <= c && c <= 'n') return ALPHABET[c - 'a'];
    return c;
}

char unassign(char &c) {
    if('a' <= c && c <= 'n') return 'X';
    return c;
}

bool is_symbol(char &c) {
    return c == '=' || c == '*' || c == '^';
}

bool is_joker(char &c) {
    return c == 'X' || ('a' <= c && c <= 'n');
}

string int_to_str(bigint x) {
    string s;
    while(x) {
        bigint r = x % 10;
        s.push_back('0' + bigint_to_int(r));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

bigint str_to_int(string &s) {
    bigint rtn = 0;
    for(char &c : s) {
        int x = char_to_int(assign(c));
        if(x < 10) rtn = rtn * 10 + x;
        else rtn = rtn * 100 + x;
    }
    return rtn;
}

void print_str(string &s) {
    string s_unassign = s;
    string s_assign = s;
    for(char &c : s_unassign) c = unassign(c);
    for(char &c : s_assign) c = assign(c);

    cout << s_unassign;
    if(s_assign != s_unassign) {
        cout << "(" << s_assign << ")";
    }
}

//カードの集合のhash(rolling_hashの流用)
const uint64_t rh_mod = 0x1FFFFFFFFFFFFFFF;
const uint64_t rh_mask30 = 0x3FFFFFFF;
const uint64_t rh_mask31 = 0x7FFFFFFF;
const uint64_t rh_mask61 = rh_mod;
uint64_t rh_base;
uint64_t rh_mul(uint64_t a, uint64_t b){
    uint64_t au = a >> 31;
    uint64_t ad = a & rh_mask31;
    uint64_t bu = b >> 31;
    uint64_t bd = b & rh_mask31;
    uint64_t mid = ad * bu + au * bd;
    uint64_t midu = mid >> 30;
    uint64_t midd = mid & rh_mask30;

    uint64_t x = au * bu * 2 + midu + (midd << 31) + ad * bd;
    uint64_t xu = x >> 61;
    uint64_t xd = x & rh_mask61;

    uint64_t rtn = xu + xd;
    if(rtn >= rh_mod) rtn -= rh_mod;
    return rtn;
}

vector<uint64_t> rh_base_pow;
void init_rh_base(int N = 128){
    rh_base = (uint64_t(1) << 32) + engine();
    rh_base_pow.resize(N);
    rh_base_pow[0] = 1;
    for(int i = 1; i < N; i++){
        rh_base_pow[i] = rh_mul(rh_base_pow[i-1], rh_base);
    }
}

//カードの種類
//'a'~'n' は 'X' に 0 ~ 13 を代入した状態を指す.
const string alphabet = "0123456789TJQKXabcdefghijklmn";

struct word {
    int len;
    string str;
    int digit;
    bigint val;
    uint64_t hash;

    word(){
        len = 0;
        str = "";
        digit = 0;
        val = 0;
        hash = 0;
    }

    word(char c){
        if('0' <= c && c <= '9') val = c - '0';
        else if('a' <= c && c <= 'n') val = c - 'a';
        else if(c == 'T') val = 10;
        else if(c == 'J') val = 11;
        else if(c == 'Q') val = 12;
        else if(c == 'K') val = 13;
        else {
            cout << "!Wrong Argument" << endl;
            assert(false);
        }

        digit = (val < 10) ? 1 : 2;
        len = 1;
        str = string(1, c);
        hash = rh_base_pow[c];
    }

    word operator*(word other){
        word rtn;
        rtn.len = len + other.len;
        rtn.str = str + other.str;
        rtn.digit = digit + other.digit;
        rtn.val = val * pow(bigint(10), other.digit) + other.val;
        rtn.hash = hash + other.hash;
        if(rtn.hash >= rh_mod) rtn.hash -= rh_mod;
        return rtn;
    }
};

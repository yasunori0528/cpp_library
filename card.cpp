const string alphabet = "0123456789TJQKXabcdefghijklmn";

struct word {
    int len;
    string str;
    int digit;
    bigint val;

    word(){
        len = 0;
        str = "";
        digit = 0;
        val = 0;
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
    }

    word operator*(word other){
        word rtn;
        rtn.len = len + other.len;
        rtn.str = str + other.str;
        rtn.digit = digit + other.digit;
        rtn.val = val * pow(bigint(10), other.digit) + other.val;
        return rtn;
    }
};

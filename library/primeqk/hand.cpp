const int HAND_SEGMENT_WIDTH = 4;
class hand {
public:
    hand() {
        a = 0;
        len = 0;
    }

    hand(string &s) {
        a = 0;
        len = 0;
        for(char &c : s) {
            if(is_symbol(c)) continue;
            a += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            len++;
        }
    }

    int get_a() {
        return a;
    }

    int size() {
        return len;
    }

    int count(int x) {
        return a >> (x * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    int count(char c) {
        return a >> (char_to_int(c) * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    bool contain(string &s) {
        hand s_hand(s);
        for(int i = 0; i < NUM_CARD_TYPES; i++) {
            if(s_hand.count(i) > count(i)) return false;
        }
        return true;
    }

    void draw(int x) {
        a += uint64_t(1) << (x * HAND_SEGMENT_WIDTH);
        len++;
    }

    void draw(char c) {
        a += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        len++;
    }

    void discard(int x) {
        a -= uint64_t(1) << (x * HAND_SEGMENT_WIDTH);
        len--;
    }

    void discard(char c) {
        a -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        len--;
    }

    void play(string &s) {
        for(char &c : s) {
            if(is_symbol(c)) continue;
            a -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            len++;
        }
    }

    bool div25() {
        if(count(1)) return false;
        if(count(3)) return false;
        if(count(7)) return false;
        if(count(9)) return false;
        if(count(11)) return false;
        if(count(13)) return false;
        if(count(14)) return false;
        return true;
    }

    int mod3() {
        if(count(14)) return -1;
        int r = 0;
        for(int i = 0; i <= 13; i++) {
            r += count(i) * i;
        }
        r %= 3;
        return r;
    }

    int mod11() {
        if(count(14)) return -1;
        for(int i = 0; i < 10; i++) if(count(i)) return -1;
        
        int r = 0;
        for(int i = 10; i <= 13; i++) {
            r += count(i) * i;
        }
        r %= 11;
        return r;
    }

    bigint max_natural() {
        bigint rtn = 0;
        for(int i = 9; i >= 0; i--) {
            for(int j = 0; j < count(i); j++) {
                rtn = rtn * 10 + i;
            }
        }
        for(int j = 0; j < count(14); j++) {
            rtn = rtn * 100 + 13;
        }
        for(int i = 13; i >= 10; i--) {
            for(int j = 0; j < count(i); j++) {
                rtn = rtn * 100 + i;
            }
        }

        return rtn;
    }

    void print() {
        for(int i = 0; i <= 14; i++) {
            for(int j = 0; j < count(i); j++) {
                cout << int_to_char(i);
            }
        }
    }

private:
    uint64_t a;
    int len;
};

bool operator<(hand h, hand g) {
    return h.get_a() < g.get_a();
}

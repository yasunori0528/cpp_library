const int HAND_SEGMENT_WIDTH = 4;
class hand {
public:
    hand() {
        a = 0;
        len = 0;
    }

    hand(string &s) {
        for(char &c : s) {
            if(is_symbol(c)) continue;
            a += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            len++;
        }
    }

    int count(int x) {
        return a >> (x * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    bool contain(string &s) {
        hand s_hand(s);
        for(int i = 0; i < NUM_CARD_TYPES; i++) {
            if(s_hand.count(i) > count(i)) return false;
        }
        return true;
    }

    void draw(char c) {
        a += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        len++;
    }

    void play(string &s) {
        for(char &c : s) {
            if(is_symbol(c)) continue;
            a -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            len++;
        }
    }

private:
    uint64_t a;
    int len;
};

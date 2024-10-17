class hand {
    uint64_t s;

    void insert(char c) {
        assert(('1' <= c && c <= '9') || ('A' <= c && c <= 'Z'));
        int x = char_to_int(c);
        s += (uint64_t(1)<<(x*3));
    }
};

class state {
private:
    int r; //0 : 通常, 1 : 革命
    int t; //0 : 先手番,  1 : 後手番
    int n; //場の枚数
    bigint x; //場に出ている数
    array<hand, 2> hand;
    vector<char> field;
    deque<char> deck;

public:
    void discard() {
        for(char &c : field) deck.push_back(c);
        field.clear();
    }

    void pass() {
        discard();
        t = 1 - t;
    }

    bool draw() {
        if(deck.size()) {
            char c = deck.front();
            deck.pop_front();
            hand.insert(c);
            return true;
        }
        return false;
    }
};

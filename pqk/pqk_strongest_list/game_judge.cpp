class hand {
private:
    uint64_t s;

public:
    hand() {
        s = 0;
    }

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
    array<hand, 2> hands; //手札
    vector<char> field; //場
    deque<char> pile; //山札

public:
    state () {
        r = 0;
        t = 0;
        n = 0;
        x = 0;
    }

    void build() {
        string d = deck;
        shuffle(d.begin(), d.end(), engine);
        for(char c : d) pile.push_back(c);
    }

    void discard() {
        for(char &c : field) pile.push_back(c);
        field.clear();
    }

    void pass() {
        discard();
        t = 1 - t;
    }

    bool draw() {
        if(pile.size()) {
            char c = pile.front();
            pile.pop_front();
            hands[t].insert(c);
            return true;
        }
        return false;
    }

    void game_start(int n) {
        for(int i = 0; i < n * 2; i++) {
            draw();
            pass();
        }
    }
};

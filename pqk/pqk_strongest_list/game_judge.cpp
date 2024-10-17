class hand {
private:
    uint64_t s;

public:
    hand() {
        s = 0;
    }

    hand(string t) {
        s = 0;
        for(char c : t) {
            if(is_symbol(c)) continue;
            else if(is_joker(c)) s += (uint64_t(1)<<(14 * 3));
            else s += (uint64_t(1)<<(char_to_int(c) * 3));
        }
    }

    int count(int x) {
        return s >> (x * 3) && 0b111;
    }

    int count(char c) {
        return count(char_to_int(c));
    }

    void insert(char c) {
        assert(('1' <= c && c <= '9') || ('A' <= c && c <= 'Z'));
        int x = char_to_int(c);
        s += (uint64_t(1)<<(x*3));
    }

    bool exist(string t) {
        hand t_hand = hand(t);
        for(int i = 1; i <= 14; i++) {
            if(count(i) < t_hand.count(i)) return false;
        }
        return true;
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

    bool play(string s) {
        if(!hands[t].exist(s)) return false;
        
    }
};

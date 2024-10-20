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
            else if(is_joker(c)) s += uint64_t(1) << (14 * 3);
            else s += uint64_t(1) << (char_to_int(c) * 3);
        }
    }

    int count(int x) {
        return (s >> (x * 3)) & uint64_t(0b111);
    }

    int count(char c) {
        return count(char_to_int(c));
    }

    int len() {
        int rtn = 0;
        for(int i = 1; i <= 14; i++) rtn += count(i);
        return rtn;
    }

    void insert(char c) {
        assert(('1' <= c && c <= '9') || ('A' <= c && c <= 'Z'));
        int x = char_to_int(c);
        s += uint64_t(1) << (x * 3);
    }

    void erase(char c) {
        c = unassign(c);
        s -= uint64_t(1) << (char_to_int(c) * 3);
    }

    bool exist(string t) {
        hand t_hand = hand(t);
        for(int i = 1; i <= 14; i++) {
            if(count(i) < t_hand.count(i)) return false;
        }
        return true;
    }

    void play(string &s) {
        for(char &c : s) {
            if(is_symbol(c)) continue;
            erase(c);
        }
    }

    void print() {
        for(int i = 1; i <= 14; i++) {
            int a = count(i);
            for(int j = 0; j < a; j++) {
                cout << alphabet[i];
            }
        }
    }

    void println() {
        print();
        cout << endl;
    }
};

const int num_of_player = 2;
class state {
private:
    int t; //0 : 先手番,  1 : 後手番, -1 : アウトゲーム
    int r; //0 : 通常, 1 : 革命
    int n; //場の枚数
    int last_player;
    bigint x; //場に出ている数
    array<hand, num_of_player> hands; //手札
    vector<string> field; //場
    deque<char> pile; //山札

public:
    state () {
        r = 0;
        t = 0;
        n = 0;
        x = 0;
        last_player = 1;
    }

    int get_t() {
        return t;
    }
    int get_r() {
        return r;
    }
    int get_n() {
        return n;
    }
    bigint get_x() {
        return x;
    }
    hand get_hand(int i) {
        return hands[i];
    }
    deque<char> get_pile() {
        return pile;
    }

    void build() {
        string d = deck;
        shuffle(d.begin(), d.end(), engine);
        for(char c : d) pile.push_back(c);
    }

    void discard() {
        for(string &s : field) for(char &c : s) pile.push_back(unassign(c));
        field.clear();
    }

    void pass() {
        t++;
        if(t == num_of_player) t = 0;
        if(t == last_player) {
            discard();
            last_player = t + 1;
            if(last_player == num_of_player) last_player = 0;
        }
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
        for(int i = 0; i < n * num_of_player; i++) {
            draw();
            pass();
        }
    }

    bool play(string s) {
        bool rtn;
        if(s == "%") {
            pass();
            rtn = true;
        }

        else if(!hands[t].exist(s)) {
            rtn = false;
        }

        else{
            hands[t].play(s);
            n = s.size();
            field.push_back(s);
            last_player = t;

            if(hands[t].len() == 0) t = -1;
            else {
                t++;
                if(t == num_of_player) t = 0;
            }
            
        }
        
        return rtn;
    }

    void println_field() {
        for(string &s : field) {
            print_str(s);
            cout << ", ";
        }
        cout << endl;
    }

    void println_pile() {
        for(char &c : pile) cout << c;
        cout << endl;
    }

    void print() {
        cout << "turn: " << t << endl;
        cout << "revolution: " << r << endl;
        cout << "hands: " << endl;
        for(int i = 0; i < num_of_player; i++) {
            cout << "player" << i << ": ";
            hands[i].println();
        }
        cout << "field: ";
        println_field();
        cout << "pile: ";
        println_pile();
    }
};

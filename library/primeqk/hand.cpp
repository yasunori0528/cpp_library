const int HAND_SEGMENT_WIDTH = 4;
class hand {
public:
    hand() {
        data = 0;
        sz = 0;
    }

    hand(string s) {
        data = 0;
        sz = 0;
        for(char &c : s) {
            if(is_symbol(c)) continue;
            data += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            sz++;
        }
    }

    uint64_t get_data() {
        return data;
    }

    int size() {
        return sz;
    }

    int count(int x) {
        return data >> (x * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    int count(char c) {
        return data >> (char_to_int(c) * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    bool contain(string &s) {
        hand s_hand(s);
        for(int i = 0; i < NUM_CARD_TYPES; i++) {
            if(s_hand.count(i) > count(i)) return false;
        }
        return true;
    }

    void draw(int x) {
        data += uint64_t(1) << (x * HAND_SEGMENT_WIDTH);
        sz++;
    }

    void draw(char c) {
        data += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        sz++;
    }

    void discard(int x) {
        data -= uint64_t(1) << (x * HAND_SEGMENT_WIDTH);
        sz--;
    }

    void discard(char c) {
        data -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        sz--;
    }

    void play(string &s) {
        for(char &c : s) {
            if(is_symbol(c)) continue;
            data -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            sz++;
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

    void natural_sub(bigint &rtn, int &d, int i, int c) {
        int d_i = (i < 10) ? 1 : 2;
        int e_i = (i < 10) ? 10 : 100;
        d += c * d_i;
        for(int j = 0; j < c; j++) {
            rtn = rtn * e_i + i;
        }
    }

    //{大きさ, 桁数} の組を返す．(leading zero を含む)
    pair<bigint, int> max_natural() {
        bigint rtn = 0;
        int d = 0;
        natural_sub(rtn, d, 9, count(9));
        natural_sub(rtn, d, 8, count(8));
        natural_sub(rtn, d, 7, count(7));
        natural_sub(rtn, d, 6, count(6));
        natural_sub(rtn, d, 5, count(5));
        natural_sub(rtn, d, 4, count(4));
        natural_sub(rtn, d, 3, count(3));
        natural_sub(rtn, d, 2, count(2));
        natural_sub(rtn, d, 13, count(13) + count(14));
        natural_sub(rtn, d, 12, count(12));
        natural_sub(rtn, d, 11, count(11));
        natural_sub(rtn, d, 1, count(1));
        natural_sub(rtn, d, 10, count(10));
        natural_sub(rtn, d, 0, count(0));

        return make_pair(rtn, d);
    }

    //{大きさ, 桁数} の組を返す．(leading zero を含む)
    pair<bigint, int> min_natural() {
        bigint rtn = 0;
        int d = 0;
        natural_sub(rtn, d, 0, count(0) + count(14));
        natural_sub(rtn, d, 10, count(10));
        natural_sub(rtn, d, 1, count(1));
        natural_sub(rtn, d, 11, count(11));
        natural_sub(rtn, d, 12, count(12));
        natural_sub(rtn, d, 13, count(13));
        natural_sub(rtn, d, 2, count(2));
        natural_sub(rtn, d, 3, count(3));
        natural_sub(rtn, d, 4, count(4));
        natural_sub(rtn, d, 5, count(5));
        natural_sub(rtn, d, 6, count(6));
        natural_sub(rtn, d, 7, count(7));
        natural_sub(rtn, d, 8, count(8));
        natural_sub(rtn, d, 9, count(9));
        
        return make_pair(rtn, d);
    }

    //sを出せるかどうか (s = [0-9*^=]*) TBW
    bool pqkable(string &s) {
        if(hand(s).max_natural().second > max_natural().second) return false;
        
        //sを 0,1,2,3,4,5,6,7,8,9,10,11,12,13,110,111,112,113 に分割する．
        int cnt = 0;
        vector<int> vs(18, 0);
        for(char c : s) {
            int x = c - '0';
            if(x == 1) {
                cnt++;
                if(cnt == 3) {
                    vs[11]++;
                    cnt -= 2;
                }
            }
            else if(0 <= x && x <= 3) {
                if(cnt == 0) vs[x]++;
                else if(cnt == 1) vs[10+x]++;
                else if(cnt == 2) vs[14+x]++;
                else assert(false);
                cnt = 0;
            }
            else {
                if(cnt == 0) ;
                else if(cnt == 1) vs[1]++;
                else if(cnt == 2) vs[11]++;
                else assert(false);
                cnt = 0;
                if(!is_symbol(c)) vs[x]++;
            }
        }

        vector<int> vh(NUM_CARD_TYPES);
        for(int i = 0; i < NUM_CARD_TYPES; i++) {
            vh[i] = count(i);
        }

        //0~9を処理
        for(int i = 0; i < 10; i++) {
            int d = min(vh[i], vs[i]);//iを何枚使うか
            vs[i] -= d;
            vh[i] -= d;

            //X使用
            if(vs[i] > 0) {
                int d2 = vs[i];
                vs[i] -= d2;
                vh[14] -= d2;
            }
        }

        if(vh[14] < 0) return false;

        //vs残り : 10~13,110~113
        //vh残り : 0~3,10~13,X
        //110~113の分け方を全探索

        vector<int> loop(4, 0); //loop[i] : "11i"のうちloop[i]個を"Ji"と分割する
        vector<int> loop_max(4);
        for(int i = 0; i < 4; i++) loop_max[i] = vs[14+i];

        bool b = true;
        while(b) {
            vector<int> vh2 = vh;
            vector<int> vs2 = vs;
            for(int i = 0; i < 4; i++) {
                vs2[11] += loop[i];
                vs2[i] += loop[i];
                vs2[1] += vs2[i+14] - loop[i];
                vs2[i+10] += vs2[i+14] - loop[i];
                vs2[i+14] = 0;
            }

            //vs残り : 0~3,10~13
            //vh残り : 0~3,10~13,X

            //0~3
            for(int i = 0; i < 4; i++) {
                int d = min(vh2[i], vs2[i]);//iを何枚使うか
                vs2[i] -= d;
                vh2[i] -= d;

                //X使用
                if(vs2[i] > 0) {
                    int d2 = vs2[i];
                    vs2[i] -= d2;
                    vh2[14] -= d2;
                }
            }

            //vs残り : 10~13
            //vh残り : 0~3,10~13,X

            //10~13(分割，X不可)
            for(int i = 0; i < 4; i++) {
                int d = min(vh2[i+10], vs2[i+10]);
                vs2[i+10] -= d;
                vh2[i+10] -= d;
            }

            //vs残り : 10~13
            //vh残り : 0~3,X

            //10,12,13
            for(int i = 0; i < 4; i++) {
                int d = min(vh2[i], vs2[i+10]);
                vs2[i+10] -= d;
                vh2[1] -= d;
                vh2[i] -= d;

                //X使用
                if(vs2[i+10] > 0) {
                    int d2 = vs2[i+10];
                    vs2[i+10] -= d2;
                    vh2[14] -= d2;
                }
            }
            //X = 1
            if(vh2[1] < 0) {
                int d = -vh2[1];
                vh2[1] += d;
                vh2[14] -= d;
            }

            //vs残り : 11
            //vh残り : 1,X

            {
                int d = min(vs2[11], vh2[1]/2);
                vs2[11] -= d;
                vh2[1] -= d*2;

                if(vs2[11] > 0) {
                    int d2 = vs2[11];
                    vs2[11] -= d2;
                    vh2[14] -= d2;
                }
            }

            if(vh2[14] >= 0) return true;

            b = false;
            for(int i = 0; i < 4; i++) {
                if(loop[i] < loop_max[i]) {
                    b = true;
                    loop[i]++;
                    for(int j = 0; j < i; j++) {
                        loop[j] = 0;
                    }
                    break;
                }
            }
        }

        return false;
    }

    //sの出し方を全列挙 (s = [0-9*^=]*) TBW
    vector<string> way_to_play(string &s) {
        return vector<string>();
    }

    void print() {
        for(int i = 0; i <= 14; i++) {
            for(int j = 0; j < count(i); j++) {
                cout << int_to_char(i);
            }
        }
    }

private:
    uint64_t data;
    int sz;
};

bool operator<(hand h, hand g) {
    return h.get_data() < g.get_data();
}

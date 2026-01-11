struct action {
    string n; // name
    string d; // ドロー
    string a; // 出した文字列
    string p; // ペナルティ
    string k; // P/C/IN/GC/RR/%/%%
    string b; // 成功/失敗
    string w; // 決着

    action() {}

    int search(string &s, int l, int r, char c) {
        assert(0 <= l && l <= r && r <= (int)s.size());
        int i = l;
        while(i < r && s[i] != c) {
            i++;
        }
        if(i == r) i = -1;
        return i;
    }

    int search(string &s, char c) {
        int s_size = s.size();
        int i = 0;
        while(i < s_size && s[i] != c) {
            i++;
        }
        if(i == s_size) i = -1;
        return i;
    }

    string is_join(string &s) {
        regex r(R"(.*:\(.*\))");
        if(regex_match(s, r)) {
            int i = search(s, ':');
            return s.substr(0, i);
        }
        return "";
    }

    action(string s) {
        //cout << "!A " << s << endl;

        int x = search(s, ':');
        assert(x >= 0);

        n = s.substr(0, x); // name
        
        //s[l, r) を見る
        int l = x+1;
        int r = s.size();

        //cout << "!B " << s.substr(l, r-l) << endl;

        if(s[l] == '(') {
            d = s.substr(l+1,r-l-2);
        }
        else{
            if(s[l] == 'D') {
                d = s[l+2];
                l += 4;
            }

            if(s[r-1] == '#') {
                w = "W";
                r--;
            }

            if(s[l] == '%') {
                k = s.substr(l, r-l);
                b = "F";
            }
            else {
                if(s[r-1] == ']') {
                    k = s.substr(r-3, 2);
                    b = "T";
                    r -= 4;
                }

                int y = search(s, l, r, 'P');
                if(y >= 0) {
                    p = s.substr(y+2, r-y-3);
                    b = "F";
                    r = y-1;
                }
                else {
                    b = "T";
                }

                int z1 = search(s, l, r, '*');
                int z2 = search(s, l, r, '^');
                if(z1 >= 0 || z2 >= 0) {
                    k = "C";
                }
                else if(k == "") {
                    k = "P";
                }

                a = s.substr(l, r-l);
            }
        }
            
        //string t = n + "," + d + "," + a + "," + p + "," + k + "," + b + "," + w;
    }

    void print() {
        cout << n << "," << d << "," << a << "," << p << "," << k << "," << b << "," << w << endl;
    }
};

struct sufu {
//private:
    vector<string> data;

    int n; //人数
    int f; //先手
    vector<string> player;
    vector<action> fu;
    map<string,int> id;
    vector<vector<int>> act;
    vector<map<string,int>> num;

public:
    sufu() {}

    sufu(vector<string> data_) : data(data_) {
        n = 0;
        f = 0;
    }

        int search(string &s, int l, int r, char c) {
        assert(0 <= l && l <= r && r <= (int)s.size());
        int i = l;
        while(i < r && s[i] != c) {
            i++;
        }
        if(i == r) i = -1;
        return i;
    }

    int search(string &s, char c) {
        int s_size = s.size();
        int i = 0;
        while(i < s_size && s[i] != c) {
            i++;
        }
        if(i == s_size) i = -1;
        return i;
    }

    string is_join(string &s) {
        regex r(R"(.*:\(.*\))");
        if(regex_match(s, r)) {
            int i = search(s, ':');
            return s.substr(0, i);
        }
        return "";
    }

    void build() {
        for(auto &s : data) {
            string pl = is_join(s);
            if(pl.size()) {
                id[pl] = n;
                n++;
                player.push_back(pl);
                act.push_back(vector<int>(10, 0));
                num.push_back(map<string,int>());
            }
            //cout << "!A " << s << endl;

            action ac(s);
            fu.push_back(ac);
        }
    }
};

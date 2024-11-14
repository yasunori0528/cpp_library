struct expression {
    bigint val;
    string s;
    int d;

    expression(bigint val_, string s_, int d_) : val(val_), s(s_), d(d_) {}

    void print() {
        cout << "(" << val << ", " << s << ", " << d << ")";
    }
};

expression operator*(expression x, expression y) {
    if(y.d == 0) return x;
    expression rtn(x.val * y.val, x.s + "*" + y.s, x.d + y.d);
    return rtn;
}
expression operator^(expression x, expression y) {
    if(y.d == 0) return x;
    expression rtn(pow(x.val, y.val), x.s + "^" + y.s, x.d + y.d);
    return rtn;
}
bool operator<(expression x, expression y) {
    return x.val < y.val;
}

// 大きさが max_exp 以下の指数を列挙
vector<vector<expression>> calc_exp_list(int max_exp) {
    vector<vector<expression>> V = {{expression(1, "", 0)}}; //V[i] : "^" を i 個含む指数の列
    int log_max_exp = log2(max_exp);
    while(1) {
        int V_size = V.size();
        vector<expression> next_V;
        for(int i = 2; i <= max_exp; i++) {
            string i_str = int_to_str(i);
            expression a(i, i_str, i_str.size());
            for(expression e : V[V_size-1]) {
                if(e.val > log_max_exp) break;
                expression ae = a ^ e;
                if(ae.val > max_exp) break;
                next_V.push_back(ae);
            }
        }

        if(next_V.size() == 0) break;
        sort(next_V.begin(), next_V.end());
        V.push_back(next_V);
    }

    vector<vector<expression>> rtn(max_exp+1);
    for(auto &vi : V) {
        for(expression &vij : vi) {
            rtn[bigint_to_int(vij.val)].push_back(vij);
        }
    }

    return rtn;
}

// max_pd 桁以下の素数を底にもつ冪のうち，消費桁数が d 以下で，手札 h で使いうるもの (max_d : hの桁数)
vector<vector<expression>> calc_pow_list(int max_pd,int d, int max_d, hand h, vector<vector<expression>> &exp_list) {
    vector<vector<expression>> rtn(max_d+1);
    for(bigint p = 2; p < pow(bigint(10), bigint(max_pd)); p++) {
        if(!miller_rabin(p)) continue;
        int p_digit = digit(p);
        string p_str = int_to_str(p);
        bigint pa = 1;
        for(int a = 1; a < int(exp_list.size()); a++) {
            pa *= p;
            int pa_digit = digit(pa);
            if(p_digit + pa_digit > max_d) break;
            for(expression e : exp_list[a]) {
                string pe_str = p_str;
                if(a > 1) pe_str += "^" + e.s;
                expression pe(pa, pe_str, p_str.size() + e.d);
                if(pe.d + pa_digit <= max_d) rtn[pe.d].push_back(pe);
            }
        }
    }

    for(auto &i : rtn) {
        sort(i.begin(), i.end());
    }
    return rtn;
}

//h から出せる合成数のうち，素因数場が d 桁以下のものを全探索し出力する．
void search_composite(hand h, int d) {
    //1. 指数の形を全列挙 ("", "2", "3", "4", "2^2", "5", ... , "256", "2^8", "2^2^3", "4^4", "4^2^2", "16^2", ...)
    //2. d/2桁以下の素数を底にもつ冪を全列挙
    //3. 2.の積で表される合成数を全探索
    //4. d/2桁より大きい素数を使う合成数を全探索(d/2桁より大きい素数は1つしか使えないので素数表を持つ必要がない)

    int max_d = h.max_natural().second;
    int max_exp = max_d * 4;//指数部の上界

    vector<vector<expression>> exp_list = calc_exp_list(max_exp); //exp_list[i] : 大きさがiの指数部の列

    vector<vector<expression>> pow_list = calc_pow_list(d / 2, d, max_d, h, exp_list);
}

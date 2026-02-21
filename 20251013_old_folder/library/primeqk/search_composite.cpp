struct expression {
    bigint val;
    string s;
    int d;

    expression() {}

    expression(bigint val_, string s_, int d_) : val(val_), s(s_), d(d_) {}

    void print() {
        cout << s << " = " << val << ", " << d;
    }
};

const expression EXP0(0, "", 0); //積の単位元
const expression EXP1(1, "", 0); //冪の単位元

expression operator*(expression x, expression y) {
    if(y.d == 0) return x;
    if(x.d == 0) return y;
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
vector<vector<expression>> calc_pow_list(int max_pd, int d, int max_d, hand h, vector<vector<expression>> &exp_list) {
    //cout << "calc_pow_list(int " << max_pd << ", int " << d << ", int " << max_d << ", hand h, vector<vector<expression>> &exp_list)" << endl;
    //chmin(max_pd, (max_d - 1) / 2);
    vector<vector<expression>> rtn(max_d+1);
    for(bigint p = 2; p < pow(bigint(10), bigint(max_pd)); p++) {
        int p_digit = digit(p);
        string p_str = int_to_str(p);
        if(!h.pqkable(p_str)) continue;
        if(!miller_rabin(p)) continue;

        if(engine()%1000==0) cout << p << endl;
        bigint pa = 1;
        for(int a = 1; a < int(exp_list.size()); a++) {
            pa *= p;
            int pa_digit = digit(pa);
            if(p_digit + pa_digit > max_d) break;
            for(expression e : exp_list[a]) {
                string pe_str = p_str;
                if(a > 1) pe_str += "^" + e.s;
                expression pe(pa, pe_str, p_str.size() + e.d);
                //pe.print(); cout << endl;
                if(pe.d + pa_digit <= max_d && h.pqkable(pe_str)) rtn[pe.d].push_back(pe);
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

    int max_d = h.max_natural().second; //手札の桁数
    chmin(d, max_d - 1);
    int max_exp = max_d * 4; //指数部の上界
    int d_big = min(d / 2 + 1, (max_d + 5) / 4); //1つしか使えない素数の桁数の下限
    int d_small = d - d_big; //大きい素数を使うときの残りの桁数の上限

    //残りの最大値
    //素因数場 : (maxd - d_big - 1)桁 = (d_big)桁 * 1桁
    //大きさ : 10 ^ (maxd - d_big - 1) = 10 ^ (d_big - 1) * 10 ^ (maxd - d_big * 2)
    bigint small_max = 0;
    if(max_d - d_big * 2 >= 0) small_max = pow((bigint)10, max_d - d_big * 2);

    vector<vector<expression>> exp_list = calc_exp_list(max_exp); //exp_list[i] : 大きさがiの指数部の列
    vector<vector<expression>> pow_list = calc_pow_list(d_big - 1, d, max_d, h, exp_list); //pow_list[i] : 素因数場の桁数がiの冪
    vector<vector<expression>> small_comp_list(d_small+1); //素因数場の桁数が d-(d/2+1) 桁以下の合成数のリスト． 大きい素数を使うときに再利用する
    small_comp_list[0].push_back(EXP1);

    /*cout << "exp_list" << endl;
    for(auto i : exp_list) {
        for(auto j : i) {
            j.print();
            cout << " ";
        }
        cout << endl;
    }

    cout << "pow_list" << endl;
    for(auto i : pow_list) {
        for(auto j : i) {
            j.print();
            cout << " ";
        }
        cout << endl;
    }*/

    expression best_comp = EXP0;
    int cnt = 0;

    //大きい素数を使わないもののうち, 素因数場がi桁のものを全探索
    for(int i = 1; i <= d; i++) {
        // "*"が入る位置をbit全探索
        for(int j = 0; j < (1 << (i - 1)); j++) {
            vector<int> d_list = {1};//冪の桁数の列
            for(int k = 0; k < i-1; k++) {
                if(j>>k&1) {
                    d_list.push_back(1);
                }
                else {
                    d_list[d_list.size()-1]++;
                }
            }

            int n = d_list.size();
            
            //d_listが単調減少でなければcontinue
            bool is_sorted = true;
            for(int k = 0; k < n-1; k++) {
                if(d_list[k] < d_list[k+1]) {
                    is_sorted = false;
                    break;
                }
            }
            if(!is_sorted) continue;

            cout << string(4, '=');
            for(int k : d_list) cout << k << " ";
            cout << string(4, '=');
            cout << endl;

            vector<int> loop(n, 0);
            vector<int> loop_max(n);
            for(int k = 0; k < n; k++) loop_max[k] = pow_list[d_list[k]].size();

            int min_pow_list_size = loop_max[0];
            for(int k = 0; k < n; k++) chmin(min_pow_list_size, loop_max[k]);

            if(min_pow_list_size == 0) continue;

            bigint min_val = 1;
            for(int k = 0; k < n; k++) {
                min_val *= pow_list[d_list[k]][0].val;
            }
            if(digit(min_val) + d > max_d) continue;

            bool b = true;
            while(b) {
                expression c = EXP1;
                //累積和を持ったほうが速い(TBW)
                for(int k = 0; k < n; k++) {
                    c = pow_list[d_list[k]][loop[k]] * c;
                }

                bool b2 = (c.d + int(int_to_str(c.val).size()) <= max_d);

                if(b2) {
                    if(c.d <= d_small && c.val < small_max) small_comp_list[c.d].push_back(c);
                    string c_str = int_to_str(c.val);
                    string s = c_str + "=" + c.s;
                    if(c_str != c.s && h.pqkable(s)) {
                        cout << s << endl;
                        chmax(best_comp, c);
                        cnt++;
                    }
                }
                

                b = false;
                for(int k = 0; k < n; k++) {
                    if(!b2 && k == 0) continue;
                    if(loop[k] < loop_max[k] - 1) {
                        b = true;
                        loop[k]++;
                        for(int l = k-1; l >= 0; l--) {
                            if(d_list[l] == d_list[l+1]) loop[l] = loop[l+1];
                            else loop[l] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }

    cout << "finish small" << endl;

    for(auto &v : small_comp_list) {
        if(v.size() > 0) {
            sort(v.begin(), v.end());
        }
    }

    //大きい素数を使うもの
    int a_max = exp_list.size();
    for(bigint p = pow(10, d_big - 1) + 1; p < pow(10, d - 1); p += 2) {
        string p_str = int_to_str(p);
        if(!h.pqkable(p_str)) continue;
        if(!miller_rabin(p)) continue;
        if(int(p_str.size()) * 2 + 1 > max_d) break;
        if(engine()%1000 == 0) cout << "p : " << p << endl;

        bigint pa = 1;
        for(int a = 1; a < a_max; a++) {
            pa *= p;
            if(pa > pow((bigint)10, max_d)) break;
            for(expression e : exp_list[a]) {
                string pe_str = p_str;
                if(a > 1) pe_str += "^" + e.s;
                expression pe(pa, pe_str, p_str.size() + e.d);
                if(digit(pe.val) + int(p_str.size()) > max_d) break;

                for(int i = 0; i <= d - pe.d; i++) {
                    if(small_comp_list[i].size()) {
                        bigint min_val = pe.val * small_comp_list[i][0].val;
                        if(digit(min_val) + i + pe.d > max_d) break;
                    }
                    
                    for(expression small_c : small_comp_list[i]) {
                        expression c = small_c * pe;

                        bool b2 = (c.d + int(int_to_str(c.val).size()) <= max_d);

                        if(b2) {
                            string c_str = int_to_str(c.val);
                            string s = c_str + "=" + c.s;
                            if(c_str != c.s && h.pqkable(s)) {
                                cout << s << endl;
                                chmax(best_comp, c);
                                cnt++;
                            }
                        }
                        else break;
                    }
                }
            }
        }
    }

    best_comp.print();
    cout << endl;
    cout << cnt << endl;
}

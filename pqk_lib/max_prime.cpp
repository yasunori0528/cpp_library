bool number_test(bigint x){
    //return gcd(bigint(x%30).get_ui(), 30) == 1;
    return miller_rabin(x);
    //x /= 10;
    //x *= 10;
    //return miller_rabin(x + 1) && miller_rabin(x + 3) && miller_rabin(x + 7) && miller_rabin(x + 9);
}

bool max_nutural_sub(string s, string t){
    return str_to_int(s + t) > str_to_int(t + s);
}

bigint hand_upper_bound(vector<string> v){
    for(auto &vi : v) if(vi == "X") vi = "K";

    sort(v.begin(), v.end(), max_nutural_sub);
    string s;
    for(auto vi : v) s += vi;
    return str_to_int(s);
}

map<bigint, set<vector<string>>> pushed_state;

bool skip_calc(string s, bigint x, vector<string> rest){
    if(s.size() >= 2){
        string sr = s.substr(s.size() - 2);
        bigint sr_int = str_to_int(sr);
        if(10 <= sr_int && sr_int <= 13){
            string s1;
            if(sr_int == 10) s1 = "T";
            else if(sr_int == 11) s1 = "J";
            else if(sr_int == 12) s1 = "Q";
            else s1 = "K";

            for(auto resti : rest){
                if(resti == s1) return true;
            }
        }
    }
    
    string t = s;
    for(auto i : rest) t += i;
    for(char c : t) if(c == 'X') return false;

    bigint y = str_to_int(t);
    if(y % 3 == 0) return true;

    if(rest.size() == 0) return false;

    for(auto i : rest){
        bigint z = str_to_int(i);
        if(z%2 != 0 && z%5 != 0){
            return false;
        }
    }
    return true;
}

string max_number(vector<string> v, function<bool(bigint)> f){
    pushed_state.clear();
    if(v.size() == 0) return "-1";
    if(v.size() == 1){
        string s = v[0];
        if(s == "X") return s;
        if(number_test(str_to_int(s))) return s;
        return "-1";
    }

    priority_queue<tuple<bigint, string, bigint, vector<string>>> q;
    q.push({hand_upper_bound(v), "", 0, v});
    
    string rtn = "-1";
    bigint max_val = 0;
    while(q.size()){
        auto[max_x, s, x, rest] = q.top();
        //cout << max_x << " " << s << " " << x << " :";
        //for(auto i : rest) cout << " " << i;
        //cout << endl;
        q.pop();
        if(max_val > max_x) break;
        if(skip_calc(s, x, rest)) continue;
        
        while(pushed_state.size()){
            bigint max_key = (*pushed_state.rbegin()).first;
            if(max_key > max_x) pushed_state.erase(max_key);
            else break;
        }

        if(rest.size() == 0){
            if(x > max_val && number_test(x)){
                rtn = s;
                max_val = x;
            }
            continue;
        }

        int rest_sz = rest.size();
        set<string> checked;
        int exist_x = -1;
        for(int i = 0; i < rest_sz; i++){
            string t = rest[i];
            if(checked.count(t)) continue;
            checked.insert(t);

            if(t == "X"){
                exist_x = i;
                continue;
            }
            else{
                string next_s = s + t;
                bigint next_x = str_to_int(next_s);
                auto next_rest = rest;
                swap(next_rest[i], next_rest[rest_sz - 1]);
                next_rest.pop_back();
                sort(next_rest.begin(), next_rest.end());
                if(pushed_state[next_x].count(next_rest)) continue;

                bigint ub_rest = hand_upper_bound(next_rest);
                bigint d_ub_rest = digit(ub_rest);
                bigint next_max_x = next_x * pow(mpz_class(10), d_ub_rest) + ub_rest;
                
                q.push({next_max_x, next_s, next_x, next_rest});
                pushed_state[next_x].insert(next_rest);
            }
        }

        if(exist_x >= 0){
            int i = exist_x;
            auto next_rest = rest;
            swap(next_rest[i], next_rest[rest_sz - 1]);
            next_rest.pop_back();
            sort(next_rest.begin(), next_rest.end());

            for(int j = 15 + 0; j <= 15 + 13; j++){
                if(s.size() == 0 && j == 15) continue;
                char c = alphabet[j];
                if(checked.count(string(1, alphabet[j-15]))) continue;
                string next_s = s + c;
                mpz_class next_x = str_to_int(next_s);
                if(pushed_state[next_x].count(next_rest)) continue;

                mpz_class ub_rest = hand_upper_bound(next_rest);
                mpz_class d_ub_rest = digit(ub_rest);
                mpz_class next_max_x = next_x * pow(mpz_class(10), d_ub_rest) + ub_rest;
                q.push({next_max_x, next_s, next_x, next_rest});
                pushed_state[next_x].insert(next_rest);
            }
        }
    }
    return rtn;
}

string max_number(string s, function<bool(bigint)> f) {
    vector<string> v;
    for(char c : s) v.push_back(string(1, c));
    return max_number(v, f);
}

void output_assigned_x(string s){
    string assigned_list;
    for(char &c : s){
        if('a' <= c && c <= 'n'){
            assigned_list.push_back(alphabet[char_to_int(c)]);
            c = 'X';
        }
    }
    cout << s;
    for(char c : assigned_list) cout << " | X = " << c;
    cout << endl; 
}

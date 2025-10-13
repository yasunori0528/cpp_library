template<typename T>
uint bigint_to_int(T x);

//使うほうのコメントアウトを外す

//gmp
template<>
uint bigint_to_int(mpz_class x) {
    return x.get_ui();
}

//boost
/*template<>
uint bigint_to_int(boost::multiprecision::cpp_int x) {
    return static_cast<uint>(x);
}*/

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
    if (a > b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
T floor(T x, T y) {
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    T r = x%y;
    r = (r+y)%y;
    return (x-r)/y;
}

template <typename T>
T ceil(T x, T y) {
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    T r = x%y;
    r = (r+y)%y;
    if(r) x += y-r;
    return x/y;
}

bigint pow(bigint x, bigint y) {
    assert(y >= 0);
    assert(!(x == 0 && y == 0));

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<bigint, bigint>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<bigint, bigint>> pow_list(n);
    for(int i = n - 1; i >= 0; i--){
        auto [l, r] = a[i];
        auto &[pl, pr] = pow_list[i];

        if(l == 0) pl = 1;
        else if(l == 1) pl = x;
        else if(l % 2 == 0) pl = pow_list[i + 1].first * pow_list[i + 1].first;
        else pl = pow_list[i + 1].first * pow_list[i + 1].second;

        if(r == l) pr = pl;
        else if(r == 0) pr = 1;
        else if(r == 1) pr = x;
        else if(r % 2 == 0) pr = pow_list[i + 1].second * pow_list[i + 1].second;
        else pr = pow_list[i + 1].first * pow_list[i + 1].second;
    }

    return pow_list[0].first;
}

bigint pow_mod(bigint x, bigint y, bigint p) {
    assert(y >= 0);
    x %= p;

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<bigint, bigint>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<bigint, bigint>> pow_list(n);
    for(int i = n - 1; i >= 0; i--){
        auto [l, r] = a[i];
        auto &[pl, pr] = pow_list[i];

        if(l == 0) pl = 1;
        else if(l == 1) pl = x;
        else if(l % 2 == 0) pl = pow_list[i + 1].first * pow_list[i + 1].first % p;
        else pl = pow_list[i + 1].first * pow_list[i + 1].second % p;

        if(r == l) pr = pl;
        else if(r == 0) pr = 1;
        else if(r == 1) pr = x;
        else if(r % 2 == 0) pr = pow_list[i + 1].second * pow_list[i + 1].second % p;
        else pr = pow_list[i + 1].first * pow_list[i + 1].second % p;
    }

    return pow_list[0].first;
}

int digit(bigint n) {
    if(n == 0) return 0;
    if(n < 10) return 1;
    else return digit(n/10)+1;
}

int log2(bigint n) {
    int rtn = 0;
    while(n > 1) {
        n /= 2;
        rtn++;
    }
    return rtn;
}

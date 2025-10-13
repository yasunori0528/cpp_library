template<typename T>
T next_pseudorand(T x, T p, T c){
    return (x * x + c) % p;
}

template<typename T>
T pollard_rho_sub(T x){
    for(T c = 1; c < x; c++){
        if(c == x - 2) continue;
        T r1 = 2;
        T r2 = 2;
        T d = 1;
        while(d == 1){
            r1 = next_pseudorand(r1, x, c);
            r2 = next_pseudorand(next_pseudorand(r2, x, c), x, c);
            d = gcd(abs(r1 - r2), x);
        }
        if(d == x) continue;
        return d;
    }
    return 1;
}

template<typename T>
vector<T> pollard_rho(T x){
    assert(x > 0);

    vector<T> rtn;
    queue<T> q;

    while(x % 2 == 0){
        rtn.push_back(2);
        x /= 2;
    }

    if(x == 1) return rtn;

    q.push(x);

    while(q.size()){
        T y = q.front();
        q.pop();

        if(miller_rabin(y)){
            rtn.push_back(y);
            continue;
        }

        T d = pollard_rho_sub(y);

        assert(1 < d && d < y && y % d == 0);
        q.push(d);
        q.push(y / d);
    }

    return rtn;
}

template<typename T>
void trial_division_sub(T &x, T p, vector<T> &rtn){
    while(x % p == 0){
        x /= p;
        rtn.push_back(p);
    }
}

template<typename T>
vector<T> trial_division(T x){
    vector<T> rtn;

    trial_division_sub(x, T(2), rtn);
    trial_division_sub(x, T(3), rtn);
    trial_division_sub(x, T(5), rtn);

    for(T i = 7; i*i <= x; ){
        trial_division_sub(x, i, rtn);
        i += 4;
        trial_division_sub(x, i, rtn);
        i += 2;
        trial_division_sub(x, i, rtn);
        i += 4;
        trial_division_sub(x, i, rtn);
        i += 2;
        trial_division_sub(x, i, rtn);
        i += 4;
        trial_division_sub(x, i, rtn);
        i += 6;
        trial_division_sub(x, i, rtn);
        i += 2;
        trial_division_sub(x, i, rtn);
        i += 6;
    }

    if(x > 1) rtn.push_back(x);

    return rtn;
}

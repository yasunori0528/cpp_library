bool miller_rabin(bigint x, size_t k = 100){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    int s = 0;
    bigint d = x - 1;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }

    if(x - 1 < k) k = bigint_to_int(x) - 1;

    set<bigint> A;
    
    {
        bigint a_max = x - 1;
        while(A.size() < k){
            A.insert(engine() % a_max + 1);
        }
    }
    //cout << "A" << endl;
    for(bigint a : A){
        bigint t = pow_mod(a, d, x);
        if(t == 1) continue;
        bool b = false;
        for(int i = 0; i < s; i++){
            if(t == x - 1){
                b = true;
                break;
            }
            t = t * t % x;
        }
        if(b) continue;
        return false;
    }
    return true;
}

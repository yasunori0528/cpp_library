bool number_test(bigint x) {
    //return miller_rabin(x);
    return miller_rabin(x/10*10+1) && miller_rabin(x/10*10+3) && miller_rabin(x/10*10+7) && miller_rabin(x/10*10+9);
}

bigint max_potential(bigint x, hand g) {
    if(g.size() == 0) return x;
    if(g.div25()) return 0;

    bigint y = g.max_natural();
    int d = digit(y);
    bigint rtn = x * pow((bigint)10, (bigint)d) + y;
    
    int r3 = g.mod3();
    if(r3 >= 0 && (x + r3) % 3 == 0) return 0;

    int r11 = g.mod11();
    if(r11 >= 0 && d % 2) r11 = 11 - r11;
    if(r11 >= 0 && (x + r11) % 11 == 0) return 0;

    return rtn;
}

bigint max_prime(hand h) {
    set<tuple<bigint, bigint, hand>> Q;
    Q.insert(make_tuple(h.max_natural(), bigint(0), h));

    while(Q.size()) {
        auto itr = Q.rbegin();
        auto [max_x, x, g] = *itr;
        Q.erase(*itr);

        //cout << x << " ";
        //g.print();
        //cout << endl;

        if(g.size() == 0) {
            if(engine() % 10000 == 0) cout << x << endl;
            if(number_test(x)) return x;
            else continue;
        }

        for(int i = 0; i <= 13; i++) {
            if(i == 0 && x == 0) continue;

            bigint next_x;
            if(i < 10) next_x = x * 10 + i;
            else next_x = x * 100 + i;

            hand next_g = g;
            if(g.count(i)) {
                next_g.discard(i);
                bigint next_max_x = max_potential(next_x, next_g);
                if(next_max_x > 0) Q.insert(make_tuple(next_max_x, next_x, next_g));
            }
            else if(g.count(14)) {
                next_g.discard(14);
                bigint next_max_x = max_potential(next_x, next_g);
                if(next_max_x > 0) Q.insert(make_tuple(next_max_x, next_x, next_g));
            }
        }
    }

    return 0;
}

bigint pow(bigint x, bigint y){
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

class hand {
    uint64_t s;
};

class state {
    int t; //0 : 先手番,  1 : 後手番
    int n; //場の枚数
    array<hand, 2> hand;
    vector<char> field;
    deque<char> deck;
};

#include <vector>
#include <functional>
#include <iostream>

template<typename T>
class CumulativeSum {
private:
    int n;
    std::vector<T> cum;
    std::function<T(T, T)> op;
    std::function<T(T)> inv;
    T identity;

public:
    CumulativeSum(int n, std::function<T(T, T)> op, std::function<T(T)> inv, T identity) 
        : n(n), cum(n + 1, identity), op(op), inv(inv) identity(identity) {}

    CumulativeSum(const std::vector<T>& data, std::function<T(T, T)> op, std::function<T(T)> inv, T identity) 
        : n(data.size()), cum(data.size() + 1, identity), op(op), inv(inv) identity(identity) {
        // 葉ノードの初期化
        for (int i = 0; i < n; ++i) {
            cum[i + 1] = cum[i] + data[i];
        }
    }

    // 区間 [l, r) のクエリ
    T query(int l, int r) {
        return op(inv(cum[l]), cum[r]);
    }
};

int f(int x, int y){
    return x+y;
}

int main() {
    return 0;
}

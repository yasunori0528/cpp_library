#include <vector>
#include <functional>
#include <iostream>

template<typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> tree;
    std::function<T(T, T)> op;
    T identity;

public:
    SegmentTree(int n, std::function<T(T, T)> op, T identity) 
        : n(n), tree(2 * n, identity), op(op), identity(identity) {}

    SegmentTree(const std::vector<T>& data, std::function<T(T, T)> op, T identity) 
        : n(data.size()), tree(2 * data.size(), identity), op(op), identity(identity) {
        // 葉ノードの初期化
        for (int i = 0; i < n; ++i) {
            tree[n + i] = data[i];
        }
        // 内部ノードの構築
        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // セグメントツリーの構築
    void build(const std::vector<T>& data) {
        for (int i = 0; i < n; ++i) {
            tree[i + n] = data[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    // 一点更新: tree[i] を value に更新
    void update(int i, T value) {
        i += n;
        tree[i] = value;
        while (i > 1) {
            i /= 2;
            tree[i] = op(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // 区間 [l, r) のクエリ
    T query(int l, int r) {
        T resL = identity, resR = identity;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) resL = op(resL, tree[l++]);
            if (r & 1) resR = op(tree[--r], resR);
            l /= 2;
            r /= 2;
        }
        return op(resL, resR);
    }

    // 更新を行うラッパークラス
    class reference {
    public:
        reference(SegmentTree& seg, int idx) : seg(seg), idx(idx) {}

        // 実際に値を設定し、セグメントツリーを更新する
        reference& operator=(const T& value) {
            seg.update(idx, value);
            return *this;
        }

        // 暗黙の型変換を提供（必要に応じて）
        operator T() const {
            return seg.query(idx, idx + 1);
        }

    private:
        SegmentTree& seg;
        int idx;
    };

    // operator[]のオーバーロード
    reference operator[](int idx) {
        return reference(*this, idx);
    }
};

int f(int x, int y){
    return x+y;
}

int main() {
    SegmentTree<int> S(11, f, 0);
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    S.build(v);
    std::cout << S[3] << std::endl;
    std::cout << S.query(2, 4) << std::endl;
    S[3] = 2;
    std::cout << S[3] << std::endl;
    std::cout << S.query(2, 4) << std::endl;

    return 0;
}

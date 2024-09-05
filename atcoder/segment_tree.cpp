template<typename T>
class segment_tree {
private:
    int n;
    vector<T> tree;
    function<T(T, T)> op;
    T identity;

public:
    segment_tree(int n, function<T(T, T)> op, T identity)
        : n(n), tree(2 * n, identity), op(op), identity(identity) {}
    
    void build(vector<T> &data) {
        for (int i = 0; i < n; i++) {
            tree[i + n] = data[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void update(int i, T value) {
        i += n;
        tree[i] = value;
        while (i) {
            i /= 2;
            tree[i] = op(tree[2 * i], tree[2 * i + 1]);
        }
    }

    T query(int l, int r) {
        T res_l = identity;
        T res_r = identity;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) res_l = op(res_l, tree[l++]);
            if (r & 1) res_r = op(tree[--r], res_r);
            l /= 2;
            r /= 2;
        }
        return op(res_l, res_r);
    }

    class reference {
    private:
        segment_tree &seg;
        int idx;

    public:
        reference(segment_tree& seg, int idx) : seg(seg), idx(idx) {}

        reference& operator=(const T& value) {
            seg.update(idx, value);
            return *this;
        }

        operator T() const {
            return seg.query(idx, idx + 1);
        }
    };

    reference operator[](int idx) {
        return reference(*this, idx);
    }
};

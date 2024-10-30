template<typename T>
class segtree {
public:
    segtree(int n_, function<T(T, T)> op_, T identity_)
        : op(op_), identity(identity_) {
        int x = 1;
        while(x < n_) x *= 2;
        n = x;
        tree.resize(n * 2 - 1, identity);
    }
    
    void build(vector<T> &data) {
        assert(data.size() <= n);
        for (size_t i = 0; i < data.size(); i++) {
            tree[i + n - 1] = data[i];
        }
        for (size_t i = data.size(); i < n; i++) {
            tree[i + n - 1] = identity;
        }
        for (int i = n - 2; i >= 0; i--) {
            tree[i] = op(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    T query(int a, int b) {
        assert(0 <= a && a <= b && b <= n);
        return query_sub(a, b, 0, 0, n);
    }

    class reference {
    private:
        segtree &seg;
        int idx;

    public:
        reference(segtree& seg, int idx) : seg(seg), idx(idx) {}

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

private:
    int n;
    vector<T> tree;
    function<T(T, T)> op;
    T identity;

    void update(int i, T value) {
        i += n - 1;
        tree[i] = value;
        while (i > 0) {
            i = (i - 1) / 2;
            tree[i] = op(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    T query_sub(int a, int b, int i, int l, int r) {
        if(r <= a || b <= l) {
            return identity;
        }
        else if(a <= l && r <= b) {
            return tree[i];
        }
        else {
            T res_l = query_sub(a, b, i * 2 + 1, l, (l + r) / 2);
            T res_r = query_sub(a, b, i * 2 + 2, (l + r) / 2, r);
            return op(res_l, res_r);
        }
    }
};

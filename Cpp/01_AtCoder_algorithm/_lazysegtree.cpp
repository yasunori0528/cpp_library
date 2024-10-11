#include <bits/stdc++.h>
using namespace std;

template<typename T, typename U>
class lazysegtree {
private:
    int n;
    vector<T> tree;
    vector<U> lazy;
    function<T(T, T)> op;
    T identity_element;
    function<T(T, U, int)> mapping;
    function<U(U, U)> combine;
    U identity_mapping;

public:
    lazysegtree(int n_, function<T(T, T)> op_, T identity_element_, function<T(T, U, int)> mapping_, function<U(U, U)> combine_, U identity_mapping_)
        : op(op_), identity_element(identity_element_), mapping(mapping_), combine(combine_), identity_mapping(identity_mapping_) {
        int x = 1;
        while(x < n_) x *= 2;
        n = x;
        tree.resize(n * 2 - 1, identity_element);
        lazy.resize(n * 2 - 1, identity_mapping);
    }
    
    void build(vector<T> &data) {
        for (int i = 0; i < n; i++) {
            tree[i + n - 1] = data[i];
        }
        for (int i = n - 2; i >= 0; i--) {
            tree[i] = op(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    void eval(int i, int len) {
        if(lazy[i] == identity_mapping) return;
        if(i < n - 1) {
            lazy[i * 2 + 1] = combine(lazy[i], lazy[i * 2 + 1]);
            lazy[i * 2 + 2] = combine(lazy[i], lazy[i * 2 + 2]);
        }
        tree[i] = mapping(tree[i], lazy[i], len);
        lazy[i] = identity_mapping;
    }

    void apply_sub(int a, int b, U f, int i, int l, int r) {
        eval(i, r - l);
        if(a <= l && r <= b) {
            lazy[i] = combine(f, lazy[i]);
            eval(i, r - l);
        }
        else if(a < r && l < b) {
            apply_sub(a, b, f, i * 2 + 1, l, (l + r) / 2);
            apply_sub(a, b, f, i * 2 + 2, (l + r) / 2, r);
            tree[i] = op(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    void apply(int a, int b, U f) {
        apply_sub(a, b, f, 0, 0, n);
    }

    T query_sub(int a, int b, int i, int l, int r) {
        eval(i, r - l);
        if(r <= a || b <= l) {
            return identity_element;
        }
        else if(a <= l && r <= b) {
            return tree[i];
        }
        else{
            T vl = query_sub(a, b, i * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, i * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    T query(int a, int b) {
        return query_sub(a, b, 0, 0, n);
    }

    void update_sub(int i, T value) {
        i += n - 1;
        tree[i] = value;
        while (i > 0) {
            i = (i - 1) / 2;
            tree[i] = op(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    void update(int i, T value) {
        query(i, i + 1);
        update_sub(i, value);
    }

    class reference {
    private:
        lazysegtree &seg;
        int idx;

    public:
        reference(lazysegtree& seg, int idx) : seg(seg), idx(idx) {}

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

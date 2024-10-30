# Segtree

長さ $N$ の[モノイド](https://ja.wikipedia.org/wiki/%E3%83%A2%E3%83%8E%E3%82%A4%E3%83%89)の配列に対し，

- 要素の1点変更
- 区間の要素の総積の取得

を $O(\log N)$ で行うことができます．

## コンストラクタ

```cpp
segtree<T> seg(int n, function<T(T, T)> op, T identity)
```

- `T` : モノイドの型
- `op` : モノイドの二項演算
- `identity` : モノイドの単位元

長さ `n` の配列を作ります． 初期値はすべて `identity` です．

## build

```cpp
void seg.build(vector<T> &data)
```

配列の値が `data` である `segtree` を構築します．

### 制約

- `data.size()` $\leq$ `n`

## 値の更新・取得

```cpp
seg[i] = x; //更新
T x = seg[i]; //取得
```

値の更新・取得は `std::vector` と同じように行うことができます．

## query

```cpp
T seg.query(int l, int r);
```
`op(seg[l], ... , seg[r-1])` を計算します．

`l = r` のときは、 `identity` を返します．

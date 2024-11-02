# max_prime

上位互換素数を探索する関数です．
少し書き換えることで他の上位互換○○も探索できます．

## Code

[max_prime.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/max_prime.cpp)

## Depends on

[math.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/math.cpp)

[card.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/card.cpp)

[hand.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/hand.cpp)

[miller_rabin.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/miller_rabin.cpp)

[pollard_rho.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/pollard_rho.cpp)

## max_prime

```cpp
bigint max_prime(hand h)
```

手札 `h` をすべて使って作ることができる素数のうち最大のものを返します．

札の並びが欲しい場合は，`h` から数を出すときの出し方を求める関数を別途作成してください．

## 補助関数

### number_test

```cpp
bool max_number_test(bigint x)
```

デフォルトでは `x` が素数のとき `true` を返す関数です．

ここを書き換えることで，別のものも探索できます．

### max_exist_candidate

```cpp
bool max_exist_candidate(bigint &x, hand &g)
```

カードを左から順に並べている途中の状態を考えます．

すでに並んでいるカード列の大きさを `x`，まだ並べていない手札を `g` とします．

この状態から素数を作ることができない場合 `false` を返します．

デフォルトでは以下のいずれかの条件を満たすときに `false` を返します．

- 作ることができる数すべてが `2` か `5` で割り切れる

- 作ることができる数すべてが `3` で割り切れる

- 作ることができる数すべてが `11` で割り切れる

探索したいものによってはこの関数も書き換える必要があります．

### max_potential

```cpp
bigint max_potential(bigint x, hand g)
```

カードを左から順に並べている途中の状態を考えます．

すでに並んでいるカード列の大きさを `x`，まだ並べていない手札を `g` とします．

この状態から作ることのできる非負整数のうち最大のものを返します．

この状態から作ることのできる非負整数の中に `number_test` が `true` を返すものがないことが確定しているとき， $0$ を返します．

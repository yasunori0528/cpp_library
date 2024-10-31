# math

## bigint_to_int

```cpp
uint bigint_to_int(bigint x)
```

多倍長整数を `uint` 型に変換します．

`x` が `uint` 型の範囲に収まらないときの挙動は未定義です．

gmp と boost 両方の関数を用意しているので，環境に合わせて使い分けてください．


## chmax

```cpp
bool chmax(T &a, const T& b)
```

`b` が `a` より大きいとき， `a` に `b` を代入し `true` を返します．
そうでないとき，何もせずに `false` を返します．

## chmin

```cpp
bool chmin(T &a, const T& b)
```

`b` が `a` より小さいとき， `a` に `b` を代入し `true` を返します．
そうでないとき，何もせずに `false` を返します．

## floor

```cpp
T floor(T x, T y)
```

$\lfloor a / b \rfloor$ を返します．

## ceil

```cpp
T ceil(T x, T y)
```

$\lceil a / b \rceil$ を返します．


## pow

```cpp
bigint pow(bigint x, bigint y)
```

$x ^ y$ を返します．

$0 ^ 0 = 0$ です．

## pow_mod

```cpp
bigint pow_mod(bigint x, bigint y, bigint p)
```

$x ^ y \mod p$ を返します．

$0 ^ 0 = 0$ です．

## digit

```cpp
int digit(bigint n)
```

$n$ の桁数を返します．
$n = 0$ のとき，$0$ を返します．

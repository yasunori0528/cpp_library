# miller_rabin

```cpp
bool miller_rabin(bigint x, size_t k = 100)
```

非負整数 $x$ が素数であるかどうかを [Miller - Rabin 素数判定法](https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95) を用いて確率的に判定します.

合成数を誤って素数と判定してしまう確率は， $4^{-k}$ です．

$k$ は判定回数で，デフォルトでは $100$ にしています．

```cpp
bool b_100 = miller_rabin(x); //kの入力を省略すると100になります．
bool b_1000 = miller_rabin(x, 1000);
```

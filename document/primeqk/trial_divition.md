# trial_divition

```cpp
vector<T> trial_division(T x)
```

非負整数 $x$ の素因数分解を [試し割り法](https://ja.wikipedia.org/wiki/%E8%A9%A6%E3%81%97%E5%89%B2%E3%82%8A%E6%B3%95) を用いて行います．

定数倍が軽いため， $x < {10}^{13}$ 程度であれば，[Pollard's rho algorithm](https://github.com/yasunori0528/cpp_library/blob/main/document/primeqk/pollard_rho.md#pollard_rho) よりも速いです．

## 計算量

$O(\sqrt{x})$

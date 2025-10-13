# pollard_rho

## Code

[pollard_rho.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/pollard_rho.cpp)

## Depends on

[math.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/math.cpp)

[miller_rabin.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/miller_rabin.cpp)

## Required by

[max_prime.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/max_prime.cpp)

[min_prime.cpp](https://github.com/yasunori0528/cpp_library/blob/main/library/primeqk/min_prime.cpp)

```cpp
vector<T> pollard_rho(T x)
```

非負整数 $x$ の素因数分解を [Pollard's rho algorithm](https://ja.wikipedia.org/wiki/%E3%83%9D%E3%83%A9%E3%83%BC%E3%83%89%E3%83%BB%E3%83%AD%E3%83%BC%E7%B4%A0%E5%9B%A0%E6%95%B0%E5%88%86%E8%A7%A3%E6%B3%95) を用いて行います．

## 計算量

$\tilde{O}(x^{1/4})$

#include <bits/stdc++.h>
#include <gmpxx.h>
mpz_class fib1(int), fib2(int), fib3(int);

int main() {
  int n, m;
  std::cin >> n >> m;
  if(m == 1) {
    std::cout << fib1(n) << std::endl;
  } else if(m == 2) {
    std::cout << fib2(n) << std::endl;
  } else if(m == 3) {
    std::cout << fib3(n) << std::endl;
  }
  return 0;
}

mpz_class fib1(int n) {
  if(n <= 1) return n;
  else return fib1(n - 1) + fib1(n - 2);
}

mpz_class fib2(int n) {
  mpz_class a = 1, b = 0;
  for(int i = 0; i < n; ++i) {
    swap(a, b);
    b += a;
  }
  return b;
}

mpz_class fib3(int n) {
  mpz_class a = 1, b = 0, c, d;
  for(int i = 30; i >= 0; --i) {
    c = a * a + b * b;
    d = b * (2 * a + b);
    if((n >> i) & 1) {
      b = c + d;
      swap(a, d);
    } else {
      swap(a, c);
      swap(b, d);
    }
  }
  return b;
}
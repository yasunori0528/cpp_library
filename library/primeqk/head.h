#ifndef HEAD
#define HEAD

#ifdef _MSC_VER

#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <random>

#ifdef __WINDOWS__
#define NOMINMAX
#include <windows.h>
#else
#include <time.h>
#endif

#else

#include <bits/stdc++.h>

#endif



#define USE_GMP 0
#define USE_BOOST 0

#if USE_GMP

#include <gmp.h>
#include <gmpxx.h>
using uint = unsigned long long;
using bigint = mpz_class;
inline const  bigint INF(std::string(255, '9'));

#elif USE_BOOST

#include <boost/multiprecision/cpp_int.hpp>
using uint = unsigned long long;
using bigint = boost::multiprecision::cpp_int;
inline const bigint INF(std::string(255, '9'));

#else

using uint = unsigned long long;
using bigint = long long;
inline const bigint INF = LLONG_MAX;

#endif

template<typename T>
uint bigint_to_int(T x);

#if USE_GMP

template<>
uint bigint_to_int<bigint>(bigint x) {
	return x.get_ui();
}

#elif USE_BOOST

template<>
uint bigint_to_int<bigint>(boost::multiprecision::cpp_int x) {
	return static_cast<uint>(x);
}

#else

template<>
uint bigint_to_int<bigint>(bigint x) {
	return x;
}

#endif

#endif

using namespace std;

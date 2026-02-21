// Math.cpp
// date: 2025-10-13
// author: yasunori

#include <bits/stdc++.h>
using namespace std;

// x mod y
template<typename T>
T mod(const T& x, const T& y) {
	assert(y > 0);

	x %= y;
	// -y < x && x < y
	if (x < 0) x += y;

	return x;
}

// floor(x / y)
template<typename T>
T floor(const T& x, const T& y) {
	assert(y != 0);

	if (y < 0) {
		x *= -1;
		y *= -1;
	}

	return (x - mod(x, y)) / y;
}

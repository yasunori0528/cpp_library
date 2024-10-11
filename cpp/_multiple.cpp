#include <bits/stdc++.h>
using namespace std;

using bitset<1024> int1024_t;

operator+(int1024_t x, int1024_t y){
    return (x^y)+((x&y)<<1);
}
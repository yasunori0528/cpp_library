#include <bits/stdc++.h>
using namespace std;

random_device seedGenerator;
mt19937 engine(seedGenerator());

// string を uint64_t に変換する
// "abc" -> (int('a') + int('b') * base + int('c') * base ^ 2) % mod
// mod = 2 ^ 61 - 1 固定
// base は実行時にランダムで生成する
class RollingHash {

private:
    uint64_t hash;
    int size;

    static const uint64_t MOD = ((uint64_t)1 << 61) - 1;
    static uint64_t base;
    static vector<uint64_t> basePower;

public:
    // コンストラクタ：空文字列
    RollingHash() {
        hash = 0;
        size = 0;
    }

    // コンストラクタ：文字
    RollingHash(char c) {
        hash = (uint64_t)c;
        size = 1;
    }
    
    // コンストラクタ：文字列
    RollingHash(const string &s) {
        size = s.size();

        hash = 0;
        for (int i = 0; i < size; i++) {
            hash += multiple((uint64_t)s[i], basePower[i]);
        }
        modulo(hash);
    }

    // コンストラクタ：配列
    RollingHash(const vector<uint64_t> &v) {
        size = v.size();

        hash = 0;
        for (int i = 0; i < size; i++) {
            hash += multiple(v[i], basePower[i]);
        }
        modulo(hash);
    }

    // base を決定し，base の累乗を計算する．
    static void initialize(int n) {
        // 2 <= base <= 2 ^ 61 - 3 である必要がある
        // 2 ^ 59 <= base <= 2 ^ 60 + 2 ^ 59 - 1 の範囲で一様ランダムにとる

        uint64_t x = engine();
        uint64_t y = engine();
        // 60bit乱数
        uint64_t rand60 = (x << 28) + (y >> 4);

        base = ((uint64_t)1 << 59) + rand60;

        basePower = vector<uint64_t>(n + 1);
        basePower[0] = 1;
        for (int i = 0; i < n; i++) {
            basePower[i + 1] = multiple(basePower[i], base);
        }
    }

    // サイズを取得
    int getSize() const {
        return size;
    }

    // ハッシュ値を取得
    uint64_t getHash() const {
        return hash;
    }

    RollingHash operator*(const RollingHash& otherRollingHash) {
        int otherSize = otherRollingHash.getSize();
        uint64_t otherHash = otherRollingHash.getHash();

        int rtnSize = size + otherRollingHash.getSize();
        uint64_t rtnHash = multiple(hash, basePower[otherSize]) + otherHash;

        if (rtnHash >= MOD) rtnHash -= MOD;

        return RollingHash(rtnSize, rtnHash);
    }

private:
    // コンストラクタ：直接入力
    RollingHash(int aSize, uint64_t aHash) {
        size = aSize;
        hash = aHash;
    }

    // x %= MOD;
    static void modulo(uint64_t& x) {
        const uint64_t MASK_61 = MOD;
        uint64_t xUpper = x >> 61;
        uint64_t xLower = x & MASK_61;

        uint64_t rtn = xUpper + xLower;
        if (rtn >= MOD) rtn -= MOD;

        x = rtn;
    }

    // a * b % mod
    static uint64_t multiple(const uint64_t& a, const uint64_t& b) {
        static const uint64_t MASK_30 = ((uint64_t)1 << 30) - 1;
        static const uint64_t MASK_31 = ((uint64_t)1 << 31) - 1;
        
        // a = aUpper * 2 ^ 31 + aLower
        // b = bUpper * 2 ^ 31 + bLower
        // mid = (aUpper * bLower + aLower * bUpper)
        // mid = midUpper * 2 ^ 30 + midLower
        //
        // a * b = aUpper * bUpper * 2 ^ 62 + (aUpper * bLower + aLower * bUpper) * 2 ^ 31 + aLower * bLower
        // = aUpper * bUpper * 2 ^ 62 + midUpper * 2 ^ 61 + midLower * 2 ^ 31 + aLower * bLower
        // = aUpper * bUpper * 2 + midUpper + midLower * 2 ^ 31 + aLower * bLower

        uint64_t aUpper = a >> 31;
        uint64_t aLower = a & MASK_31;
        uint64_t bUpper = b >> 31;
        uint64_t bLower = b & MASK_31;

        uint64_t mid = aUpper * bLower + aLower * bUpper;
        uint64_t midUpper = mid >> 30;
        uint64_t midLower = mid & MASK_30;

        // x = a * b
        uint64_t x = aUpper * bUpper * 2 + midUpper + (midLower << 31) + aLower * bLower;
        // modulo(x);

        return x;
    }
};

uint64_t RollingHash::base;
vector<uint64_t> RollingHash::basePower;

// Decimal.cpp
// date: 2025-10-13
// author: yasunori

#include <bits/stdc++.h>
#include "Math.cpp"
using namespace std;

// 符号なし固定長十進整数
template<uint8_t BASE, uint8_t MAX_DIGIT>
class Decimal {
private:
	// 値を格納する配列
	// table[i] : 10^iの位
	uint8_t* table;

public:
	// コンストラクタ
	Decimal() {
		table = new uint8_t[MAX_DIGIT];
		for (uint8_t i = 0; i < MAX_DIGIT; i++) {
			table[i] = 0;
		}
	}
	// コンストラクタ(デフォルト整数型)
	Decimal(uint64_t x) {
		table = new uint8_t[MAX_DIGIT];
		for (uint8_t i = 0; i < MAX_DIGIT; i++) {
			table[i] = uint8_t(x % BASE);
			x /= BASE;
		}
	}
	// コンストラクタ(文字列)
	Decimal(string s) {
		assert(s.size() <= MAX_DIGIT);

		table = new uint8_t[MAX_DIGIT];
		for (uint8_t i = 0; i < s.size(); i++) {
			table[i] = uint8_t(s[s.size() - i - 1] - '0');
		}
		for (uint8_t i = s.size(); i < MAX_DIGIT; i++) {
			table[i] = 0;
		}
	}
	// デストラクタ
	~Decimal() {
		delete[] table;
	}

	// 加算
	Decimal operator+(const Decimal& other) {
		uint8_t* newTable;
		newTable = new uint8_t[MAX_DIGIT];
		for (uint8_t i = 0; i < MAX_DIGIT; i++) {
			newTable[i] = table[i] + other.table[i];
		}

		Decimal result(newTable);
		result.normalize();
		return result;
	}

	// 乗算
	Decimal operator*(const Decimal& other) {
		uint8_t* newTable;
		newTable = new uint8_t[MAX_DIGIT];
		for (uint8_t i = 0; i < MAX_DIGIT; i++) {
			newTable[i] = 0;
		}

		for (uint8_t i = 0; i < MAX_DIGIT; i++) {
			for (uint8_t j = 0; j < MAX_DIGIT; j++) {
				if (i + j >= MAX_DIGIT) break;
				newTable[i + j] += table[i] * table[j];
			}
		}

		Decimal result(newTable);
		result.normalize();
		return result;
	}

private:
	// コンストラクタ(配列)
	Decimal(uint8_t* aTable) {
		table = move(aTable);
	}

	// 正規化
	// 各桁の値を0-9にする
	void normalize() {
		for (uint8_t i = 0; i+1 < MAX_DIGIT; i++) {
			table[i+1] += floor(table[i], BASE);
			table[i] = mod(table[i], BASE);
		}
	}
};

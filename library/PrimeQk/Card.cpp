// Card.cpp
// date : 2026/01/30
// author : yasunori

#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using BigInt = mpz_class;

// カードを管理する列挙型
enum CardType : int8_t {
	CardUnknown = -1,	// 未知のカード
	Card0 = 0,
	Card1 = 1,
	Card2 = 2,
	Card3 = 3,
	Card4 = 4,
	Card5 = 5,
	Card6 = 6,
	Card7 = 7,
	Card8 = 8,
	Card9 = 9,
	CardT = 10,
	CardJ = 11,
	CardQ = 12,
	CardK = 13,
	CardX = 14,
};

// Cardの表示名
string CARD_NAME = "0123456789TJQKX";

class Card {
	CardType cardType;
	bool isJoker;

	Card(CardType aCardType) {
		cardType = aCardType;
		isJoker = aCardType == CardX;
	}

	char getDisplayName() const {
		assert(cardType != CardUnknown);
		return CARD_NAME[(int)cardType];
	}
};

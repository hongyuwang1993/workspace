#include <gtest/gtest.h>
#include "DNPoker.h"

class DNPokerTest : public ::testing::Test {
protected:
	DNPokerTest() {}
	virtual ~DNPokerTest() {}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}

	void testConstructor() {
		struct DNPoker poker1;
		EXPECT_EQ(0, poker1.poker_color);
		EXPECT_EQ(0, poker1.poker_value);
	}

	void testEqual(){
		struct DNPoker poker1;
		struct DNPoker poker2;
		poker1.poker_color = 0;
		poker1.poker_value = 2;
		poker2.poker_color = 3;
		poker2.poker_value = 0;
		if (poker1.IsNullPoker()){
			if (poker2.IsNullPoker())
				EXPECT_TRUE(poker1 == poker2);
			else
				EXPECT_FALSE(poker1 == poker2);
		}
		poker2.poker_value = 1;
		if (poker1.IsNullPoker()){
			if (poker2.IsNullPoker())
				EXPECT_TRUE(poker1 == poker2);
			else
				EXPECT_FALSE(poker1 == poker2);
		}
		poker1.poker_color = 2;
		EXPECT_FALSE(poker1 == poker2);
		poker1.poker_color = 3;
		poker1.poker_value = 1;
		EXPECT_TRUE(poker1 == poker2);
	}

	void testFriendlyName(){
		struct DNPoker poker;
		poker.poker_color = 2;
		poker.poker_value = 5;
		EXPECT_STREQ("Ó£»¨5", poker.FriendlyName().c_str());

		struct DNPoker nullpoker;
		EXPECT_STREQ("invalid_poker", nullpoker.FriendlyName().c_str());

		poker.poker_color = 6;
		EXPECT_STREQ("invalid_poker", poker.FriendlyName().c_str());
	}

	void testReset(){
		struct DNPoker poker;
		poker.poker_color = 2;
		poker.poker_value = 3;
		EXPECT_FALSE(0 == poker.poker_color);
		EXPECT_FALSE(0 == poker.poker_value);

		poker.Reset();
		EXPECT_TRUE(0 == poker.poker_color);
		EXPECT_TRUE(0 == poker.poker_value);
	}
	void testAssign(){
		struct DNPoker poker1;
		struct DNPoker poker2;
		poker1.poker_color = 1;
		poker1.poker_value = 2;
		EXPECT_FALSE(1 == poker2.poker_color);
		EXPECT_FALSE(2 == poker2.poker_value);
		poker2 = poker1;
		EXPECT_TRUE(1 == poker2.poker_color);
		EXPECT_TRUE(2 == poker2.poker_value);
	}
}; 

void testDNPokerValueFirstCmp(){
	struct DNPoker poker1;
	struct DNPoker poker2;
	poker1.poker_value = 2;
	poker2.poker_value = 2;
	poker1.poker_color = 4;
	poker2.poker_color = 3;
	EXPECT_EQ(false, DNPokerValueFirstCmp(poker1, poker2));
	poker1.poker_color = 3;
	EXPECT_EQ(false, DNPokerValueFirstCmp(poker1, poker2));
	poker1.poker_color = 2;
	EXPECT_EQ(true, DNPokerValueFirstCmp(poker1, poker2));
}

void testDNPokerColorFirstCmp(){
	struct DNPoker poker1;
	struct DNPoker poker2;
	poker1.poker_value = 4;
	poker2.poker_value = 3;
	poker1.poker_color = 3;
	poker2.poker_color = 3;
	EXPECT_EQ(false, DNPokerColorFirstCmp(poker1, poker2));
	poker1.poker_value = 3;
	EXPECT_EQ(false, DNPokerColorFirstCmp(poker1, poker2));
	poker1.poker_value = 2;
	EXPECT_EQ(true, DNPokerColorFirstCmp(poker1, poker2));
}


class CDNPokerTest : public ::testing::Test{
protected:
	CDNPokerTest() {}
	virtual ~CDNPokerTest() {}

	void testConstructor(){
		CDNPoker cpoker;
		EXPECT_EQ(52, cpoker.poker_num_);
		EXPECT_EQ(0, cpoker.deal_position_);
		EXPECT_EQ(1, cpoker.poker_min_value_);
		EXPECT_EQ(13, cpoker.poker_max_value_);
	}

	void testDealPokers(){
		struct DNPoker *pokers[5];
		CDNPoker cpoker;
		int test[52];
		for (int i = 0; i < 52; i++)
			test[i] = 0;
		for (int i = 0; i < 5; i++){
			pokers[i] = (DNPoker*)malloc(5 * sizeof(DNPoker));
		}
		cpoker.Shuffle();
		cpoker.DealPokers(pokers, 5);
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				test[(pokers[i][j].poker_color - 1) * 13 + pokers[i][j].poker_value - 1]++;
			}
		}
		for (int i = 0; i < 52; i++){
			EXPECT_TRUE(test[i] < 2);
		}
	}

	void testFindMaxPoker(){
		CDNPoker cpoker;
		struct DNPoker poker[5];
		poker[0].poker_color = 1;
		poker[0].poker_value = 5;
		poker[1].poker_color = 1;
		poker[1].poker_value = 8;
		poker[2].poker_color = 2;
		poker[2].poker_value = 5;
		poker[3].poker_color = 3;
		poker[3].poker_value = 8;
		poker[4].poker_color = 1;
		poker[4].poker_value = 2;
		EXPECT_TRUE(poker[3] == *cpoker.FindMaxPoker(poker));
	}

	void testComparePokers(){

	}
};

TEST_F(DNPokerTest, testConstructor) {
	testConstructor();
}

TEST_F(DNPokerTest, testEqual) {
	testEqual();
}

TEST_F(DNPokerTest, testFriendlyName) {
	testFriendlyName();
}

TEST_F(DNPokerTest, testReset) {
	testReset();
}

TEST_F(DNPokerTest, testDNPokerValueFirstCmp) {
	testDNPokerValueFirstCmp();
}

TEST_F(DNPokerTest, testDNPokerColorFirstCmp) {
	testDNPokerColorFirstCmp();
}

TEST_F(DNPokerTest, testAssign) {
	testAssign();
}

TEST_F(CDNPokerTest, testConstructor) {
	testConstructor();
}

TEST_F(CDNPokerTest, testDealPokers) {
	testDealPokers();
}

TEST_F(CDNPokerTest, testFindMaxPoker) {
	testFindMaxPoker();
}
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
}; 

TEST_F(DNPokerTest, testConstructor) {
	testConstructor();
}

TEST_F(DNPokerTest, testEqual) {
	testEqual();
}
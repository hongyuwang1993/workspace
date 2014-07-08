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
};

TEST_F(DNPokerTest, testConstructor) {
	testConstructor();
}

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

	void testNotEqual(){
		struct DNPoker poker1;
		struct DNPoker poker2;
		poker1.poker_color = 0;
		poker1.poker_value = 2;
		poker2.poker_color = 3;
		poker2.poker_value = 0;	
		EXPECT_FALSE(poker1 != poker2);
		poker1.poker_color = 1;
		EXPECT_TRUE(poker1 != poker2);
		poker2.poker_color = 1;
		poker2.poker_value = 2;
		EXPECT_FALSE(poker1 != poker2);
		poker2.poker_color = 5;
		EXPECT_TRUE(poker1 != poker2);
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
	
	void testIsNullPoker(){
		struct DNPoker poker;
		EXPECT_TRUE(poker.IsNullPoker());
		poker.poker_value = 1;
		EXPECT_TRUE(poker.IsNullPoker());
		poker.poker_value = 0;
		poker.poker_color = 1;
		EXPECT_TRUE(poker.IsNullPoker());
		poker.poker_value = 1;
		EXPECT_FALSE(poker.IsNullPoker());
	}

	void testFriendlyName(){
		struct DNPoker poker;
		poker.poker_color = 2;
		poker.poker_value = 5;
		EXPECT_STREQ("樱花5", poker.FriendlyName().c_str());
		struct DNPoker nullpoker;
		EXPECT_STREQ("invalid_poker", nullpoker.FriendlyName().c_str());

		poker.poker_color = 6;
		EXPECT_STREQ("invalid_poker", poker.FriendlyName().c_str());
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

	void testGetPokerNum(){
		CDNPoker cpoker;
		cpoker.poker_num_ = 52;
		EXPECT_EQ(52, cpoker.GetPokerNum());
	}

	void testGetMinValue(){
		CDNPoker cpoker;
		cpoker.poker_min_value_ = 1;
		EXPECT_EQ(1, cpoker.GetMinValue());
	}

	void testGetMaxValue(){
		CDNPoker cpoker;
		cpoker.poker_max_value_ = 13;
		EXPECT_EQ(13, cpoker.GetMaxValue());
	}

	void testInitPoker(){
		CDNPoker cpoker;
		cpoker.InitPoker(1, 13);
		EXPECT_EQ(0, cpoker.deal_position_);
		EXPECT_EQ(1, cpoker.poker_min_value_);
		EXPECT_EQ(13, cpoker.poker_max_value_);
		EXPECT_EQ(52, cpoker.poker_num_);
		for (int i = 1; i <= 4; i++){
			for (int j = 1; j <= 13; j++){
				EXPECT_EQ(i, cpoker.dn_Poker_[(i - 1)*13+j - 1].poker_color);
				EXPECT_EQ(j, cpoker.dn_Poker_[(i - 1) * 13 + j - 1].poker_value);
			}
		}
		cpoker.InitPoker(12, 3);
		EXPECT_EQ(0, cpoker.deal_position_);
		EXPECT_EQ(0, cpoker.poker_min_value_);
		EXPECT_EQ(0, cpoker.poker_max_value_);
		EXPECT_EQ(0, cpoker.poker_num_);
	}

	void testShuffle(){
		CDNPoker cpoker;
		DNPoker pokers[52];
		memcpy(pokers, cpoker.dn_Poker_, 52 * sizeof(struct DNPoker));
		cpoker.Shuffle();
		int test[52];
		//测试52张牌是否不相同
		for (int i = 0; i < 52; i++)
			test[i] = 0;
		for (int i = 0; i < 52; i++){
			test[(cpoker.dn_Poker_[i].poker_color - 1) * 13 + cpoker.dn_Poker_[i].poker_value - 1]++;
		}
		for (int i = 0; i < 52; i++)
			EXPECT_EQ(1, test[i]);
		//测试洗牌后牌是否不一样了
		int m = 0;
		for (int i = 0; i < 52; i++){
			if (pokers[i] != cpoker.dn_Poker_[i]){
				m = 1;
				break;
			}
		}
		EXPECT_EQ(1, m);
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

	void testCompareSinglePoker(){
		CDNPoker cpoker;
		DNPoker poker1, poker2;
		poker1.poker_color = 1;
		poker1.poker_value = 8;
		poker2.poker_color = 2;
		poker2.poker_value = 4;
		EXPECT_TRUE(cpoker.CompareSinglePoker(&poker1, &poker2));
		poker2.poker_value = 8;
		EXPECT_FALSE(cpoker.CompareSinglePoker(&poker1, &poker2));
	}

	void testComparePokers(){
		CDNPoker cpoker;
		struct DNPokers pokers_a, pokers_b;
		//测试两者都没有牛
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 3;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 5;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 2;
		pokers_a.poker[3].poker_color = 4;
		pokers_a.poker[3].poker_value = 9;
		pokers_a.poker[4].poker_color = 4;
		pokers_a.poker[4].poker_value = 8;

		pokers_b.poker[0].poker_color = 2;
		pokers_b.poker[0].poker_value = 3;
		pokers_b.poker[1].poker_color = 1;
		pokers_b.poker[1].poker_value = 10;
		pokers_b.poker[2].poker_color = 1;
		pokers_b.poker[2].poker_value = 13;
		pokers_b.poker[3].poker_color = 3;
		pokers_b.poker[3].poker_value = 5;
		pokers_b.poker[4].poker_color = 4;
		pokers_b.poker[4].poker_value = 6;
		EXPECT_FALSE(cpoker.ComparePokers(pokers_a, pokers_b));
		//一者为5小牛
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 1;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 2;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 2;
		pokers_a.poker[3].poker_color = 4;
		pokers_a.poker[3].poker_value = 3;
		pokers_a.poker[4].poker_color = 4;
		pokers_a.poker[4].poker_value = 1;

		pokers_b.poker[0].poker_color = 2;
		pokers_b.poker[0].poker_value = 3;
		pokers_b.poker[1].poker_color = 1;
		pokers_b.poker[1].poker_value = 10;
		pokers_b.poker[2].poker_color = 1;
		pokers_b.poker[2].poker_value = 13;
		pokers_b.poker[3].poker_color = 3;
		pokers_b.poker[3].poker_value = 5;
		pokers_b.poker[4].poker_color = 4;
		pokers_b.poker[4].poker_value = 6;
		EXPECT_FALSE(cpoker.ComparePokers(pokers_a, pokers_b));
		//一者为4炸
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 1;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 1;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 1;
		pokers_a.poker[3].poker_color = 1;
		pokers_a.poker[3].poker_value = 3;
		pokers_a.poker[4].poker_color = 4;
		pokers_a.poker[4].poker_value = 1;

		pokers_b.poker[0].poker_color = 2;
		pokers_b.poker[0].poker_value = 3;
		pokers_b.poker[1].poker_color = 1;
		pokers_b.poker[1].poker_value = 10;
		pokers_b.poker[2].poker_color = 1;
		pokers_b.poker[2].poker_value = 13;
		pokers_b.poker[3].poker_color = 3;
		pokers_b.poker[3].poker_value = 5;
		pokers_b.poker[4].poker_color = 4;
		pokers_b.poker[4].poker_value = 6;
		EXPECT_FALSE(cpoker.ComparePokers(pokers_a, pokers_b));

		//测试一者有牛，一者没牛
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 3;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 5;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 2;
		pokers_a.poker[3].poker_color = 4;
		pokers_a.poker[3].poker_value = 9;
		pokers_a.poker[4].poker_color = 4;
		pokers_a.poker[4].poker_value = 7;

		pokers_b.poker[0].poker_color = 2;
		pokers_b.poker[0].poker_value = 3;
		pokers_b.poker[1].poker_color = 1;
		pokers_b.poker[1].poker_value = 10;
		pokers_b.poker[2].poker_color = 1;
		pokers_b.poker[2].poker_value = 13;
		pokers_b.poker[3].poker_color = 3;
		pokers_b.poker[3].poker_value = 5;
		pokers_b.poker[4].poker_color = 4;
		pokers_b.poker[4].poker_value = 6;
		EXPECT_FALSE(cpoker.ComparePokers(pokers_a, pokers_b));
		//测试两者都有牛
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 3;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 5;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 2;
		pokers_a.poker[3].poker_color = 4;
		pokers_a.poker[3].poker_value = 9;
		pokers_a.poker[4].poker_color = 4;
		pokers_a.poker[4].poker_value = 8;

		pokers_b.poker[0].poker_color = 2;
		pokers_b.poker[0].poker_value = 3;
		pokers_b.poker[1].poker_color = 1;
		pokers_b.poker[1].poker_value = 10;
		pokers_b.poker[2].poker_color = 1;
		pokers_b.poker[2].poker_value = 13;
		pokers_b.poker[3].poker_color = 3;
		pokers_b.poker[3].poker_value = 5;
		pokers_b.poker[4].poker_color = 4;
		pokers_b.poker[4].poker_value = 12;
		EXPECT_FALSE(cpoker.ComparePokers(pokers_a, pokers_b));
		
	}

	void testCompareNiutype(){
		CDNPoker cpoker;
		EXPECT_EQ(-1, cpoker.CompareNiutype( CDNPoker::MEI_NIU, CDNPoker::WU_HUA_NIU));
		EXPECT_EQ(0, cpoker.CompareNiutype(CDNPoker::MEI_NIU, CDNPoker::MEI_NIU));
		EXPECT_EQ(1, cpoker.CompareNiutype(CDNPoker::WU_XIAO_NIU, CDNPoker::WU_HUA_NIU));
	}

	void testDN_Switch(){
		CDNPoker cpoker;
		EXPECT_EQ(CDNPoker::NIU_DING, cpoker.DN_Switch(1));
	}

	void testGetDNType(){
		CDNPoker cpoker;
		EXPECT_EQ("牛二", cpoker.GetDNType(2));
	}

	void testGetDNTypeToString(){
		CDNPoker cpoker;
		EXPECT_EQ("niu_san", cpoker.GetDNTypeToString(CDNPoker::NIU_SAN));
	}

	void testHasCow(){
		CDNPoker cpoker;
		DNPoker poker[5];
		//测试5花牛
		poker[0].poker_color = 2;
		poker[0].poker_value = 13;
		poker[1].poker_color = 1;
		poker[1].poker_value = 11;
		poker[2].poker_color = 1;
		poker[2].poker_value = 13;
		poker[3].poker_color = 3;
		poker[3].poker_value = 11;
		poker[4].poker_color = 4;
		poker[4].poker_value = 12;
		int32 pokerIndex[5] = { 0, 1, 2, 3, 4 };
		EXPECT_EQ(CDNPoker::WU_HUA_NIU, cpoker.HasCow(poker, pokerIndex));
		poker[0].poker_color = 2;
		poker[0].poker_value = 13;
		poker[1].poker_color = 1;
		poker[1].poker_value = 11;
		poker[2].poker_color = 1;
		poker[2].poker_value = 13;
		poker[3].poker_color = 3;
		poker[3].poker_value = 11;
		poker[4].poker_color = 4;
		poker[4].poker_value = 8;
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.HasCow(poker, pokerIndex));
		//测试5小牛
		poker[0].poker_color = 2;
		poker[0].poker_value = 1;
		poker[1].poker_color = 1;
		poker[1].poker_value = 1;
		poker[2].poker_color = 1;
		poker[2].poker_value = 2;
		poker[3].poker_color = 3;
		poker[3].poker_value = 2;
		poker[4].poker_color = 4;
		poker[4].poker_value = 3;
		EXPECT_EQ(CDNPoker::WU_XIAO_NIU, cpoker.HasCow(poker, pokerIndex));
		poker[0].poker_color = 2;
		poker[0].poker_value = 1;
		poker[1].poker_color = 1;
		poker[1].poker_value = 1;
		poker[2].poker_color = 1;
		poker[2].poker_value = 2;
		poker[3].poker_color = 3;
		poker[3].poker_value = 2;
		poker[4].poker_color = 4;
		poker[4].poker_value = 6;
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.HasCow(poker, pokerIndex));
		//测试4炸
		poker[0].poker_color = 2;
		poker[0].poker_value = 3;
		poker[1].poker_color = 1;
		poker[1].poker_value = 3;
		poker[2].poker_color = 3;
		poker[2].poker_value = 3;
		poker[3].poker_color = 4;
		poker[3].poker_value = 3;
		poker[4].poker_color = 4;
		poker[4].poker_value = 12;
		pokerIndex[4] = -1;
		EXPECT_EQ(CDNPoker::SI_ZHA, cpoker.HasCow(poker, pokerIndex));
		poker[0].poker_color = 2;
		poker[0].poker_value = 3;
		poker[1].poker_color = 1;
		poker[1].poker_value = 5;
		poker[2].poker_color = 3;
		poker[2].poker_value = 3;
		poker[3].poker_color = 4;
		poker[3].poker_value = 3;
		poker[4].poker_color = 4;
		poker[4].poker_value = 12;
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.HasCow(poker, pokerIndex));
		//测试牛牛
		poker[0].poker_color = 2;
		poker[0].poker_value = 3;
		poker[1].poker_color = 1;
		poker[1].poker_value = 4;
		poker[2].poker_color = 3;
		poker[2].poker_value = 3;
		poker[3].poker_color = 4;
		poker[3].poker_value = 8;
		poker[4].poker_color = 4;
		poker[4].poker_value = 2;
		pokerIndex[3] = -1;
		EXPECT_EQ(CDNPoker::NIU_NIU, cpoker.HasCow(poker, pokerIndex));
		//测试其他牛型
		poker[0].poker_color = 2;
		poker[0].poker_value = 3;
		poker[1].poker_color = 1;
		poker[1].poker_value = 4;
		poker[2].poker_color = 3;
		poker[2].poker_value = 3;
		poker[3].poker_color = 4;
		poker[3].poker_value = 8;
		poker[4].poker_color = 4;
		poker[4].poker_value = 9;
		EXPECT_EQ(CDNPoker::NIU_QI, cpoker.HasCow(poker, pokerIndex));
		poker[0].poker_color = 2;
		poker[0].poker_value = 3;
		poker[1].poker_color = 1;
		poker[1].poker_value = 4;
		poker[2].poker_color = 3;
		poker[2].poker_value = 4;
		poker[3].poker_color = 4;
		poker[3].poker_value = 8;
		poker[4].poker_color = 4;
		poker[4].poker_value = 9;
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.HasCow(poker, pokerIndex));
	}

	void testFindCow(){
		CDNPoker cpoker;
		struct DNPoker poker[5];
		int32 niuPokerIndex[5] = { -1, -1, -1, -1, -1 };
		int32 otherPokerIndex[2] = { -1, -1 };
		int test[5];
		for (int i = 0; i < 5; i++)
			test[i] = 0;
		poker[0].poker_color = 2;
		poker[0].poker_value = 3;
		poker[1].poker_color = 3;
		poker[1].poker_value = 5;
		poker[2].poker_color = 1;
		poker[2].poker_value = 2;
		poker[3].poker_color = 4;
		poker[3].poker_value = 9;
		poker[4].poker_color = 4;
		poker[4].poker_value = 7;

		cpoker.FindCow(poker, niuPokerIndex, otherPokerIndex);
		for (int i = 0; i < 3; i++)
			test[niuPokerIndex[i]]++;
		for (int i = 0; i < 2; i++)
			test[otherPokerIndex[i]]++;
		for (int i = 0; i < 5; i++)
			EXPECT_EQ(1, test[i]);
	}

	void testChangeDNPokerJQK(){
		CDNPoker cpoker;
		EXPECT_EQ(10, cpoker.ChangeDNPokerJQK(13));
		EXPECT_EQ(5, cpoker.ChangeDNPokerJQK(5));
	}

	void testDNPokerCompare(){
		CDNPoker cpoker;
		DNPoker poker1, poker2;
		poker1.poker_color = 2;
		poker1.poker_value = 5;
		poker2.poker_color = 2;
		poker2.poker_value = 5;
		EXPECT_EQ(0, cpoker.DNPokerCompare(poker1, poker2));
		poker2.poker_color = 3;
		EXPECT_EQ(-1, cpoker.DNPokerCompare(poker1, poker2));
		poker1.poker_value = 9;
		EXPECT_EQ(1, cpoker.DNPokerCompare(poker1, poker2));
	}
};

class DNPokersTest : public ::testing::Test{
protected:
	DNPokersTest() {}
	virtual ~DNPokersTest() {}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}

	void testConstructor() {
		struct DNPokers pokers;
		EXPECT_EQ(CDNPoker::MEI_NIU, pokers.dn_type);
		EXPECT_EQ(CDNPoker::MEI_NIU, pokers.dn_player_select_type);
		EXPECT_EQ(NULL, pokers.max_poker);
	}

	void testReset(){
		struct DNPokers pokers;
		EXPECT_EQ(CDNPoker::MEI_NIU, pokers.dn_type);
		EXPECT_EQ(CDNPoker::MEI_NIU, pokers.dn_player_select_type);
		EXPECT_EQ(NULL, pokers.max_poker);
		for (int i = 0; i < 5; i++){
			EXPECT_EQ(0, pokers.poker[i].poker_color);
			EXPECT_EQ(0, pokers.poker[i].poker_value);
			EXPECT_EQ(-1, pokers.niu_poker_index[i]);
		}
	}

	void testHasPoker(){
		struct DNPokers pokers;
		EXPECT_FALSE(pokers.HasPoker());
		pokers.poker[0].poker_color = 3;
		pokers.poker[0].poker_value = 2;
		EXPECT_FALSE(pokers.HasPoker());
		pokers.poker[1].poker_color = 2;
		pokers.poker[1].poker_value = 2;
		EXPECT_FALSE(pokers.HasPoker());
		pokers.poker[2].poker_color = 3;
		pokers.poker[2].poker_value = 7;
		EXPECT_FALSE(pokers.HasPoker());
		pokers.poker[3].poker_color = 3;
		pokers.poker[3].poker_value = 12;
		EXPECT_FALSE(pokers.HasPoker());
		pokers.poker[4].poker_color = 3;
		pokers.poker[4].poker_value = 5;
		EXPECT_TRUE(pokers.HasPoker());
	}

	void testSetPoker(){
		struct DNPokers pokers;
		struct DNPoker poker[5];
		for (int i = 0; i < 5; i++){
			poker[i].poker_color = i % 4 + 1;
			poker[i].poker_value = i + 1;
		}
		pokers.SetPoker(poker);
		for (int i = 0; i < 5; i++){
			EXPECT_EQ(i % 4 + 1, pokers.poker[i].poker_color);
			EXPECT_EQ(i + 1, pokers.poker[i].poker_value);
		}
	}

	void testSetNiuPokerIndex(){
		struct DNPokers pokers;
		int32 niuPokerIndex[5];
		for (int i = 0; i < 5; i++){
			niuPokerIndex[i] = i;
		}
		pokers.SetNiuPokerIndex(niuPokerIndex);
		for (int i = 0; i < 5; i++){
			EXPECT_EQ(i, pokers.niu_poker_index[i]);
		}
	}

	void testSetMaxPoker(){
		struct DNPokers pokers;
		struct DNPoker poker;
		poker.poker_color = 1;
		poker.poker_value = 3;
		pokers.SetMaxPoker(&poker);
		EXPECT_EQ(*pokers.max_poker, poker);
	}

	void testIsTypeIdentified(){
		struct DNPokers pokers;
		struct DNPoker poker;
		poker.poker_color = 1;
		poker.poker_value = 3;
		pokers.SetMaxPoker(&poker);
		EXPECT_TRUE(pokers.IsTypeIdentified());
		pokers.max_poker = NULL;
		EXPECT_FALSE(pokers.IsTypeIdentified());
	}
};

TEST_F(DNPokerTest, testConstructor) {
	testConstructor();
}

TEST_F(DNPokerTest, testAssign) {
	testAssign();
}

TEST_F(DNPokerTest, testEqual) {
	testEqual();
}

TEST_F(DNPokerTest, testNotEqual) {
	testNotEqual();
}

TEST_F(DNPokerTest, testReset) {
	testReset();
}

TEST_F(DNPokerTest, testIsNullPoker) {
	testIsNullPoker();
}

TEST_F(DNPokerTest, testFriendlyName) {
	testFriendlyName();
}


TEST(main, testDNPokerValueFirstCmp) {
	testDNPokerValueFirstCmp();
}

TEST(main, testDNPokerColorFirstCmp) {
	testDNPokerColorFirstCmp();
}



TEST_F(CDNPokerTest, testConstructor) {
	testConstructor();
}

TEST_F(CDNPokerTest, testGetPokerNum) {
	testGetPokerNum();
}

TEST_F(CDNPokerTest, testGetMinValue) {
	testGetMinValue();
}

TEST_F(CDNPokerTest, testGetMaxValue) {
	testGetMaxValue();
}

TEST_F(CDNPokerTest, testInitPoker) {
	testInitPoker();
}

TEST_F(CDNPokerTest, testShuffle) {
	testShuffle();
}

TEST_F(CDNPokerTest, testDealPokers) {
	testDealPokers();
}

TEST_F(CDNPokerTest, testFindMaxPoker) {
	testFindMaxPoker();
}

TEST_F(CDNPokerTest, testCompareSinglePoker) {
	testCompareSinglePoker();
}

TEST_F(CDNPokerTest, testComparePokers) {
	testComparePokers();
}

TEST_F(CDNPokerTest, testCompareNiutype) {
	testCompareNiutype();
}

TEST_F(CDNPokerTest, testDN_Switch) {
	testDN_Switch();
}

TEST_F(CDNPokerTest, testGetDNType) {
	testGetDNType();
}

TEST_F(CDNPokerTest, testGetDNTypeToString) {
	testGetDNTypeToString();
}

TEST_F(CDNPokerTest, testHasCow) {
	testHasCow();
}

TEST_F(CDNPokerTest, testFindCow) {
	testFindCow();
}

TEST_F(CDNPokerTest, testChangeDNPokerJQK) {
	testChangeDNPokerJQK();
}

TEST_F(CDNPokerTest, testDNPokerCompare) {
	testDNPokerCompare();
}

TEST_F(DNPokersTest, testConstructor) {
	testConstructor();
}

TEST_F(DNPokersTest, testReset) {
	testReset();
}

TEST_F(DNPokersTest, testHasPoker) {
	testHasPoker();
}

TEST_F(DNPokersTest, testSetPoker) {
	testSetPoker();
}

TEST_F(DNPokersTest, testSetNiuPokerIndex) {
	testSetNiuPokerIndex();
}

TEST_F(DNPokersTest, testSetMaxPoker) {
	testSetMaxPoker();
}

TEST_F(DNPokersTest, testIsTypeIdentified) {
	testIsTypeIdentified();
}



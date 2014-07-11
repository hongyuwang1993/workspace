#include  <gtest/gtest.h>
#include  "DNPoker.h"
#include <string.h>

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
		EXPECT_STREQ("”£ª®5", poker.FriendlyName().c_str());
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
		//≤‚ ‘52’≈≈∆ «∑Ò≤ªœ‡Õ¨
		for (int i = 0; i < 52; i++)
			test[i] = 0;
		for (int i = 0; i < 52; i++){
			test[(cpoker.dn_Poker_[i].poker_color - 1) * 13 + cpoker.dn_Poker_[i].poker_value - 1]++;
		}
		for (int i = 0; i < 52; i++)
			EXPECT_EQ(1, test[i]);
		//≤‚ ‘œ¥≈∆∫Û≈∆ «∑Ò≤ª“ª—˘¡À
		int m = 0;
		for (int i = 0; i < 52; i++){
			if (pokers[i] != cpoker.dn_Poker_[i]){
				m = 1;
				break;
			}
		}
		EXPECT_EQ(1, m);
	}

	void testDNDeal(){
		CDNPoker cpoker;
		struct DNPoker poker[5];
		cpoker.deal_position_ = -1;
		EXPECT_FALSE(cpoker.DNDeal(poker));
		cpoker.deal_position_ = 50;
		EXPECT_FALSE(cpoker.DNDeal(poker)); 
		cpoker.deal_position_ = 0;
		cpoker.DNDeal(poker);
		for (int i = 0; i < 5; i++)
			EXPECT_TRUE(poker[i].poker_color> 0 && poker[i].poker_value > 0);
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
		//≤‚ ‘¡Ω’ﬂ∂º√ª”–≈£
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 5;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 5;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 1;
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
		EXPECT_TRUE(cpoker.ComparePokers(pokers_a, pokers_b));
		pokers_a.Reset();
		pokers_b.Reset();
		//◊Û±ﬂ”–≈££¨”“±ﬂ√ª≈£
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 1;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 2;
		pokers_a.poker[2].poker_color = 1;
		pokers_a.poker[2].poker_value = 7;
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
		pokers_a.Reset();
		pokers_b.Reset();
		//≤‚ ‘◊Û±ﬂ√ª≈££¨”“±ﬂ”–≈£
		pokers_a.poker[0].poker_color = 2;
		pokers_a.poker[0].poker_value = 3;
		pokers_a.poker[1].poker_color = 3;
		pokers_a.poker[1].poker_value = 1;
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
		pokers_b.poker[4].poker_value = 10;
		EXPECT_TRUE(cpoker.ComparePokers(pokers_a, pokers_b));
	
		
	}

	void testCompareNiutype(){
		CDNPoker cpoker;
		EXPECT_EQ(-1, cpoker.CompareNiutype( CDNPoker::MEI_NIU, CDNPoker::WU_HUA_NIU));
		EXPECT_EQ(0, cpoker.CompareNiutype(CDNPoker::MEI_NIU, CDNPoker::MEI_NIU));
		EXPECT_EQ(1, cpoker.CompareNiutype(CDNPoker::WU_XIAO_NIU, CDNPoker::WU_HUA_NIU));
	}

	void testDN_Switch(){
		CDNPoker cpoker;
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.DN_Switch(0));
		EXPECT_EQ(CDNPoker::NIU_DING, cpoker.DN_Switch(1));
		EXPECT_EQ(CDNPoker::NIU_ER, cpoker.DN_Switch(2));
		EXPECT_EQ(CDNPoker::NIU_SAN, cpoker.DN_Switch(3));
		EXPECT_EQ(CDNPoker::NIU_SI, cpoker.DN_Switch(4));
		EXPECT_EQ(CDNPoker::NIU_WU, cpoker.DN_Switch(5));
		EXPECT_EQ(CDNPoker::NIU_LIU, cpoker.DN_Switch(6));
		EXPECT_EQ(CDNPoker::NIU_QI, cpoker.DN_Switch(7));
		EXPECT_EQ(CDNPoker::NIU_BA, cpoker.DN_Switch(8));
		EXPECT_EQ(CDNPoker::NIU_JIU, cpoker.DN_Switch(9));
		EXPECT_EQ(CDNPoker::NIU_NIU, cpoker.DN_Switch(10));
		EXPECT_EQ(CDNPoker::SI_ZHA, cpoker.DN_Switch(11));
		EXPECT_EQ(CDNPoker::WU_HUA_NIU, cpoker.DN_Switch(12));
		EXPECT_EQ(CDNPoker::WU_XIAO_NIU, cpoker.DN_Switch(13));
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.DN_Switch(14));
	}

	void testGetDNType(){
		CDNPoker cpoker;
		EXPECT_EQ("√ª≈£", cpoker.GetDNType(0));
		EXPECT_EQ("≈£∂°", cpoker.GetDNType(1));
		EXPECT_EQ("≈£∂˛", cpoker.GetDNType(2));
		EXPECT_EQ("≈£»˝", cpoker.GetDNType(3));
		EXPECT_EQ("≈£Àƒ", cpoker.GetDNType(4));
		EXPECT_EQ("≈£ŒÂ", cpoker.GetDNType(5));
		EXPECT_EQ("≈£¡˘", cpoker.GetDNType(6));
		EXPECT_EQ("≈£∆ﬂ", cpoker.GetDNType(7));
		EXPECT_EQ("≈£∞À", cpoker.GetDNType(8));
		EXPECT_EQ("≈£æ≈", cpoker.GetDNType(9));
		EXPECT_EQ("≈£≈£", cpoker.GetDNType(10));
		EXPECT_EQ("Àƒ’®", cpoker.GetDNType(11));
		EXPECT_EQ("ŒÂª®≈£", cpoker.GetDNType(12));
		EXPECT_EQ("ŒÂ–°≈£", cpoker.GetDNType(13));
		EXPECT_EQ("√ª≈£", cpoker.GetDNType(14));
	}

	void testGetDNTypeToString(){
		CDNPoker cpoker;
		EXPECT_EQ("mei_niu", cpoker.GetDNTypeToString(CDNPoker::MEI_NIU));
		EXPECT_EQ("niu_ding", cpoker.GetDNTypeToString(CDNPoker::NIU_DING));
		EXPECT_EQ("niu_er", cpoker.GetDNTypeToString(CDNPoker::NIU_ER));
		EXPECT_EQ("niu_san", cpoker.GetDNTypeToString(CDNPoker::NIU_SAN));
		EXPECT_EQ("niu_si", cpoker.GetDNTypeToString(CDNPoker::NIU_SI));
		EXPECT_EQ("niu_wu", cpoker.GetDNTypeToString(CDNPoker::NIU_WU));
		EXPECT_EQ("niu_liu", cpoker.GetDNTypeToString(CDNPoker::NIU_LIU));
		EXPECT_EQ("niu_qi", cpoker.GetDNTypeToString(CDNPoker::NIU_QI));
		EXPECT_EQ("niu_ba", cpoker.GetDNTypeToString(CDNPoker::NIU_BA));
		EXPECT_EQ("niu_jiu", cpoker.GetDNTypeToString(CDNPoker::NIU_JIU));
		EXPECT_EQ("niu_niu", cpoker.GetDNTypeToString(CDNPoker::NIU_NIU));
		EXPECT_EQ("si_zha", cpoker.GetDNTypeToString(CDNPoker::SI_ZHA));
		EXPECT_EQ("wu_hua_niu", cpoker.GetDNTypeToString(CDNPoker::WU_HUA_NIU));
		EXPECT_EQ("wu_xiao_niu", cpoker.GetDNTypeToString(CDNPoker::WU_XIAO_NIU));
		EXPECT_EQ("mei_niu", cpoker.GetDNTypeToString(CDNPoker::MEI_NIU));
	}

	void testHasCow(){
		CDNPoker cpoker;
		DNPoker poker[5];
		//≤‚ ‘5ª®≈£
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
		//≤‚ ‘5–°≈£
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
		//≤‚ ‘4’®
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
		//≤‚ ‘≈£≈£
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
		//≤‚ ‘∆‰À˚≈£–Õ
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
		//∆‰À˚≈£
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
		//≈£≈£
		for (int i = 0; i < 5; i++)
			test[i] = 0;
		poker[0].poker_color = 2;
		poker[0].poker_value = 13;
		poker[1].poker_color = 3;
		poker[1].poker_value = 11;
		poker[2].poker_color = 1;
		poker[2].poker_value = 12;
		poker[3].poker_color = 4;
		poker[3].poker_value = 3;
		poker[4].poker_color = 4;
		poker[4].poker_value = 7;
		EXPECT_EQ(CDNPoker::NIU_NIU, cpoker.FindCow(poker, niuPokerIndex, otherPokerIndex));
		for (int i = 0; i < 3; i++)
			test[niuPokerIndex[i]]++;
		for (int i = 0; i < 2; i++)
			test[otherPokerIndex[i]]++;
		for (int i = 0; i < 5; i++)
			EXPECT_EQ(1, test[i]);
		
		//ŒÂ–°≈£
		for (int i = 0; i < 5; i++)
			test[i] = 0;
		poker[0].poker_color = 2;
		poker[0].poker_value = 1;
		poker[1].poker_color = 3;
		poker[1].poker_value = 1;
		poker[2].poker_color = 1;
		poker[2].poker_value = 1;
		poker[3].poker_color = 4;
		poker[3].poker_value = 2;
		poker[4].poker_color = 4;
		poker[4].poker_value = 2;
		EXPECT_EQ(CDNPoker::WU_XIAO_NIU, cpoker.FindCow(poker, niuPokerIndex, otherPokerIndex));
		
		//ŒÂª®≈£
		for (int i = 0; i < 5; i++)
			test[i] = 0;
		poker[0].poker_color = 2;
		poker[0].poker_value = 13;
		poker[1].poker_color = 3;
		poker[1].poker_value = 11;
		poker[2].poker_color = 1;
		poker[2].poker_value = 12;
		poker[3].poker_color = 4;
		poker[3].poker_value = 13;
		poker[4].poker_color = 4;
		poker[4].poker_value = 11;
		EXPECT_EQ(CDNPoker::WU_HUA_NIU, cpoker.FindCow(poker, niuPokerIndex, otherPokerIndex));
		
		//Àƒ’®
		for (int i = 0; i < 5; i++)
			test[i] = 0;
		poker[0].poker_color = 2;
		poker[0].poker_value = 6;
		poker[1].poker_color = 3;
		poker[1].poker_value = 6;
		poker[2].poker_color = 1;
		poker[2].poker_value = 6;
		poker[3].poker_color = 4;
		poker[3].poker_value = 6;
		poker[4].poker_color = 4;
		poker[4].poker_value = 7;
		EXPECT_EQ(CDNPoker::SI_ZHA, cpoker.FindCow(poker, niuPokerIndex, otherPokerIndex));
		
		//√ª≈£
		for (int i = 0; i < 5; i++)
			test[i] = 0;
		poker[0].poker_color = 2;
		poker[0].poker_value = 13;
		poker[1].poker_color = 3;
		poker[1].poker_value = 11;
		poker[2].poker_color = 1;
		poker[2].poker_value = 5;
		poker[3].poker_color = 4;
		poker[3].poker_value = 3;
		poker[4].poker_color = 4;
		poker[4].poker_value = 4;
		EXPECT_EQ(CDNPoker::MEI_NIU, cpoker.FindCow(poker, niuPokerIndex, otherPokerIndex));
	}

	void testHasCow_CDNPokers(){
		CDNPoker cpoker;
		struct DNPokers pokers;
		struct DNPoker  poker[5];
		int32 pokerIndex[5] = { 0, 1, 2, 3, 4 };
		for (int i = 0; i < 5; i++){
			poker[i].poker_color = i % 4 + 1;
			poker[i].poker_value = i + 1;
		}
		pokers.SetPoker(poker);
		cpoker.HasCow(pokers, pokerIndex);
		EXPECT_EQ(pokers.dn_type, cpoker.HasCow(pokers.poker, pokerIndex));
		for (int i = 0; i < 5; i++){
			EXPECT_EQ(pokers.niu_poker_index[i], pokerIndex[i]);
		}
		EXPECT_EQ(pokers.max_poker, cpoker.FindMaxPoker(pokers.poker));
	}

	void testFindCow_CDNPokers(){
		CDNPoker cpoker;
		struct DNPokers pokers;
		struct DNPoker  poker[5];
		int32 niuPokerIndex[5] = { 0, 1, 2, -1, -1 };
		int32 otherPokerIndex[2] = { 3, 4 };
		for (int i = 0; i < 5; i++){
			poker[i].poker_color = i % 4 + 1;
			poker[i].poker_value = i + 1;
		}
		pokers.SetPoker(poker);
		cpoker.FindCow(pokers, niuPokerIndex, otherPokerIndex);
		EXPECT_EQ(pokers.dn_type, cpoker.FindCow(pokers.poker, niuPokerIndex, otherPokerIndex));
		for (int i = 0; i < 5; i++){
			EXPECT_EQ(pokers.niu_poker_index[i], niuPokerIndex[i]);
		}
		EXPECT_EQ(pokers.max_poker, cpoker.FindMaxPoker(pokers.poker));
		int32 *pniuPokerIndex = NULL;
		int32 *potherPokerIndex = NULL;
		
		cpoker.FindCow(pokers, pniuPokerIndex, potherPokerIndex);
		
		
	}

	void testChangeDNPokerJQK(){
		CDNPoker cpoker;
		EXPECT_EQ(10, cpoker.ChangeDNPokerJQK(13));
		EXPECT_EQ(5, cpoker.ChangeDNPokerJQK(5));
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

	void testDNPokerCompare(){
		CDNPoker cpoker;
		DNPoker poker1, poker2;
		poker1.poker_color = 2;
		poker1.poker_value = 5;
		poker2.poker_color = 2;
		poker2.poker_value = 5;
		EXPECT_EQ(0, cpoker.DNPokerCompare(poker1, poker2));
		poker2.poker_color = 1;
		EXPECT_EQ(1, cpoker.DNPokerCompare(poker1, poker2));
		poker2.poker_color = 3;
		EXPECT_EQ(-1, cpoker.DNPokerCompare(poker1, poker2));
		poker1.poker_value = 9;
		EXPECT_EQ(1, cpoker.DNPokerCompare(poker1, poker2));
		poker1.poker_value = 2;
		EXPECT_EQ(-1, cpoker.DNPokerCompare(poker1, poker2));
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

void testpokerValueIndexPairComparator(){
	std::pair<int32, int32> a = { 2, 3 };
	std::pair<int32, int32> b = { 4, 5 };
	EXPECT_TRUE(pokerValueIndexPairComparator(a, b));
}

void testpokerIndexComparator(){
	int m = 1;
	int n = 2;
	void *a = (void*)&m;
	void *b = (void*)&n;
	EXPECT_EQ(-1, pokerIndexComparator(a, b));
	
}

TEST(main, testpokerValueIndexPairComparator){
	testpokerValueIndexPairComparator();
}

TEST(main, testpokerIndexComparator){
	testpokerIndexComparator();
}


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

TEST_F(CDNPokerTest, testDNDeal) {
	testDNDeal();
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

TEST_F(CDNPokerTest, testHasCow_CDNPokers) {
	testHasCow_CDNPokers();
}

TEST_F(CDNPokerTest, testFindCow_CDNPokers) {
	testFindCow_CDNPokers();
}


TEST_F(CDNPokerTest, testChangeDNPokerJQK) {
	testChangeDNPokerJQK();
}

TEST_F(CDNPokerTest, testDealPokers) {
	testDealPokers();
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



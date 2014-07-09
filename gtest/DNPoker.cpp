#include "DNPoker.h"
#include <assert.h>
#include <stdio.h>
#include <vector>
#include<algorithm>

static bool pokerValueIndexPairComparator(const std::pair<int32, int32> &a, const std::pair<int32, int32> &b) {
	return a.first < b.first;
}

static int pokerIndexComparator(const void *a, const void *b) {
	const int32 *ia = static_cast<const int*>(a);
	const int32 *ib = static_cast<const int*>(b);
	return *ia - *ib;
}

//牌数相同比较花色
bool DNPokerValueFirstCmp(const DNPoker& one, const DNPoker& other) 
{
	int16 diff = one.poker_value - other.poker_value;
	if (0 == diff)
	{
		diff = one.poker_color - other.poker_color;
	}
	return diff < 0;
}

//花色相同比较牌数
bool DNPokerColorFirstCmp (const DNPoker& one, const DNPoker& other) 
{
	int16 diff = one.poker_color - other.poker_color;
	if (0 == diff)
	{
		diff = one.poker_value - other.poker_value;
	}
	return diff < 0;
}

DNPoker & DNPoker::operator=( const DNPoker &d1 )
{
	if (d1.poker_color == this->poker_color && d1.poker_value == this->poker_value)
	{
		return *this;
	}

	this->poker_color = d1.poker_color;
	this->poker_value = d1.poker_value;
	return *this;
}

bool DNPoker::operator==( const DNPoker & other ) const
{
	return (IsNullPoker() && other.IsNullPoker()) || (poker_color == other.poker_color && poker_value == other.poker_value);
}


bool DNPoker::operator!=( const DNPoker & other ) const
{
	return !(*this == other);
}
 
bool DNPoker::IsNullPoker() const
{
	return (poker_value==0||poker_color==0);
}

std::string DNPoker::FriendlyName() const
{
	static char * color_names[] = { NULL, "方块", "樱花", "红桃", "黑桃" };
	static char * value_names[] = { NULL, "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	char name[16] = { 0 };
	if ((poker_color ==0)||(poker_color > 4)||(poker_value == 0)||(poker_value > 13))
	{
		snprintf(name, sizeof(name), "%s", "invalid_poker");	
	}
	else
	{
		snprintf(name, sizeof(name), "%s%s", color_names[poker_color], value_names[poker_value]);
	}
	return std::string(name);
}

void DNPoker::Reset()
{
	poker_value = 0;
	poker_color = 0;
}

CDNPoker::CDNPoker() : poker_num_(0), poker_min_value_(0), poker_max_value_(0), deal_position_(0)
{
	InitPoker(MIN_DNPOKER_VALUE, MAX_DNPOKER_VALUE);
}


CDNPoker::~CDNPoker()
{

}

void CDNPoker::InitPoker(BYTE minPoker, BYTE maxPoker)
{
	poker_num_ = 0;
	deal_position_ = 0;
	poker_min_value_ = 0;
	poker_max_value_ = 0;

	assert(minPoker <= maxPoker);

	int poker_count_color = maxPoker - minPoker + 1;
	int total_poker_count = DNPOKER_COLOR_COUNT * poker_count_color;

	for (int i=0; i<total_poker_count; ++i)
	{
		BYTE byValue = (i % poker_count_color) + minPoker;
		BYTE byColor = (i / poker_count_color) + 1;

		dn_Poker_[poker_num_].poker_value = byValue;
		dn_Poker_[poker_num_].poker_color = byColor;

		++poker_num_;
	}

	poker_min_value_ = minPoker;
	poker_max_value_ = maxPoker;

	return;
}
//洗牌函数
void CDNPoker::Shuffle(int16 iTimes)
{
	static int x = 0;

	for (int iT=0; iT<iTimes; ++iT)
	{
		int iValue = 0;
		DNPoker median;

		for(int index = 0; index < GetPokerNum(); index ++)
		{
			if (x > 1000000)
			{
				x = 0;
			}
			x+=10000;

			iValue = index + rand() % (GetPokerNum() - index);
			//index位置的牌和iValue位置的牌交换
			median = dn_Poker_[index];
			dn_Poker_[index] = dn_Poker_[iValue];
			dn_Poker_[iValue] = median;
		}
	}

	deal_position_ = 0;

	return;
}

bool CDNPoker::DNDeal(DNPoker* poker)
{
	if (deal_position_ < 0 || deal_position_ > GetPokerNum()-5)
	{
		return false;		
	}

	poker[0] = dn_Poker_[deal_position_++];
	poker[1] = dn_Poker_[deal_position_++];
	poker[2] = dn_Poker_[deal_position_++];
	poker[3] = dn_Poker_[deal_position_++];
	poker[4] = dn_Poker_[deal_position_++];;

	return true;
}

DNPoker * CDNPoker::FindMaxPoker(DNPoker poker[5])
{
	DNPoker * max_poker = &poker[0];
	for (int i = 1; i < 5; i++)
	{
		DNPoker * current_poker = &poker[i];

		if ((max_poker->poker_value < current_poker->poker_value) ||
			(max_poker->poker_value == current_poker->poker_value && max_poker->poker_color < poker[i].poker_color)
			)
		{
			max_poker = &poker[i];
		}
	}

	return max_poker;
}

bool CDNPoker::CompareSinglePoker(DNPoker* poker_a, DNPoker* poker_b)
{
	if (poker_a->poker_value == poker_b->poker_value) {
		return poker_a->poker_color > poker_b->poker_color;
	} else {
		return poker_a->poker_value > poker_b->poker_value;
	}
}


bool CDNPoker::ComparePokers(DNPokers & poker_a, DNPokers & poker_b) {
	if (poker_a.IsTypeIdentified() == false) {
		CDNPoker::FindCow(poker_a, NULL, NULL);
	}
	if (poker_b.IsTypeIdentified() == false) {
		CDNPoker::FindCow(poker_b, NULL, NULL);
	}

	bool a_lose = false;

	//比较牛型，如果牛型相同，比较最大的手牌大小，直到花色
	int ret = CompareNiutype(poker_a.dn_type, poker_b.dn_type);
	if (ret == 0)
	{
		//从5张牌中找到最大的牌,判断.左小于右边
		if (!CompareSinglePoker(poker_a.max_poker, poker_b.max_poker))
		{
			a_lose = true;
		}
	}
	else if (ret == -1)
	{
		a_lose = true;
	}

	return a_lose;
}

/** 
 ** -1 when a < b; 1 when a > b; otherwise 0.
 */
int CDNPoker::CompareNiutype(CDNPoker::DN_TYPE a_niu_type, CDNPoker::DN_TYPE b_niu_type)
{
	//比较牛型
	if (a_niu_type < b_niu_type)
	{
		//庄输,闲胜
		return -1;
	}
	else if (a_niu_type == b_niu_type)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}


CDNPoker::DN_TYPE CDNPoker::FindCow(DNPoker poker[5], int32 niuPokerIndex[5], int32 otherPokerIndex[2]) 
{
	static const int32 all_niu_poker_index[5] = {0, 1, 2, 3, 4};

	int wuxiao_num = 0;
	int wuxiao_sum = 0;
	int wuhua_num = 0;
	
	int all_poker_sum = 0;

	//判断是否为五小牛、五花牛
	for (int i = 0; i < 5; ++i)
	{
		all_poker_sum += ChangeDNPokerJQK(poker[i].poker_value);

		if (poker[i].poker_value < 5)
		{
			++wuxiao_num;
			wuxiao_sum += poker[i].poker_value;
		} else if (poker[i].poker_value > 10) {
			++wuhua_num;
		}
	}

	if ((wuxiao_num == 5)&&(wuxiao_sum <= 10)) {
		// 判断是否为五小牛
		memcpy(niuPokerIndex, all_niu_poker_index, sizeof(int32)*5);
		return CDNPoker::WU_XIAO_NIU;

	} else if (wuhua_num == 5) {
		//判断是否为五花牛
		memcpy(niuPokerIndex, all_niu_poker_index, sizeof(int32)*5);
		return CDNPoker::WU_HUA_NIU;
	}

	//判断是否为四炸
	std::vector<std::pair<int32, int32> > sorted_pokers;
	for (int i=0;i<5;i++) {
		sorted_pokers.push_back(std::pair<int32, int32>(poker[i].poker_value, i));
	}

	std::sort(sorted_pokers.begin(), sorted_pokers.end(), pokerValueIndexPairComparator);

	int si_zha_count = 0;
	for (int i=1; i<5; i++)
	{
		std::pair<int32, int32> & curPair = sorted_pokers[i];
		if (sorted_pokers[i-1].first == curPair.first) {
			niuPokerIndex[si_zha_count] = curPair.second;
			si_zha_count++;

			if (si_zha_count == 3) {
				return CDNPoker::SI_ZHA;
			}
		} else {
			if (i >= 2) {
				// Fast quit.
				break;
			}
			si_zha_count = 0;
			otherPokerIndex[0] = curPair.second;
		}
	}

	CDNPoker::DN_TYPE type = MEI_NIU;
	int nSum = 0;
	int i = 0, j = 0, k = 0;
	for(i = 0; i < 5; ++ i)
	{
		for(j = i + 1; j < 5; ++ j)
		{
			for(k = j + 1; k < 5; ++ k)
			{
				nSum = ChangeDNPokerJQK(poker[i].poker_value) + ChangeDNPokerJQK(poker[j].poker_value) + ChangeDNPokerJQK(poker[k].poker_value);

				if(nSum % 10 == 0)
				{
					niuPokerIndex[0] = i;
					niuPokerIndex[1] = j;
					niuPokerIndex[2] = k;
					
					// OtherPokerIndex.
					qsort(niuPokerIndex, 3, sizeof(int32), pokerIndexComparator);
					if (niuPokerIndex[0] == 2) {
						otherPokerIndex[0] = 0;
						otherPokerIndex[1] = 1;
					} else {
						int otherPokerIndex_index = 0;
						for (int i=1; i<3; i++) {
							int delta = niuPokerIndex[i] - niuPokerIndex[i-1];
							for (int z=1;z<delta;z++) {
								otherPokerIndex[otherPokerIndex_index++] = niuPokerIndex[i-1] + z;
							}
							if (otherPokerIndex_index == 2) {
								break;
							}
						}
						if (niuPokerIndex[0] == 1) {
							otherPokerIndex[1] = 0;
						}
					}

					int32 type = all_poker_sum % 10;
					if (type == 0) {
						type = CDNPoker::NIU_NIU;
					}
					return (CDNPoker::DN_TYPE)type;
				}
			}
		}
	}
	return CDNPoker::MEI_NIU;
}

CDNPoker::DN_TYPE CDNPoker::HasCow(DNPoker poker[5], int32 pokerIndex[5])
{
	CDNPoker::DN_TYPE type = MEI_NIU;

	// TODO(fbzhong): Dupe check in PokerIndex.
	int pokerIndexCount = 0;
	for (int i=0;i<5;i++) {
		if (pokerIndex[i] >= 0 && pokerIndex[i] < 5) {
			pokerIndexCount++;
		} else {
			break;
		}
	}

	if (pokerIndexCount == 5) {
		// 特殊牌型：五花牛、五小牛

		//判断是否为五小牛
		int wuxiao_num = 0;
		int wuxiao_snum = 0;
		for (int i = 0; i < 5; ++i)
		{
			if (poker[i].poker_value < 5)
			{
				++wuxiao_num;
				wuxiao_snum = wuxiao_snum + poker[i].poker_value;
			}
		}

		if ((wuxiao_num == 5)&& (wuxiao_snum <= 10))
		{
			return CDNPoker::WU_XIAO_NIU;
		}

		//判断是否为五花牛
		int wuhua_num = 0;
		for (int i = 0; i < 5; ++i)
		{
			if (poker[i].poker_value > 10)
			{
				++wuhua_num;
			}
		}

		if (wuhua_num == 5) {
			return CDNPoker::WU_HUA_NIU;
		}
	} else if (pokerIndexCount == 4) {
		//判断是否为四炸
		for (int i = 1; i< pokerIndexCount; i++)
		{
			if (poker[pokerIndex[i]].poker_value != poker[pokerIndex[0]].poker_value) {
				return CDNPoker::MEI_NIU;
			}
		}
		return CDNPoker::SI_ZHA;
	} else if (pokerIndexCount == 3) {
		int nSum = 0;
		int totalSum = 0;

		for (int i=0; i<5; i++) {
			totalSum += ChangeDNPokerJQK(poker[i].poker_value);
		}

		for (int i=0; i<pokerIndexCount; i++) {
			nSum += ChangeDNPokerJQK(poker[pokerIndex[i]].poker_value);
		}

		if(nSum % 10 == 0)
		{
			int s = totalSum % 10;

			if (s == 0) {
				return CDNPoker::NIU_NIU;
			} else {
				return (CDNPoker::DN_TYPE)s;
			}
		}
	}

	return CDNPoker::MEI_NIU;
}

void CDNPoker::HasCow(DNPokers &pokers, int32 pokerIndex[5]) {
	pokers.dn_type = HasCow(pokers.poker, pokerIndex);
	pokers.SetNiuPokerIndex(pokerIndex);
	pokers.SetMaxPoker(FindMaxPoker(pokers.poker));
}

void CDNPoker::FindCow(DNPokers &pokers, int32 niuPokerIndex[5], int32 otherPokerIndex[2]) {
	int32 n_index[5] = {-1, -1, -1, -1, -1};
	int32 o_index[2] = {-1, -1};

	if (niuPokerIndex == NULL) {
		niuPokerIndex = n_index;
	}
	if (otherPokerIndex == NULL) {
		otherPokerIndex = o_index;
	}

	pokers.dn_type = FindCow(pokers.poker, niuPokerIndex, otherPokerIndex);
	pokers.SetNiuPokerIndex(niuPokerIndex);
	pokers.SetMaxPoker(FindMaxPoker(pokers.poker));
}

int32 CDNPoker::ChangeDNPokerJQK(const BYTE& pokerValue)
{
	if (pokerValue>10)
	{
		return 10;
	}
	return pokerValue;
}

CDNPoker::DN_TYPE CDNPoker::DN_Switch(const int32& tType)
{
	DN_TYPE type = MEI_NIU;
	switch(tType)
	{
	case 0:
		type = MEI_NIU;
		break;
	case 1:
		type = NIU_DING;
		break;
	case 2:
		type = NIU_ER;
		break;
	case 3:
		type = NIU_SAN;
		break;
	case 4:
		type = NIU_SI;
		break;
	case 5:
		type = NIU_WU;
		break;
	case 6:
		type = NIU_LIU;
		break;
	case 7:
		type = NIU_QI;
		break;
	case 8:
		type = NIU_BA;
		break;
	case 9:
		type = NIU_JIU;
		break;
	case 10:
		type = NIU_NIU;
		break;
	case 11:
		type = SI_ZHA;
		break;
	case 12:
		type = WU_HUA_NIU;
		break;
	case 13:
		type = WU_XIAO_NIU;
		break;
	default:
		type = MEI_NIU;
		break;
	}
	return type;
}


std::string CDNPoker::GetDNType(const int16& tType)
{
	std::string type = "没牛";
	switch(tType)
	{
	case 0:
		type = "没牛";
		break;
	case 1:
		type = "牛丁";
		break;
	case 2:
		type = "牛二";
		break;
	case 3:
		type = "牛三";
		break;
	case 4:
		type = "牛四";
		break;
	case 5:
		type = "牛五";
		break;
	case 6:
		type = "牛六";
		break;
	case 7:
		type = "牛七";
		break;
	case 8:
		type = "牛八";
		break;
	case 9:
		type = "牛九";
		break;
	case 10:
		type = "牛牛";
		break;
	case 11:
		type = "四炸";
		break;
	case 12:
		type = "五花牛";
		break;
	case 13:
		type = "五小牛";
		break;
	default:
		type = "没牛";
		break;
	}
	return type;
}

std::string CDNPoker::GetDNTypeToString(CDNPoker::DN_TYPE tType)
{
	std::string type = "mei_niu";
	switch(tType)
	{
		case CDNPoker::NIU_DING:
				type = "niu_ding";
				break;
		case CDNPoker::NIU_ER:
				type = "niu_er";
				break;
		case CDNPoker::NIU_SAN:
				type = "niu_san";
				break;
		case CDNPoker::NIU_SI:
				type = "niu_si";
				break;
		case CDNPoker::NIU_WU:
				type = "niu_wu";
				break;
		case CDNPoker::NIU_LIU:
				type = "niu_liu";
				break;
		case CDNPoker::NIU_QI:
				type = "niu_qi";
				break;
		case CDNPoker::NIU_BA:
				type = "niu_ba";
				break;
		case CDNPoker::NIU_JIU:
				type = "niu_jiu";
				break;
		case CDNPoker::NIU_NIU:
				type = "niu_niu";
				break;
		case CDNPoker::SI_ZHA:
				type = "si_zha";
				break;
		case CDNPoker::WU_HUA_NIU:
				type = "wu_hua_niu";
				break;
		case CDNPoker::WU_XIAO_NIU:
				type = "wu_xiao_niu";
				break;
		default:
				type = "mei_niu";
				break;
	}
	return type;
}

int32 CDNPoker::DNPokerCompare(DNPoker& pokerA,DNPoker& pokerB)
{
	if (pokerA.poker_value == pokerB.poker_value)
	{
		if (pokerA.poker_color == pokerB.poker_color)//错误
		{
			return 0;
		}
		else if (pokerA.poker_color > pokerB.poker_color)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else if (pokerA.poker_value > pokerB.poker_value)
	{
		return 1;
	}
	else if (pokerA.poker_value < pokerB.poker_value)
	{
		return -1;
	}

	return 0;
}

bool CDNPoker::DealPokers(DNPoker * poker[], int32 playerNumber) 
{

	for (int i=0; i<playerNumber; i++) 
	{
		DNDeal(poker[i]);
	}

	return true;
}
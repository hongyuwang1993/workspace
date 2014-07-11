#ifndef SOURCE_GAMEBASE_DNPOKER_H_
#define SOURCE_GAMEBASE_DNPOKER_H_
#if _MSC_VER
#define snprintf _snprintf
#endif
#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include  <string.h>


#define MAX_DNPOKER_COUNT 52	// È¥µô´óÐ¡Íõ Joker
#define MIN_DNPOKER_VALUE 1		//A
#define MAX_DNPOKER_VALUE 13   //K
#define DNPOKER_COLOR_COUNT 4

#define int8 char
#define int16 short
#define int32 int
#define int64 long long
#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned long long

#define BYTE unsigned char

 bool pokerValueIndexPairComparator(const std::pair<int32, int32>& a, const std::pair<int32, int32>& b);
 int pokerIndexComparator(const void *, const void *);

enum DNPokerColor
{
	DN_POKER_COLOR_DIAMONDS = 1,	 //·½¿é
	DN_POKER_COLOR_CLUBS = 2,		//Ó£»¨
	DN_POKER_COLOR_HEARTS = 3,		//ºìÌÒ
	DN_POKER_COLOR_SPADES = 4,		//ºÚÌÒ
};

struct DNPoker
{
	BYTE poker_value;
	BYTE poker_color;

	DNPoker() : poker_color(0),poker_value(0)
	{ }

	DNPoker& operator=(const DNPoker& poker);

	bool operator==(const DNPoker& otherPoker) const;

	bool operator!=(const DNPoker& poker) const;

	void Reset();

	bool IsNullPoker() const;

	std::string FriendlyName() const;
};

bool DNPokerValueFirstCmp(const DNPoker& one,const DNPoker& other);

bool DNPokerColorFirstCmp(const DNPoker& one,const DNPoker& other);

struct DNPokers;

class CDNPoker
{
	friend class CDNPokerTest;
public:
	CDNPoker();
	~CDNPoker();

#define DN_NOBRAND -1 // ¿ÕÊÖÅÆ

	enum DN_TYPE
	{
		MEI_NIU = 0,	//Ã»Å£
		NIU_DING = 1, //Å£¶¡
		NIU_ER = 2,	//Å£¶þ
		NIU_SAN = 3, //Å£Èý
		NIU_SI = 4,	//Å£ËÄ
		NIU_WU = 5,	//Å£Îå
		NIU_LIU = 6, //Å£Áù		
		NIU_QI = 7, //Å£Æß
		NIU_BA = 8,	//Å£°Ë
		NIU_JIU = 9, //Å£¾Å
		NIU_NIU = 10,	//Å£Å£

		SI_ZHA,			//ËÄÕ¨
		WU_HUA_NIU,		//Îå»¨Å£
		WU_XIAO_NIU,		//ÎåÐ¡Å£		
		
		DN_TYPE_COUNT,	// place holder.
	};
	 
	int32 GetPokerNum()
	{
		return poker_num_;
	}

	inline BYTE GetMinValue()
	{
		return poker_min_value_;
	} 

	inline BYTE GetMaxValue()
	{
		return poker_max_value_;
	}

	void InitPoker(BYTE minPoker,BYTE maxPoker);

	void Shuffle(int16 iTimes=1);

	bool DNDeal(DNPoker* poker);

	static DNPoker * FindMaxPoker(DNPoker poker[5]);

	static bool CompareSinglePoker(DNPoker* poker_a, DNPoker* poker_b);

	//static bool CompareMaxNiutype(DNPoker* poker_a, DNPoker* poker_b);

	static bool ComparePokers(DNPokers & poker_a, DNPokers & poker_b);//no...
	/** 
	 ** -1 when a < b; 1 when a > b; otherwise 0.
	 */
	static int32 CompareNiutype(CDNPoker::DN_TYPE a_niu_type, CDNPoker::DN_TYPE b_niu_type);

	//static DN_TYPE GetDNType(DNPoker poker[5],int32 pokerIndex[], int32 pokerIndexSize);

	static DN_TYPE DN_Switch(const int32& type);
	
	static std::string GetDNType(const int16& tType);
	

	static std::string GetDNTypeToString(CDNPoker::DN_TYPE tType);

	//	static bool HasCow(DNPoker* poker,int32* pokerIndex , int32 count);
	static DN_TYPE HasCow(DNPoker poker[5],int32 pokerIndex[5]);

	static DN_TYPE FindCow(DNPoker poker[5], int32 niuPokerIndex[5], int32 otherPokerIndex[2]);

	static int32 ChangeDNPokerJQK(const BYTE& pokerValue);

	//bool DealPokers(DNPoker** poker, int16 playerNumber);

	static void HasCow(DNPokers &pokers, int32 pokerIndex[5]);//no...
	static void FindCow(DNPokers &pokers, int32 niuPokerIndex[5], int32 otherPokerIndex[2]);//no...

	bool DealPokers(DNPoker * poker[], int32 playerNumber);
private:
	int32 DNPokerCompare(DNPoker& pokerA,DNPoker& pokerB);

public:
	int32 poker_num_;
	int32 deal_position_;

	DNPoker dn_Poker_[MAX_DNPOKER_COUNT];

	BYTE poker_min_value_;
	BYTE poker_max_value_;
};


struct DNPokers
{
	DNPoker poker[5];
	CDNPoker::DN_TYPE dn_type;
	CDNPoker::DN_TYPE dn_player_select_type;
	DNPoker * max_poker;
	int32 niu_poker_index[5];

	DNPokers() : dn_type(CDNPoker::MEI_NIU)
		, dn_player_select_type(CDNPoker::MEI_NIU)
		, max_poker(NULL) {
			Reset();
	}

	void Reset() {
		for (int i=0; i<sizeof(poker)/sizeof(poker[0]); i++) {
			poker[i].Reset();
			niu_poker_index[i] = -1;
		}
		max_poker = NULL;
		dn_type = CDNPoker::MEI_NIU;
		dn_player_select_type = CDNPoker::MEI_NIU;
	}

	bool HasPoker()
	{
		return !(poker[0].IsNullPoker() || poker[1].IsNullPoker() || poker[2].IsNullPoker()|| poker[3].IsNullPoker()|| poker[4].IsNullPoker());
	}

	void SetPoker( DNPoker newPokers[5] ) 
	{
		memcpy(poker, newPokers, sizeof(DNPoker) * 5);
	}

	void SetNiuPokerIndex(int32 niuPokerIndex[5]) {
		memcpy(niu_poker_index, niuPokerIndex, sizeof(int32)*5);
	}

	void SetMaxPoker(DNPoker * p) {
		max_poker = p;
	}

	bool IsTypeIdentified() {
		return max_poker != NULL;
	}
};

#endif  // SOURCE_GAMEBASE_DNPOKER_H_

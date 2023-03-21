#pragma once

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "ChartDB.h"

#define DATA_BASESTAT_MAX	1
#define DATA_CLASSSTAT_MAX	6
#define DATA_RACESTAT_MAX	6
#define DATA_RACE_MAX	256

#define DATA_FACTOR_MAX	35
#define DATA_RESULT_MAX	41
#define DATA_ENABLEITEM_MAX	19

#define DATA_STATPOINT		6

#define _BAL_LEVELMAX	125
#define _BAL_VIEWLEVELMAX	(_BAL_LEVELMAX-25)

#define DATA_CHARSKILL_MAX		120

#define _STATFILE_VER	0.13

#define _HP_POTION	200

class CStat
{
	// Constructor, Destructor & private initializer
	public:
		CStat();
		~CStat();

	private :

	public:
		void Init(void);
		BOOL Save(FILE *);
		BOOL Load(FILE *);
		void CalcTotal(void);

		// Set
		void SetId(int i) { mId = i; };
		void SetStat(int i, char c=0) { mStatus[c] = i; };
		void SetStr(int i) { mStatus[0] = i; };
		void SetDex(int i) { mStatus[1] = i; };
		void SetCon(int i) { mStatus[2] = i; };
		void SetInt(int i) { mStatus[3] = i; };
		void SetWis(int i) { mStatus[4] = i; };
		void SetMen(int i) { mStatus[5] = i; };
		void SetTotal(int i) { mStatus[6] = i; };
		void SetName(char *ch) { strcpy(mName, ch); };
		void SetRange(WORD w, char c=0) { mRange[c] = w; };
		void SetUseItem(char c) { mUseItem = c; };
		void SetUseItemArmor(char c) { mUseItemArmor = c; };
		void SetSpeed(double f) { mfSpeed = f; };

		// Report Interfaces
		int GetId(void) { return mId; };
		int GetStat(char c=0) { return mStatus[c]; };
		int GetStr(void) { return mStatus[0]; };
		int GetDex(void) { return mStatus[1]; };
		int GetCon(void) { return mStatus[2]; };
		int GetInt(void) { return mStatus[3]; };
		int GetWis(void) { return mStatus[4]; };
		int GetMen(void) { return mStatus[5]; };
		int GetTotal(void) { return mStatus[6]; };
		char * GetName(void) { return mName; };
		WORD GetRange(char c=0) { return mRange[c]; };
		char GetUseItem(void) { return mUseItem; };
		char GetUseItemArmor(void) { return mUseItemArmor; };
		double GetSpeed(void) { return mfSpeed; };

	// Attributes
	protected:
		int mId;
		int	mStatus[7];
		char mName[_MAX_FNAME];
		WORD mRange[8];
		char mUseItem;
		char mUseItemArmor;
		double mfSpeed;
};
typedef CStat* LPStat;

//	�����Ÿ�
#define STAT_RANGE_MIN		0
#define STAT_RANGE_MAX		1
#define STAT_RRANGE_MIN		2
#define STAT_RRANGE_MAX		3
#define STAT_MRANGE_MIN		4
#define STAT_MRANGE_MAX		5
#define STAT_MRRANGE_MIN	6
#define STAT_MRRANGE_MAX	7

class CFormula
{
	// Constructor, Destructor & private initializer
	public:
		CFormula();
		~CFormula();

	private :

	public:
		BOOL Save(FILE *);
		BOOL Load(FILE *);

		// Set
		void SetId(int i) { mId = i; };
		void SetName(char *ch) { strcpy(mName, ch); };
		void SetInit(int i) { mInit = i; };
		void SetX(double d) { mRateX = d; };
		void SetY(double d) { mRateY = d; };

		// Report Interfaces
		int GetId(void) { return mId; };
		char * GetName(void) { return mName; };
		int GetInit(void) { return mInit; };
		double GetX(void) { return mRateX; };
		double GetY(void) { return mRateY; };

	// Attributes
	protected:
		int mId;
		char mName[50];
		int mInit;
		double mRateX;
		double mRateY;
};
typedef CFormula* LPFormula;

class CFactor
{
	// Constructor, Destructor & private initializer
	public:
		CFactor();
		~CFactor();

	private :

	public:
		// Set
		void SetData(double d, char c=0) { mData[c] = d; };
		void SetResultData(double d, char c=0) { mResultData[c] = d; };

		// Report Interfaces
		double GetData(char c=0) { return mData[c]; };
		int GetDataInt(char c=0) { return int(mData[c]); };
		double GetResultData(char c=0) { return mResultData[c]; };
		int GetResultDataInt(char c=0) { return int(mResultData[c]); };

	// Attributes
	protected:
		double mData[DATA_FACTOR_MAX];
		double mResultData[DATA_RESULT_MAX];
};
typedef CFactor* LPFactor;

//	mData�� ����Ǵ� �ڷ��� ����
#define DATA_ATTACKPOINT		0	//�������ݷ�
#define DATA_WEIGHT				1	//��������
#define DATA_RANGEATTACKPOINT	2	//���Ÿ����ݷ�
#define DATA_SPEED				3	//�Ϲݰ��ݼӵ�
#define DATA_ATACKGRADE			4	//���ݵ��
#define DATA_DEFENSEGRADE		5	//�����
#define DATA_CRITICALRATIO		6	//����ġ��Ȯ��
#define DATA_HP					7	//�����
#define DATA_HPRECOVERY			8	//����� ȸ����
#define DATA_PHYSICALRESIST		9	//������������
#define DATA_CRITICALMAX		10	//��չ���ġ���ִ�
#define DATA_ITEMDEFENSE		11	//������ ��������
#define DATA_MAGICATTACKPOINT	12	//�������ݷ�
#define DATA_CURSERATIO			13	//���ּ�����
#define DATA_MAGICRATTACKPOINT	14	//�������Ÿ����ݷ�
#define DATA_MAGICSPEED			15	//���������ӵ�
#define DATA_MAGICRATIO			16	//����������
#define DATA_MAGICCRITICALRATIO	17	//����ġ��Ȯ��
#define DATA_MP					18	//���ŷ�
#define DATA_MPRECOVERY			19	//���ŷ� ȸ����
#define DATA_MAGICRESIST		20	//������������
#define DATA_MAGICCRITICALMAX	21	//��ո���ġ���ִ�
#define DATA_ITEMMAGICDEFENSE	22	//������ ��������
#define DATA_CLASSNUMBER		23	//���� ��ȣ
#define DATA_LEVEL				24	//����
#define DATA_ITEM_AP			25	//������ ���� ���ݷ�
#define DATA_ITEM_MAP			26	//������ ���� ���ݷ�
#define DATA_ITEM_RAP			27	//������ ���� ���Ÿ� ���ݷ�
#define DATA_ITEM_MRAP			28	//������ ���� ���Ÿ� ���ݷ�
#define DATA_ITEM_SP			29	//���� �⺻ ������ �ӵ�����
#define DATA_ITEM_RSP			30	//���� ���Ÿ� ������ �ӵ�����
#define DATA_ITEM_MSP			31	//���� �⺻ ������ �ӵ�����
#define DATA_ITEM_MRSP			32	//���� ���Ÿ� ������ �ӵ�����
#define DATA_CREATURE_AP_SEC	33	//��ȯ���� �ʴ� ���� ���ݷ�
#define DATA_RACENUMBER			34	//���� ��ȣ

//	mResultData�� ����Ǵ� �ڷ��� ����
#define RDATA_CRITCAL_AP_SEC				0	//�ʴ繰�����ݷ�(ġ��)
#define RDATA_AP_SEC						1	//�ʴ繰�����ݷ�
#define RDATA_DAMAGE_SEC					2	//�ʴ繰��������
#define RDATA_ATTACK_COUNT					3	//��չ�������Ƚ��
#define RDATA_CRITCAL_RAP_SEC				4	//�ʴ���Ÿ����ݷ�(ġ��)
#define RDATA_RAP_SEC						5	//�ʴ���Ÿ����ݷ�
#define RDATA_RDAMAGE_SEC					6	//�ʴ���Ÿ�������
#define RDATA_RATTACK_COUNT					7	//��տ��Ÿ�����Ƚ��
#define RDATA_CRITCAL_MAP_SEC				8	//�ʴ縶�����ݷ�(ġ��)
#define RDATA_MAP_SEC						9	//�ʴ縶�����ݷ�
#define RDATA_MDAMAGE_SEC					10	//�ʴ縶��������
#define RDATA_MATTACK_COUNT					11	//��ո�������Ƚ��
#define RDATA_CRITCAL_MRAP_SEC				12	//�ʴ縶�����Ÿ����ݷ�(ġ��)
#define RDATA_MRAP_SEC						13	//�ʴ縶�����Ÿ����ݷ�
#define RDATA_MRDAMAGE_SEC					14	//�ʴ縶�����Ÿ�������
#define RDATA_MRATTACK_COUNT				15	//��ո������Ÿ�����Ƚ��
#define RDATA_HPMAX_RECOVERY_TIME			16	//��HPȸ���ð�
#define RDATA_MPMAX_RECOVERY_TIME			17	//��MPȸ���ð�
#define RDATA_MIN_ATTACKCOUNT				18	//�ּҰ���Ƚ��
#define RDATA_ATTACK_TYPE					19	//���� Ÿ��	0:����	1:���Ÿ�	2:	����	3: ���� ���Ÿ�
#define RDATA_ND_RATTACKCOUNT				20	//������ ���Ÿ� ���� Ƚ��
#define RDATA_ND_MATTACKCOUNT				21	//������ ���� ���� Ƚ��
#define RDATA_ND_MRATTACKCOUNT				22	//������ ���� ���Ÿ� ���� Ƚ��
#define RDATA_D_RATTACKCOUNT				23	//���ٽ� ���� ���Ÿ� ���� Ƚ��
#define RDATA_FA_TYPE						24	//�ļ� ���� Ÿ��	0:����	1:���Ÿ�	2:	����	3: ���� ���Ÿ�
#define RDATA_FA_COUNT						25	//�ļ� ���� Ƚ��
#define RDATA_WIN_ATTACK_COUNT				26	//�¸� �� ���� Ƚ��
#define RDATA_WIN_RESULT					27	//����	0:�¸�	1:�й�
#define RDATA_REAL_FA_COUNT					28	//�� �ļ� ���� Ƚ��
#define RDATA_REAL_ATTACK_COUNT				29	//�� �� ���� Ƚ��
#define RDATA_COMBAT_DAMAGE					30	//������ ���� ����
#define RDATA_REMAIN_HP						31	//���� HP
#define RDATA_HP_RECOVERY_TIME				32	//HP ȸ�� �ð�
#define RDATA_COMBAT_TIME					33	//���� �ҿ� �ð�
#define RDATA_CONTINUOUS_WIN_COUNT			34	//���� �¸� Ƚ��
#define RDATA_CONTINUOUS_REMAIN_HP			35	//���� ���� �� ���� HP
#define RDATA_CONTINUOUS_HP_RECOVERY_TIME	36	//���� ���� HP ȸ�� �ð�
#define RDATA_CONTINUOUS_COMBAT_TIME		37	//���� �� ���� �ð�
#define RDATA_ONE_COMBAT_TIME				38	//�� ���� ��� �ҿ� �ð�
#define RDATA_DEBUF_RATIO					39	//���� ����� ������
#define RDATA_MDEBUF_RATIO					40	//���� ����� ������

class CCharSkill
{
	// Constructor, Destructor & private initializer
	public:
		CCharSkill();
		~CCharSkill();

	private :

	public:
		// Set
		void SetSkillID(char dclass, int skillnum, WORD skillid) { mSkillID[dclass][skillnum] = skillid; };
		void SetEnableItem(DWORD d, char dclass=0) { mEnableItem[dclass] = d; };
		void EnableItemSetBit(BYTE b, char dclass=0) { mEnableItem[dclass] = mEnableItem[dclass]+(1<<(b-1)); };
		void EnableItemResetBit(BYTE b, char dclass=0) { mEnableItem[dclass] = mEnableItem[dclass]-(1<<(b-1)); };
		void SetIsSummon(BYTE b, char dclass=0) { mbIsSummmon[dclass]=b; };

		// Report Interfaces
		WORD GetSkillID(char dclass, int skillnum) { return mSkillID[dclass][skillnum]; };
		DWORD GetEnableItem(char dclass=0) { return mEnableItem[dclass]; };
		BYTE IsEnableItem(int b, char dclass=0) { return (BYTE)((mEnableItem[dclass]&(1<<(b-1)))>>(b-1)); };
		BYTE IsSummon(char dclass=0) { return mbIsSummmon[dclass]; };

	// Attributes
	protected:
		WORD mSkillID[DATA_CLASSSTAT_MAX][DATA_CHARSKILL_MAX];
		DWORD mEnableItem[DATA_CLASSSTAT_MAX];
		BYTE mbIsSummmon[DATA_CLASSSTAT_MAX];
};
typedef CCharSkill* LPCharSkill;
//	mEnableItem�� ����Ǵ� �ڷ��� ���� ��Ʈ ���� 
//	1	�Ѽհ�
//	2	������
//	3	�μհ�
//	4	��ũ��
//	5	����
//	6	Ȱ
//	7	����
//	8	��������
//	9	����������
//	10	�ݰ���
//	11	�ݰ���
//	12	����
//	13	�Ǻ�
//	14	����
//	15	�氡��
//	16	�߰���
//	17	�氩��
//	18	�߰���

class CBalance
{
	// Constructor, Destructor & private initializer
	public:
		CBalance();
		~CBalance();

	private :

	public:
		// Set
		void SetLevel(int i) { mLevel = i; };
		void SetExp(int i) { mExp = i; };
		void SetExpTotal(int i) { mExpTotal = i; };
		void SetGoldTotal(int i) { mGoldTotal = i; };
		void SetMobHP(int i) { mMobHP = i; };
		void SetMobExp(int i) { mMobExp = i; };
		void SetMobGold(int i) { mMobGold = i; };
		void SetMobHunt(int i) { mMobHunt = i; };
		void SetMobHuntTotal(int i) { mMobHuntTotal = i; };

		// Report Interfaces
		int GetLevel(void) { return mLevel; };
		int GetExp(void) { return mExp; };
		int GetExpTotal(void) { return mExpTotal; };
		int GetGoldTotal(void) { return mGoldTotal; };
		int GetMobHP(void) { return mMobHP; };
		int GetMobExp(void) { return mMobExp; };
		int GetMobGold(void) { return mMobGold; };
		int GetMobHunt(void) { return mMobHunt; };
		int GetMobHuntTotal(void) { return mMobHuntTotal; };

	// Attributes
	protected:
		int	mLevel;

		//	Zgl.01. ����ġ �뷱���� ���� ������ ���� 
		int mExp;
		int mExpTotal;
		int mGoldTotal;
		int mMobHP;
		int mMobExp;
		int mMobGold;
		int mMobHunt;
		int mMobHuntTotal;

};
typedef CBalance* LPBalance;

class CBalancePool
{
	// Constructor, Destructor & private initializer
	public:
		CBalancePool();
		~CBalancePool();

	private :
		void InitName(void);

	public:
		void Init(void);
		void CreateMember(void);
		BOOL IsLoadFile(LPCSTR szFileName);	
		BOOL LoadFile(LPCSTR szFileName);	
		BOOL SaveFile(LPCSTR szFileName);

		//	Set
		void SetStatPoint(int data) { miStatPoint = data; };
		void SetClassName(int i, char *str) { strcpy(mClassName[i], str); };
		void SetRaceName(int i, char *str) { strcpy(mRaceName[i], str); };
		void SetRaceMax(WORD d) { mRaceMax = d; };

		// Report Interfaces
		int GetStatPoint(void) { return miStatPoint; };
		LPStat	GetBaseStat(WORD num) { return mBaseStat[num]; };
		LPStat	GetClassStat(WORD num) { return mClassStat[num]; };
		LPStat	GetRaceStat(WORD num) { return mRaceStat[num]; };
		WORD	GetRaceMax(void) { return mRaceMax; };
		LPFormula GetFormula(WORD num) { return mFormula[num]; };
		LPBalance GetBalance(WORD num) { return mBalance[num]; };
		char *	GetClassName(int i) { return mClassName[i]; };
		char *	GetRaceName(int i) { return mRaceName[i]; };
		WORD GetClassExCount(void) { return mClassExCount; };
		WORD GetRaceExCount(void) { return mRaceExCount; };
		LPFactor GetFactor(void) { return mFactor; };
		LPFactor GetFactorTemp(void) { return mFactorTemp; };
		LPFactor GetFactorOffense(int i=0) { return mFactorOffense[i]; };
		LPFactor GetFactorDefense(int i=0) { return mFactorDefense[i]; };
		int GetStat(int Level, int Class, int Race, int Sel);
		void CalcFactor(int Level, int Class, int Race);
		void CalcCombat(int OffLevel, int OffClass, int OffRace, int DefLevel, int DefClass, int DefRace, char OffNum=0, char DefNum=0);
		void CalcWinCombat(int OffLevel, int OffClass, int OffRace, int DefLevel, int DefClass, int DefRace, char OffNum=0, char DefNum=0);
		void CalcCombatFactor(LPFactor pFactorOffense, LPFactor pFactorDefense);
		void CalcCombatFactor2(LPFactor pFactorOffense, LPFactor pFactorDefense);
		void CalcWinCombatFactor2(LPFactor pFactorOffense, LPFactor pFactorDefense);
		double CalcDP(int Level, int Class);
		double CalcMDP(int Level, int Class);
		double CalcAP(int Level, int Class, int IsSpeed=0);
		double CalcMAP(int Level, int Class, int IsSpeed=0);
		double CalcRAP(int Level, int Class, int IsSpeed=0);
		double CalcMRAP(int Level, int Class, int IsSpeed=0);
		double CalcCreatureAP(int Level, int Class);
		double CalcAttackRatio(LPFactor pFactorOffense, LPFactor pFactorDefense);
		double CalcMagicRatio(LPFactor pFactorOffense, LPFactor pFactorDefense);
		void CopyFactorToTarget(LPFactor pFactor);
		void CopyFactor(LPFactor pTFactor, LPFactor pSFactor);
		void AddFactor(LPFactor pTFactor, LPFactor pSFactor);
		void AvrFactor(LPFactor pFactor, double dData);
		void InitFactor(LPFactor pFactor);
//		void CopyFactorToOffense(char c=0);
//		void CopyFactorToDefense(char c=0);
		void CopyResultToFactor(LPFactor pFactor);
//		void CopyResultOffenseToFactor(char c=0);
//		void CopyResultDefenseToFactor(char c=0);
		LPCharSkill GetClassSkill(int i=0) { return mClassSkill[i]; };

		BOOL InsertRace(WORD);
		BOOL DeleteRace(WORD);
		BOOL CopyRace(WORD, WORD);

		// Attributes
	protected:
		//	����Ǵ� ���
		int miStatPoint;

		LPStat	mBaseStat[DATA_BASESTAT_MAX];
		LPStat	mClassStat[DATA_CLASSSTAT_MAX];
		LPStat	mRaceStat[DATA_RACE_MAX];
		WORD	mRaceMax;

		LPFormula mFormula[DATA_FACTOR_MAX];

		//	����� ���� ����� ������ ���� �ʴ´�.
		char		mClassName[3][_MAX_FNAME];
		WORD		mClassExCount;
		char		mRaceName[1][_MAX_FNAME];
		WORD		mRaceExCount;
		LPBalance	mBalance[_BAL_LEVELMAX+1];
		LPFactor	mFactor;
		LPFactor	mFactorTemp;
		LPFactor	mFactorOffense[_BAL_LEVELMAX+1];
		LPFactor	mFactorDefense[_BAL_LEVELMAX+1];
		LPCharSkill	mClassSkill[_BAL_LEVELMAX+1];

};
typedef CBalancePool* LPBalancePool;

#define OffData(a) pFactorOffense->GetData(a)
#define OffDataInt(a) pFactorOffense->GetDataInt(a)
#define DefDataInt(a) pFactorDefense->GetDataInt(a)

#define OffResult(a) pFactorOffense->GetResultData(a)


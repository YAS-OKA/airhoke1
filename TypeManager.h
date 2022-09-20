#pragma once
#include"data.h"
#include"BaseType.h"
#include"Pac.h"
#include"Player.h"
#include"Type1.h"
#include"Type2.h"
#include"Type3.h"
#include"Type4.h"
#include"Type5.h"
#include"Enemy.h"
#include"myfunction.h"

enum class CharactersState
{
	TsAnnna,
	AttackedTsAnnna,
};

static struct ChackDuaChange
{
	double nowDuability;
	double preDuability;
};

class TypeManager
{
private:
	static BaseType* m_pType;
	static int32 PreScore;
	static int32 Score;
	static Pac* insP;
	static Player* player_m;
	static Enemy* enemy_m;

	static ChackDuaChange ChackHitMan;
	static double itagaruTimer;
public:
	enum TYPE {
		TYPE1,
		TYPE2,
		TYPE3,
		TYPE4,
		TYPE5,
		Clear
	};

	TypeManager(int32 ScoreInit);
	~TypeManager();

	static void ChangeType(int32 type);

	static int32 GetNowScore();
	static int32 GetScore();
	static int32 GetNowType();

	static void Retry();

	static void Update();

	static void Draw(Array<Texture> characters);

};


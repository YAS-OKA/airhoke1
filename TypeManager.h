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
#include "Ball_1.h"

enum class CharactersState
{
	M_Annna,
	M_Alien,
	TsAnnna,
	AttackedTsAnnna,
	TsAlien,
	Tim1,
	Tim2,
	Tim3,
	Tim4,
	BombGage,
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
	static int32 sc;//malletBreakのときにnowScoreをもらう(Scoreでことたりると思ったけど、変更を加えるのが怖かった)

	static Pac* insP;
	static Player* player_m;
	static Enemy* enemy_m;

	static ChackDuaChange ChackHitMan;
	static ChackDuaChange ChackHitMan1;
	static double itagaruTimer;
	static double itagaruTimer1;

	static Ball_1* bat;
	static bool Explo;//ボムが発動中ならtrue
	static double ExploTimer;//ボムの経過時間
	static double Timerinterval;//intervalBatより大きくなると0になる
	static double intervalBat;//蝙蝠が出てくる間隔

	static double BombBibTimer;//ボムによって揺れるじかん
	static double TimMotionTimer;//ティム君の動きのハンドルに使うタイマー
	static double TimMotionTime;//ティム君の一連の動きに要する時間

	static int32 ShowBombGage;

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

	static void Draw(Array<Texture> characters, Array<Texture>Bat);

};


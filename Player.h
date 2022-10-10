#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"Mallet.h"
#include"Pac.h"
//#include "Ball_1.h"


class Player: public Mallet
{
private:
	double delta;
	double duability;
	int32 BombNum=1;
	//Ball_1 Bat;
	bool HaveBomb;//ボムがあるかないか
	int32 PiggyBomb;//ボムを使った時のスコアを保持
	int32 CountBombExplo;//ボムを使った回数をカウント
public:
	Player(double x, double y, double em, double m_r, double h_s, double r_s, double m_s, double tableleft, double tableupper,
		double windowwide, double windowhight, double g_r,Array<Vec2> life);
	~Player();

	int32 AccumulateBomb(int32 nowscore);//bombを吐いてから,たまったスコアの量を返す。

	bool GetHaveBomb() { return HaveBomb; };

	void SetHaveBomb(bool ft) { HaveBomb = ft; };

	void keymove(bool enemyBrak);

	void Move(Vec2 houkou, bool enemyBreak);

	void ChangeSpeed();

	void SetBombNum(int32 n) {	BombNum = n; };

	int32 GetBombNum() { return BombNum; };

	void duabilityDown();

	void duabilityDownContinuous();

	int32 GetDua();

	Circle GetAtarihantei();

	void BreakMallet(int32* score);

	void RepairMallet();

	void Repaired();

	void Draw();
};

#endif

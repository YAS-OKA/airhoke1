#pragma once
#include"Pac.h"
#include"Player.h"
#include "Ball_1.h"

class BaseType
{
protected:
	int32 m_score;
	bool bombflag;
	Ball_1* ball1 = 0;
	Ball_1* ball2 = 0;
	Ball_1* ball3 = 0;
	Ball_1* ball4 = 0;
	Ball_1* ball5 = 0;
	Ball_1* ball6 = 0;
	Ball_1* ball7 = 0;

public:
	BaseType(int32 scor);
	int32 Getm_score();
	void SetBombflag(bool ft) { bombflag = ft; };
	bool GetBombflag() { return bombflag; };
	void Setm_score(int32 score);
	void ExceptBall(Array<ball> bat);
	virtual void Update(Pac* pac, Player* player, Enemy* enemy) = 0;
	virtual void Draw() = 0;
};


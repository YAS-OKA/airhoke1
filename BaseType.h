#pragma once
#include"Pac.h"
#include"Player.h"

class BaseType
{
protected:
	int32 m_score;
public:
	BaseType(int32 scor);
	int32 Getm_score();
	void Setm_score(int32 score);
	virtual void Update(Pac* pac, Player* player, Enemy* enemy) = 0;
	virtual void Draw() = 0;
};


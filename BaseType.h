#pragma once
#include"Pac.h"
#include"Player.h"

class BaseType
{
protected:
	int32* m_score;
public:
	BaseType(int32* scor);
	virtual void Update(Pac* pac, Player* player, Enemy* enemy) = 0;
	virtual void Draw() = 0;
};


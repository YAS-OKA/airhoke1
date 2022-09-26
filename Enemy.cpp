#include "stdafx.h"
#include "Enemy.h"
#include "Pac.h"

Enemy::Enemy(double x, double y, double e, double m_r, double h_s, double r_s, double m_s, double tableleft, double tableupper,
	double windowwide, double windowhight, double g_r, Array<Vec2> life)
	:Mallet(x, y, e, m_r, h_s, r_s, m_s, tableleft, tableupper, windowwide, windowhight, g_r, life)
{
	SetEmove(0);
}
Enemy::~Enemy()
{

}

void Enemy::emove(double x)
{
	if(!Break)
		SetXY(x,tableUpper+Pr);
}

void Enemy::SetEmove(double time,double Mt, double mt, int32 Mh, int32 mh)
{
	t1 = time;
	thetaMax = Mt, thetamin = mt, Maxh = Mh, minh = mh;
	theta = Random(mt, Mt);
	h = Random(mh, Mh);
}

void Enemy::Emove(Vec2 pacp, Vec2 pacv)
{
	if (pacp.y < tableUpper + tableHight / 2 && pacv.y < 0)
	{
		double dt = Scene::DeltaTime();
		Vec2 dis{ pacp.x + (Pr + Mr) * Sin((theta + CalDir(Vec2(0,0),pacv)) / 2),pacp.y - (Pr + Mr) * Cos((theta + CalDir(Vec2(0,0),pacv)) / 2) };
		SetXY(GetXY().x + (dis.x - GetXY().x) * dt / t1, GetXY().y + (dis.y - GetXY().y) * dt / t1);
		Print << t1;
	}
	else
	{
		SetEmove(-(pacp.y - h+(Pr+Mr)*Sin(CalDir(Vec2(0,0),pacv)+3.14) )/ pacv.y);
	}
}

void Enemy::CollidePac(Vec2 v,double damage)
{
	
	duability -= sqrt(v.x * v.x + v.y * v.y) * damage;
}

void Enemy::ColideTim()
{
	duability -= TimDamage;
}

int32 Enemy::GetDua()
{
	return duability;
}

void Enemy::SetDua(int32 d)
{
	duability = d;
}

void Enemy::BreakMallet()
{
	SetXY(-1000, -1000);
	duability = 0;
	Break = true;
}

void Enemy::RepairMallet()
{
	duability = DuaInit;
	Break = false;
}

#include "stdafx.h"
#include "Enemy.h"
#include "Pac.h"

Enemy::Enemy(double x, double y, double e, double m_r, double h_s, double r_s, double m_s, double tableleft, double tableupper,
	double windowwide, double windowhight, double g_r, Array<Vec2> life)
	:Mallet(x, y, e, m_r, h_s, r_s, m_s, tableleft, tableupper, windowwide, windowhight, g_r, life)
{
}
Enemy::~Enemy()
{

}

void Enemy::emove(double x)
{
	if(!Break)
		SetXY(x,tableUpper+Pr);
}

void Enemy::HitBackPac(double x)
{
	double dt = Scene::DeltaTime();
	if (HitBackTimer > 0)
	{
		HitBackTimer += dt;
		if (HitBackTimer < 0.3)//打ち返す
		{
			SetXY(GetXY().x + rowspeed * dt * Cos(theta), GetXY().y + rowspeed * dt * Sin(theta));
		}
		else if (GetXY().y - dt * rowspeed > tableUpper + Mr)//高さを戻す
		{
			SetXY(GetXY().x, GetXY().y - dt * rowspeed);
		}
		else
		{
			SetXY(GetXY().x, tableUpper + Mr);
			if (GetXY().x != x)//パックの下に戻る
			{
				if (GetXY().x > x)
				{
					if (GetXY().x - rowspeed * dt <= x)
					{
						SetXY(x, GetXY().y);
						HitBackTimer = 0;						//打ち返す一連の流れが終了
					}
					else
						SetXY(GetXY().x - rowspeed * dt, GetXY().y);
				}
				else
				{
					if (GetXY().x + rowspeed * dt >= x)
					{
						SetXY(x, GetXY().y);
						HitBackTimer = 0;						//打ち返す一連の流れが終了
					}
					else
						SetXY(GetXY().x + rowspeed * dt, GetXY().y);
				}
			}
		}
	}
	else
		emove(x);
}

Vec2 Enemy::GetVelo()
{
	Vec2 nowV;
	nowV = (GetXY() - GetPreXY()) / Scene::DeltaTime();
	return nowV;
}

void Enemy::CollidePac(Vec2 v,double damage)
{
	if (CalDir(Vec2(0, 0), v) + 3.14 < 3.14 / 2)
		theta = Random(3.14 / 2 - thetaRange / 2, Maxt + CalDir(Vec2(0, 0), v) + 3.14);
	else
		theta = Random(mint + CalDir(Vec2(0, 0), v) + 3.14, 3.14 / 2 + thetaRange / 2);
	theta = Random(mint, Maxt);
	HitBackTimer += Scene::DeltaTime();
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

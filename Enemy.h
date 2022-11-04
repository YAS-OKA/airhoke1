#pragma once
#include "Mallet.h"
#include "myfunction.h"
#include"data.h"

class Enemy:public Mallet
{
private:
	//Rect DuabilityBar;
	int32 point;
	double HitBackTimer = 0;//これが0より大きくなるとhitbackする。パックが衝突したらscenedeltatimeを代入
	double theta=3.14/2;
	double Maxt=3.14*2/3, mint=3.14/3;
	double thetaRange = Maxt - mint;

	bool CantHitBack = false;

	Audio TimPanch{ U"Audios/ティム殴る.mp3" };
	Audio Down{ U"Audios/宇宙人ダウン.mp3" };

public:
	Enemy(double x, double y, double e, double m_r, double h_s, double r_s, double m_s, double tableleft, double tableupper,
		double windowwide, double windowhight, double g_r,Array<Vec2> life);

	~Enemy();

	void emove(double x);

	void SetCantHitBack(bool tf) { CantHitBack = tf; };

	void HitBackPac(double pacx);//パックのｘ座標が引数

	Vec2 GetVelo();//敵の瞬間の速さを返す

	void CollidePac(Vec2 velocity,double damage);//パックに当たった時、耐久値を減らす

	void ColideTim();//tim君に当たった時

	int32 GetDua();

	void SetDua(int32 d);

	void BreakMallet();

	void RepairMallet();

};

#pragma once
#include "Mallet.h"
#include "myfunction.h"
#include"data.h"

class Enemy:public Mallet
{
private:
	//Rect DuabilityBar;
	int32 point;
	double theta;//ランダム
	double thetaMax, thetamin;//パックを打ち返す方向の範囲
	int32 h; //マレットが目指す場所のy座標
	int32 Maxh, minh;//ランダムの範囲
	double t1;
public:
	Enemy(double x, double y, double e, double m_r, double h_s, double r_s, double m_s, double tableleft, double tableupper,
		double windowwide, double windowhight, double g_r,Array<Vec2> life);

	~Enemy();

	void emove(double x);

	void SetEmove(double time,double Maxtheta=3.14/3, double mintheta=3.14*2/3, int32 Maxh=tableUpper+tableHight/6+Mr, int32 minh=tableUpper+Mr);

	void Emove(Vec2 pacp,Vec2 pacv);

	void CollidePac(Vec2 velocity,double damage);//パックに当たった時、耐久値を減らす

	void ColideTim();//tim君に当たった時

	int32 GetDua();

	void SetDua(int32 d);

	void BreakMallet();

	void RepairMallet();

};

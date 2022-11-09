#include "stdafx.h"
#include "Type2.h"

Type2::Type2(int32 sco)
	:bullet1(0), type(0), TypeChange(true), FirstGene(true), BaseType(sco)
{
	Edamage = 0.18;
	bullet = { {{WindowWide / 2, tableUpper + tableHight / 4} ,3.14 / 4},{{WindowWide / 2, tableUpper + tableHight / 4} ,3.14 * 3 / 4},{{WindowWide / 2, tableUpper + tableHight / 4} ,3.14 * 5 / 4},{{WindowWide / 2, tableUpper + tableHight / 4} ,3.14 * 7/ 4} };

	bullet1 = new EneBullet_1(bullet_R, bullet);
	bullet2 = new EneBullet_1(bullet_R, bullet);


	ball1 = new Ball_1(ball_r, ball_R);
	ball2 = new Ball_1(ball_r, ball_R);
	ball3 = new Ball_1(ball_r, ball_R);
	ball4 = new Ball_1(ball_r, ball_R);
	ball5 = new Ball_1(ball_r, ball_R);
	ball6 = new Ball_1(ball_r, ball_R);
	ball7 = new Ball_1(ball_r, ball_R);
}

Type2::~Type2() {}

void Type2::Update(Pac* pac, Player* player, Enemy* enemy)
{
	if (player->GetRevivaled())		//プレイヤーが復活したとき,または点を入れられたとき弾をすべて消す
	{
		ball1->BallAllExtingish();
		player->SetRevivaled(false);
	}
	//初めに一回行う処理
	if (TypeChange)
	{
		switch (type)
		{
		case 0:
			break;
		case 1:
			ball1->BallAllExtingish();
			delete bullet1;
			bullet1 = new EneBullet_1(bullet_R, bullet);
			FirstGene = true;
			break;
		case 2:
			ball1->BallAllExtingish();
			delete ball1;
			ball1 = new Ball_1(5, 12);
			delete bullet1;
			delete bullet2;
			bullet = { {{WindowWide / 2 - tableWide / 4, tableUpper + tableHight / 4} ,3.14 / 4},{{WindowWide / 2 - tableWide / 4, tableUpper + tableHight / 4} ,3.14 * 3 / 4},{{WindowWide / 2 - tableWide / 4, tableUpper + tableHight / 4} ,3.14 * 5 / 4},{{WindowWide / 2 - tableWide / 4, tableUpper + tableHight / 4} ,3.14 * 7 / 4} };
			bullet1 = new EneBullet_1(bullet_R, bullet);
			bullet = { {{WindowWide / 2 + tableWide / 4, tableUpper + tableHight / 4} ,3.14 / 4},{{WindowWide / 2 + tableWide / 4, tableUpper + tableHight / 4} ,3.14 * 3 / 4},{{WindowWide / 2 + tableWide / 4, tableUpper + tableHight / 4} ,3.14 * 5 / 4},{{WindowWide / 2 + tableWide / 4, tableUpper + tableHight / 4} ,3.14 * 7 / 4} };
			bullet2 = new EneBullet_1(bullet_R, bullet);
			FirstGene = true;
			break;
		default:
			break;
		}
		TypeChange = false;
	}
	
	//タイプがチェンジしていない時
	switch (type)
	{
	case 0:
		bullet1->GeneBullet_1(1);
		if (enemy->GetDua() < DuaInit * 3 / 4) {
			TypeChange = true; type++;
		}
		bullet1->Shotball(ball1, BallSpeed * 3 / 4, 0.3+Nannido*0.1);
		ball1->BallMove();
		bullet1->SwingNeck_360(1);
		break;
	case 1:
		if (FirstGene)
		{
			bullet1->GeneBullet_1(0.1);	//最初生み出されるまで
			if (bullet1->TimerNotCount())
				FirstGene = false;
		}
		if (enemy->GetDua() < DuaInit * 2 / 5) {
			TypeChange = true; type++;
		}
		bullet1->Shotball(ball1, BallSpeed * 3 / 4, 0.15+Nannido*0.1);
		ball1->BallMove();
		bullet1->SwingNeck_360(3+Nannido);
		break;
	case 2:
		if (FirstGene)
		{
			bullet1->GeneBullet_1(1);
			bullet2->GeneBullet_1(0.7);
			if (bullet1->TimerNotCount() && bullet2->TimerNotCount())
				FirstGene = false;
		}
		bullet1->Shotball(ball1, BallSpeed * 6 / 7 -Nannido*50, 4, 0.15+Nannido*0.3);
		bullet2->Shotball(ball1, BallSpeed * 6 / 7 - Nannido * 50, 4, 0.15 + Nannido * 0.3);
		bullet1->MoveGrab(Vec2(WindowWide / 2, tableUpper + tableHight / 4),4000);
		bullet2->MoveGrab(Vec2(WindowWide / 2, tableUpper + tableHight / 4), 4000);
		ball1->BallMove(BallSpeed / 3);
		bullet1->SwingNeck_360(4+Nannido*2);
		bullet2->SwingNeck_360(4 + Nannido * 2);
		break;
	default:
		break;
	}
	ball1->IntersectsPac(pac,&m_score);
	ball1->RemoveOutBall(table);
	if (ball1->IntersectsPlayer(player))
	{
		ball1->BallAllExtingishWithoutRay();
	}
	ball1->BallDecrease();
	ball1->BallDecelerate();
}

void Type2::Draw()
{
	
	ball1->Ball_1_draw();
	switch (type)
	{
	case 0:
		bullet1->bulletDraw();
		break;
	case 1:
		bullet1->bulletDraw();
		break;
	case 2:
		bullet1->bulletDraw();
		bullet2->bulletDraw();
		break;
	default:
		break;
	}
	
}

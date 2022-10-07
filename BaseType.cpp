#include "stdafx.h"
#include "BaseType.h"

BaseType::BaseType(int32 scor) :m_score(scor)
{
	bombflag = false;
}

int32 BaseType::Getm_score()
{
	return m_score;
}

void BaseType::Setm_score(int32 score)
{
	m_score = score;
}

void BaseType::ExceptBall(Array<ball> bat)
{
	ball1->ExceptBall(bat, &m_score);
	ball2->ExceptBall(bat, &m_score);
	ball3->ExceptBall(bat, &m_score);
	ball4->ExceptBall(bat, &m_score);
	ball5->ExceptBall(bat, &m_score);
	ball6->ExceptBall(bat, &m_score);
	ball7->ExceptBall(bat, &m_score);
}

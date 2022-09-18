#include "stdafx.h"
#include "BaseType.h"

BaseType::BaseType(int32 scor) :m_score(scor)
{

}

int32 BaseType::Getm_score()
{
	return m_score;
}

void BaseType::Setm_score(int32 score)
{
	m_score = score;
}

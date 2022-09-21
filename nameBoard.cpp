#include "stdafx.h"
#include "nameBoard.h"

nameBoard::nameBoard(Font f, Vec2 v, int32 Limit) :len(Limit), font(f), LeftTop(v)
{
	
}

bool nameBoard::isEnter()
{
	return Enter;
}

void nameBoard::Update()
{
	if (KeyUp.down())
	{
		nowmoji.colmn--;
	}
	if (KeyDown.down())
	{
		nowmoji.colmn++;
	}
	if (KeyLeft.down())
	{
		nowmoji.row--;
	}
	if (KeyRight.down())
	{
		nowmoji.row++;
	}
	nowmoji.row = (nowmoji.row + 13) % 13;
	nowmoji.colmn = (nowmoji.colmn + 5) % 5;

	if (KeyZ.down())
	{
		if (nowmoji.colmn == 4)
		{
			switch (nowmoji.row)
			{
			case 11:
				if (not name.isEmpty())
					name.pop_back();
				break;
			case 12:
				Enter = true;
				break;
			default:
				if (name.size() < len)
					name += board[nowmoji.colmn][nowmoji.row];
				break;
			}
		}
		else
		{
			if (name.size() < len)
				name += board[nowmoji.colmn][nowmoji.row];
		}
	}
}

void nameBoard::Draw()
{
	Vec2 p = LeftTop;
	for (int32 i = 0; i < 5; i++)
	{
		for (int32 j = 0; j < 13; j++)
		{
			if (nowmoji.row == j && nowmoji.colmn == i)
				font(board[i][j]).draw(p.x, p.y, ColorF(Palette::Lavenderblush));
			else
				font(board[i][j]).draw(p.x, p.y , ColorF(Palette::Black));
			p.x += font.fontSize() * board[i][j].length()+3;
		}
		p.x = LeftTop.x;
		p.y += font.fontSize()+3;
	}
}

String nameBoard::GetName()
{
	return name;
}

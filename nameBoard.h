#pragma once
class nameBoard
{
private:
	String board[5][13] =
	{
		{U"A",U"B",U"C",U"D",U"E",U"F",U"G",U"H",U"I",U"J",U"K",U"L",U"M"},
		{U"N",U"O",U"P",U"Q",U"R",U"S",U"T",U"U",U"V",U"W",U"X",U"Y",U"Z"},
		{U"a",U"b",U"c",U"d",U"e",U"f",U"g",U"h",U"i",U"j",U"k",U"l",U"m"},
		{U"n",U"o",U"p",U"q",U"r",U"s",U"t",U"u",U"v",U"w",U"x",U"y",U"z"},
		{U"<",U">",U"!",U"?",U";",U"/",U"[",U"]",U"^",U".",U"_",U"戻る",U"決定"},
	};

	struct nowSelecting {
		int32 row = 0;
		int32 colmn = 0;
	}nowmoji;

	Vec2 LeftTop;//左上の座標
	String name;
	bool Enter = false;
	Font font;
	int32 len;
public:
	nameBoard(Font f,Vec2 v,int32 Limitlen = 3);//文字数制限
	bool isEnter();
	void SetEnter(bool ft);
	void Update();
	void Draw();
	String GetName();
};


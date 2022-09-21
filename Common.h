# pragma once
# include <Siv3D.hpp>

enum class State
{
	Title,
	Game,
	Ranking,
	GameClear,
};

struct Scores
{
	// ハイスコア
	int32 highScore;
	//名前
	String name;
	//日付
	int32 y;
	int32 m;
	int32 d;

};

// 共有するデータ
struct GameData
{
	// 直前のゲームのスコア
	Optional<int32> lastGameScore;

	Array<Scores>HighScores =
	{
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
		{0,U"__________",0,0,0},
	};
};

using App = SceneManager<State, GameData>;




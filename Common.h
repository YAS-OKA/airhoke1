# pragma once
# include <Siv3D.hpp>

enum class State
{
	Title,
	Game,
	GameClear,
};

// 共有するデータ
struct GameData
{
	// 直前のゲームのスコア
	Optional<int32> lastGameScore;

	// ハイスコア
	Array<int32> highScores = { 0, 0, 0, 0, 0 };
};

using App = SceneManager<State, GameData>;




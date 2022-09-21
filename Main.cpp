#include <Siv3D.hpp>
#include"data.h"
#include"Mallet.h"
#include"Player.h"
#include"Pac.h"
#include"Enemy.h"
#include"ButtonManager.h"
#include"TypeManager.h"
#include"Common.h"
#include"nameBoard.h"

///自分が死んだとき、玉の消滅にエフェクトをつけたい

const int32 WindowWide = 1200;
const int32 WindowHight = 800;


ButtonManager b_manager;

Array<Texture> Characters;

void SetTextureCharacters()
{
	const Texture textureTsAnnna{ U"Images/TableSideAnnna.png" };
	const Texture textureAttackedTsAnnna{ U"Images/AttackedTableSideAnnna.png" };
	Characters << textureTsAnnna;
	Characters << textureAttackedTsAnnna;
}

class Title : public App::Scene
{
private:
	Font font{ 30 };
public:
	Title(const InitData& init)
		: IScene(init)
	{
		pause = false;
		gameover = false;
		BackChangeSc = false;
		changeSc = false;
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"スタート", Vec2(WindowWide / 2-60, WindowHight / 2), 30, 120, Palette::White, START);
		b_manager.SetButton(U"終了", Vec2(WindowWide / 2-60, WindowHight / 2 + 50), 30, 120, Palette::White, QUIT);
	}

	void update() override
	{
		b_manager.Update();

		if (changeSc)
		{
			changeScene(State::Game);
		}
	}

	void draw()const override
	{
		b_manager.Draw();

		Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

		FontAsset(U"Titlefont")(U"弾幕エアホッケー").drawAt(600, 100);

		font(U"z...決定").draw(10, WindowHight - 50);
	}
};

class Game : public App::Scene
{
private:
	int32 Score;
	int32 ScoreInit = 0;//ゼロで固定。最初からにしたとき、必ずゼロで始まる（typemanagerデストラクタでm_scoreを0にしている）から
	TypeManager* t_manager = NULL;
	Font font{ 60 };
	Font Scorefont1{ 30 };
	Font Scorefont2{ 22 };
	bool oneTime = true;
	
public:
	
	Game(const InitData& init)
		:IScene(init),Score(0)
	{
		SetTextureCharacters();
		t_manager = new TypeManager(ScoreInit);
		changeSc = false;
		t_manager->ChangeType(4);
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"再開", Vec2(WindowWide - 300, tableUpper + tableHight * 3 / 4), 30, 120, Palette::White, RESTART);
		b_manager.SetButton(U"最初から始める", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 + 50), 30, 150, Palette::White, REBEGIN);
		b_manager.SetButton(U"タイトルに戻る", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 + 100), 30, 150, Palette::White, BACK_TO_TITLE);
	}

	void update() override
	{
		t_manager->Update();

		if (rebegin)
		{
			delete t_manager;
			pause = false;
			gameover = false;
			rebegin = false;
			changeScene(State::Game);
		}
				
		if (BackChangeSc)
		{
			delete t_manager;
			changeScene(State::Title);
		}
		if (changeSc)
		{
			Score = t_manager->GetScore();
			delete t_manager;
			getData().lastGameScore = Score;
			changeScene(State::Ranking);

		}

		if (gameover&&oneTime)
		{			
			b_manager.RemoveAllButton();
			b_manager.SetButton(U"タイトルに戻る", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 + 100), 30, 150, Palette::White, BACK_TO_TITLE);
			b_manager.SetButton(U"最初から始める", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 + 50), 30, 150, Palette::White, REBEGIN);
			b_manager.SetButton(U"途中から始める", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4), 30, 150, Palette::White, RETRY);
			oneTime = false;
		}
		if (gameover)
			b_manager.Update();

		if (pause)
			b_manager.Update();

		if (retry)
		{
			t_manager->ChangeType(t_manager->GetNowType());
			t_manager->Retry();
			oneTime = true;
			changeSc = false;
			gameover = false;
			retry = false;
		}
		
	}

	void draw() const override
	{
		if (!changeSc)
		{
			if (!changeSc)
				t_manager->Draw(Characters);
			if (pause)
			{
				Rect{ 0,0,WindowWide,WindowHight }.draw(ColorF(Palette::Black, 0.7));
				font(U"ポーズ").drawAt(Scene::Center(), Palette::White);
				b_manager.Draw();
			}
			if (gameover)
			{
				Rect{ 0,0,WindowWide,WindowHight }.draw(ColorF(Palette::Black, 0.7));
				font(U"ゲームオーバー").drawAt(Scene::Center(), Palette::Darkred);
				b_manager.Draw();
			}
			Scorefont1(U"スコア").draw(WindowWide - tableLeft + 10, WindowHight - 40, ColorF(Palette::Yellow));
			Scorefont2(t_manager->GetNowScore()).draw(WindowWide - tableLeft + 110, WindowHight - 32, ColorF(Palette::White));
		}
	}
};

class Ranking :public App::Scene
{
public:
	Ranking(const InitData& init) :IScene(init)
	{
		board = new nameBoard(fontBoard, Vec2(WindowWide/2-fontBoard.fontSize() * 7.5, WindowHight - 160), 10);
		changeSc = false;
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"はい", Vec2(WindowWide / 2 - 110, WindowHight - 150), 30, 60, Palette::White, FLAG);
		b_manager.SetButton(U"いいえ", Vec2(WindowWide / 2 + 50, WindowHight - 150), 30, 60, Palette::White, START);

		auto& data = getData();
		kariHighScores = data.HighScores;

		if (data.lastGameScore)
		{
			const int32 lastScore = *data.lastGameScore;

			// ランキングを再構成
			const Date date = Date::Today();
			
			Scores last = { lastScore , U"",date.year,date.month,date.day };
			
			kariHighScores << last;
			//スコアソート
			for (int32 i = 0; i < RankingCount; i++)
				for (int32 j = RankingCount; j - 1 >= i; j--)
				{
					if (kariHighScores[j].highScore > kariHighScores[j - 1].highScore);
					{
						Scores z;
						z = kariHighScores[j];
						kariHighScores[j] = kariHighScores[j - 1];
						kariHighScores[j - 1] = z;
					}
				}
			kariHighScores.resize(RankingCount);
			// ランクインしていたら m_rank に順位をセット
			for (int32 i = 0; i < RankingCount; ++i)
			{
				if (kariHighScores[i].highScore == last.highScore)
				{
					m_rank = i;
					break;
				}
			}
			data.lastGameScore.reset();

		}
	}
	void update() override
	{
		if (changeSc)
			changeScene(State::GameClear);

		if (board->isEnter()&&not board->GetName().isEmpty())
		{
			kariHighScores[m_rank].name = board->GetName();
			getData().HighScores = kariHighScores;
			FlashTimer += Scene::DeltaTime();
			Timer += Scene::DeltaTime();

			if (FlashTimer > FlashInterval * 2)
				FlashTimer = 0;
		}
		else
		{
			board->SetEnter(false);
			if (b_manager.GetFlag())
			{
				board->Update();
			}
			else
			{
				b_manager.Update();
			}
		}

		if (Timer > TimeOfBeginingSceneChange)
			changeSc = true;
	}
	void draw() const override
	{
		if (not b_manager.GetFlag())
		{
			fontBoard(U"スコアを保存しますか？").drawAt(WindowWide / 2, WindowHight - 200, ColorF(Palette::Black));
			b_manager.Draw();
		}
		else
		{
			//入力ボードを表示
			board->Draw();
			fontBoard(board->GetName()).draw(WindowWide / 2 - fontBoard.fontSize() * 3, WindowHight - 200, ColorF(Palette::Black));
			fontBoard(U"名前を入力してください。").draw(WindowWide / 2 - fontBoard.fontSize() * 6, WindowHight - 250, ColorF(Palette::Black));
			}

		Scene::SetBackground(ColorF{ 0.4, 0.6, 0.9 });

		FontAsset(U"Ranking")(U"HIGH SCORE RANKING").drawAt(WindowWide/2, 60);

		// ランキングを表示
		for (auto i : step(RankingCount))
		{
			const RectF rect{ WindowWide / 2 - 200, 120 + i * 50, 400, 50 };

			rect.draw(ColorF{ 1.0, 0 });
			//スコア
			FontAsset(U"Ranking")(kariHighScores[i].highScore).drawAt(rect.center(), ColorF{ 0.25 });
			//名前
			
			if (FlashTimer < FlashInterval && board->isEnter() && i == m_rank)
			{
				//何も表示しない
			}
			else
			{
			FontAsset(U"Ranking")(kariHighScores[i].name).draw(WindowWide / 2 - 250 - fontBoard.fontSize() * 10, 120 + i * 50, ColorF{ Palette::Black });
			}
			//日付
			if (kariHighScores[i].y == 0)
				FontAsset(U"Ranking")(U"----/--/--").draw(WindowWide / 2 + 250, 120 + i * 50, ColorF{ 0.25 });
			else
			{
				String d = Format(kariHighScores[i].y);
				d << U'/'; d += Format(kariHighScores[i].m); d << U'/'; d += Format(kariHighScores[i].d);
				FontAsset(U"Ranking")(d).draw(WindowWide / 2 + 250, 120 + i * 50, ColorF{ 0.25 });
			}

			// ランクインしていたら
			if (i == m_rank)
			{
				rect.stretched(Periodic::Triangle0_1(0.5s) * 10).drawFrame(5, ColorF{ 0.8, 0.6, 0.4 });
			}
		}
	}
private:
	nameBoard *board;

	Font fontBoard{ 26 };

	static constexpr int32 RankingCount = 8;

	bool hozonn = false;

	int32 m_rank = -1;

	Array<Scores> kariHighScores;

	double FlashTimer=0;
	double FlashInterval = 0.1;
	double Timer = 0;
	double TimeOfBeginingSceneChange = 1;
};

class GameClear : public App::Scene
{
public:
	GameClear(const InitData& init) : IScene(init)
	{
		changeSc = false;
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"タイトルに戻る", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 ), 30, 150, Palette::White, BACK_TO_TITLE);
	}

	void update() override
	{
		b_manager.Update();
		if (BackChangeSc)
		{
			changeScene(State::Title);
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
		b_manager.Draw();
		FontAsset(U"Titlefont")(U"ゲームクリア！！").drawAt(Scene::Center(), Palette::Greenyellow);
	}
};

void Main()
{
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	Window::Resize(WindowWide, WindowHight);

	FontAsset::Register(U"Titlefont", 60, Typeface::Heavy);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);

	App manager;

	manager.add<Title>(State::Title);

	manager.add<Game>(State::Game);

	manager.add<Ranking>(State::Ranking);

	manager.add<GameClear>(State::GameClear);
	
	while (System::Update())
	{

		
		if (!manager.update())
		{
			break;
		}
	}
}

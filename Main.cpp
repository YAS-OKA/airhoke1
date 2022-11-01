﻿#include <Siv3D.hpp>
#include<HamFramework.hpp>
#include"data.h"
#include"Mallet.h"
#include"Player.h"
#include"Pac.h"
#include"Enemy.h"
#include"ButtonManager.h"
#include"TypeManager.h"
#include"Common.h"
#include"nameBoard.h"


const int32 WindowWide = 1200;
const int32 WindowHight = 800;

ButtonManager b_manager;

Array<Texture> Characters;
Array<Texture> Bat;

void ResetRanking()
{
	TextWriter writer(U"score.txt");

	for (auto i : step(8))
	{
		writer << U"__________" << U','
			<< 0 << U','
			<< 0 << U','
			<< 0 << U','
			<< 0;
	}
}

//描画する絵のアレイ
void SetTextureCharacters()
{
	//横の絵
	const Texture textureTsAnnna{ U"Images/TableSideAnnna.png" };
	const Texture textureAttackedTsAnnna{ U"Images/AttackedTableSideAnnna.png" };
	const Texture textureTsAlien{ U"Images/TableSideAlien2.1.png" };
	//マレットドット絵
	const Texture textureAnnnaOnMallet{ U"Images/AnnnaOnMallet.png" };
	const Texture textureAlienOnMallet{ U"Images/AlienOnMallet.png" };
	//ティム
	const Texture textureTim1{ U"Images/Tim1.png" };
	const Texture textureTim2{ U"Images/Tim2.png" };
	const Texture textureTim3{ U"Images/Tim3.png" };
	const Texture textureTim4{ U"Images/Tim4.png" };
	//ボムゲージ
	const Texture textureBombGage{ U"Images/BombMark.png" };

	//コウモリの絵
	const Texture textureBat1{ U"images/Bat1.png" };
	const Texture textureBat2{ U"images/Bat2.png" };
	const Texture textureBat3{ U"images/Bat3.png" };

	Characters << textureAnnnaOnMallet;
	Characters << textureAlienOnMallet;
	Characters << textureTsAnnna;

	Characters << textureAttackedTsAnnna;
	Characters << textureTsAlien;

	Characters << textureTim1;
	Characters << textureTim2;
	Characters << textureTim3;
	Characters << textureTim4;

	Characters << textureBombGage;

	Bat << textureBat1;
	Bat << textureBat2;
	Bat << textureBat3;
}

class Title : public App::Scene
{
private:
	Font font{ 40 };
	const Texture textureGameBack{ U"Images/game_Back.png" };
	Font fontYN{ 25 };
public:
	Title(const InitData& init)
		: IScene(init)
	{
		TypeManager::StartFPrintTimer = 3;
		TypeManager::PrintTimer = 0;

		TypeManager::started = false;

		pause = false;
		gameover = false;
		BackChangeSc = false;
		changeSc = false;
		changeExst = false;
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"スタート", Vec2(WindowWide / 2-70, WindowHight / 2), 30, 140, Palette::White, START);
		b_manager.SetButton(U"状況・設定など", Vec2(WindowWide / 2 - 70, WindowHight / 2 + 50), 30, 140, Palette::White, STORY);
		b_manager.SetButton(U"終了", Vec2(WindowWide / 2-70, WindowHight / 2 + 100), 30, 140, Palette::White, QUIT);
	}

	void update() override
	{
		b_manager.Update();

		if (changeSc)
		{
			changeScene(State::Game);
		}
		if (changeExst)
		{
			changeScene(State::Story);
		}
	}

	void draw()const override
	{
		textureGameBack.scaled(4).draw(0, 0,ColorF(0.9));

		b_manager.Draw();

		Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

		FontAsset(U"Danmaku")(U"弾幕").draw(300, 170, ColorF(Palette::Lime));
		FontAsset(U"Titlefont")(U"エアホッケー").draw(500, 190, ColorF(Palette::Aqua));


		font(U"z...決定").draw(30, WindowHight - 70);
		fontYN(U"2022 やっさん").draw(WindowWide *5 / 6, WindowHight - 50);
	}
};

class Story : public App::Scene
{
public:
	Story(const InitData& init) :IScene(init)
	{
		text << reader1.readAll();
		text << reader2.readAll();
		text << reader3.readAll();
		text << reader4.readAll();
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"タイトルへ", Vec2(WindowWide - tableLeft + 220, WindowHight-tableUpper-100), 30, 110, Palette::White, BACK_TO_TITLE);
		b_manager.SetButton(U"次のページ", Vec2(WindowWide-tableLeft+220, tableUpper), 30, 110, Palette::White, START);
		b_manager.SetButton(U"前のページ", Vec2(tableLeft-330, tableUpper), 30, 110, Palette::White, FLAG);
	}
	void update() override
	{
		b_manager.Update();
		if (changeSc)
		{
			if(NowPage<text.size()-1)
				NowPage++;
			changeSc = false;
		}
		if (BackChangeSc)
		{
			BackChangeSc = false;
			changeScene(State::Title);
		}
		if (b_manager.GetFlag())
		{
			if (NowPage > 0)
				NowPage--;
			b_manager.SetFlag(false);
			
		}
	}
	void draw() const override
	{
		textureGameBack.scaled(4).draw();
		TextWindow.draw(ColorF(Palette::Black, 0.8));
		font(text[NowPage]).draw(tableLeft - 200, 10);
		b_manager.Draw();
		
	}
private:
	int32 NowPage = 0;
	const Texture textureGameBack{ U"Images/game_Back.png" };
	Font font{ 25 };
	Array<String> text;
	Rect TextWindow{ tableLeft - 210,0,tableWide + 420,WindowHight };
	TextReader reader1{ U"story1.txt" };
	TextReader reader2{ U"story2.txt" };
	TextReader reader3{ U"story3.txt" };
	TextReader reader4{ U"story4.txt" };
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
	Font Sp{ 37 };
	bool oneTime = true;
	Font SCF{ 140,Typeface::Heavy };
	Font StartF{ 110 ,Typeface::Heavy };
	const Texture textureGameBack{ U"Images/game_Back.png" };

	double SCFPrintTimer = 1.5;
	Vec2 from = { WindowWide * 3 / 8,WindowHight / 2 };
	Vec2 to = { WindowWide / 2,WindowHight / 2 };
	Vec2 to2 = { WindowWide * 5 / 8,WindowHight / 2 };

	double Ptimer;
	bool SCFPrint;
public:
	
	Game(const InitData& init)
		:IScene(init),Score(0)
	{
		SCFPrint = false;
		Ptimer = 0;
		SetTextureCharacters();
		t_manager = new TypeManager(ScoreInit);
		changeSc = false;
		t_manager->ChangeType(0);
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"再開", Vec2(WindowWide - 300, tableUpper + tableHight * 3 / 4), 30, 120, Palette::White, RESTART);
		b_manager.SetButton(U"最初から始める", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 + 50), 30, 150, Palette::White, REBEGIN);
		b_manager.SetButton(U"タイトルに戻る", Vec2(WindowWide - 315, tableUpper + tableHight * 3 / 4 + 100), 30, 150, Palette::White, BACK_TO_TITLE);

	}

	void update() override
	{
		t_manager->Update();

		if (Ptimer > SCFPrintTimer)
		{
			SCFPrint = false;
			Ptimer = 0;
		}
		if (t_manager->GetGoalFlag())
		{
			SCFPrint=true;
		}
		if (SCFPrint)
		{
			Ptimer += Scene::DeltaTime();
		}


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
			Score = t_manager->GetNowScore();
			delete t_manager;
			getData().lastGameScore = Score;
			changeScene(State::Ranking);
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
		textureGameBack.scaled(4).draw(0, 0,ColorF(0.4));

		if (!changeSc)
		{
			Sp(U"必殺技").draw(WindowWide - tableLeft + 10, WindowHight - tableUpper - 100 - 27);
			t_manager->Draw(Characters, Bat,SCF,StartF);
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
		if (SCFPrint)
		{
			String s;
			s = Format(t_manager->GoalScore()[0]);
			s += U" ー ";
			s += Format(t_manager->GoalScore()[1]);
			if (Ptimer < 0.5)
			{
				const double t = Min(Ptimer, 0.5);

				const double e = EaseOutExpo(t);

				const Vec2 pos = from.lerp(to, e);
				SCF(s).drawAt(pos,ColorF(Palette::White,e));
			}
			else if (Ptimer < 1) {
				SCF(s).drawAt(WindowWide / 2, WindowHight / 2);
			}
			else if (Ptimer < SCFPrintTimer) {
				const double t = Min(Ptimer-1, 0.5);

				const double e = EaseOutExpo(t);

				const Vec2 pos = to.lerp(to2, e);
				SCF(s).drawAt(pos, ColorF(Palette::White,1-e));
			}
		}
	}
};

class Ranking :public App::Scene
{
public:
	Ranking(const InitData& init) :IScene(init)
	{
		board = new nameBoard(fontBoard, Vec2(WindowWide / 2 - fontBoard.fontSize() * 7.5, WindowHight - 160), 10);
		changeSc = false;
		b_manager.RemoveAllButton();
		b_manager.SetButton(U"はい", Vec2(WindowWide / 2 - 110, WindowHight - 150), 30, 60, Palette::White, FLAG);
		b_manager.SetButton(U"いいえ", Vec2(WindowWide / 2 + 50, WindowHight - 150), 30, 60, Palette::White, START);

		auto& data = getData();

		data.HighScores.clear();

		TextReader reader{ U"score.txt" };

		String line;

		int32 i = 0;
		while (reader.readLine(line))
		{
			Scores s;
			s.name = line.split(',')[0];
			s.highScore = Parse<int32>(line.split(',')[1]);
			s.y = Parse<int32>(line.split(',')[2]);
			s.m = Parse<int32>(line.split(',')[3]);
			s.d = Parse<int32>(line.split(',')[4]);

			data.HighScores << s;
		}


		const int32 lastScore = *data.lastGameScore;

		// ランキングを再構成
		const Date date = Date::Today();

		Scores last = { lastScore , U"",date.year,date.month,date.day };

		data.HighScores << last;
		//ソート
		//Print << data.HighScores[8].highScore;
		
		for (auto i : step(RankingCount+1))
		{
			m_rank = RankingCount - i;

			if (i == RankingCount)//スコアが1位の時
			{
				for (auto j : step(i))
				{
					Scores z = data.HighScores[RankingCount - j];
					data.HighScores[RankingCount - j] = data.HighScores[RankingCount - j - 1];
					data.HighScores[RankingCount - j - 1] = z;
				}
				break;
			}
			if (data.HighScores[RankingCount - i-1].highScore > data.HighScores[RankingCount].highScore)
			{
				for (auto j : step(i))
				{
					Scores z = data.HighScores[RankingCount - j];
					data.HighScores[RankingCount - j] = data.HighScores[RankingCount - j - 1];
					data.HighScores[RankingCount - j - 1] = z;
				}

				break;
			}
			
		}
		
		data.HighScores.resize(RankingCount);
		
		data.lastGameScore.reset();
	}

	void update() override
	{
		auto& data = getData();

		if (changeSc && BackChangeSc)
			changeScene(State::Title);//タイトルに戻るを選択してランキングシーンに飛んだ場合
		else if(changeSc)
			changeScene(State::GameClear);//ゲームをクリアしてからランキングシーンに飛んだ場合
		if (m_rank != -1) {
			if (board->isEnter() && not board->GetName().isEmpty())
			{
				//決定が押されたとき
				data.HighScores[m_rank].name = board->GetName();

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
			{
				//スコアを記録
				TextWriter writer(U"score.txt");

				for (auto i : step(8))
				{
					writer << getData().HighScores[i].name << U','
						<< getData().HighScores[i].highScore << U','
						<< getData().HighScores[i].y << U','
						<< getData().HighScores[i].m << U','
						<< getData().HighScores[i].d;
				}
				changeSc = true;
			}
		}
		else if (KeyZ.down())
			changeSc = true;
	}
	void draw() const override
	{
		if (m_rank != -1)
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
		}
		Scene::SetBackground(ColorF{ 0.4, 0.6, 0.9 });

		FontAsset(U"Ranking")(U"HIGH SCORE RANKING").drawAt(WindowWide/2, 60);

		// ランキングを表示
		for (auto i : step(RankingCount))
		{
			const RectF rect{ WindowWide / 2 - 200, 120 + i * 50, 400, 50 };

			rect.draw(ColorF{ 1.0, 0 });
			//スコア
			FontAsset(U"Ranking")(getData().HighScores[i].highScore).drawAt(rect.center(), ColorF{ 0.25 });
			//名前
			
			if (FlashTimer < FlashInterval && board->isEnter() && i == m_rank)
			{
				//何も表示しない
			}
			else
			{
				FontAsset(U"Ranking")(getData().HighScores[i].name).draw(WindowWide / 2 - 250 - fontBoard.fontSize() * 10, 120 + i * 50, ColorF{ Palette::Black });
			}
			//日付
			if (getData().HighScores[i].y == 0)
				FontAsset(U"Ranking")(U"----/--/--").draw(WindowWide / 2 + 250, 120 + i * 50, ColorF{ 0.25 });
			else
			{
				String d = Format(getData().HighScores[i].y);
				d << U'/'; d += Format(getData().HighScores[i].m); d << U'/'; d += Format(getData().HighScores[i].d);
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

	double FlashTimer=0;
	double FlashInterval = 0.1;
	double Timer = 0;
	double TimeOfBeginingSceneChange = 1;
};

class Ending : public App::Scene
{
public:
	Ending(const InitData& init) : IScene(init)
	{
		const Texture p1{ U"Images/ending/1.JPG" };
		const Texture p2{ U"Images/ending/2.JPG" };
		const Texture p3{ U"Images/ending/3.JPG" };
		const Texture p4{ U"Images/ending/4.JPG" };
		const Texture p5{ U"Images/ending/5.JPG" };
		const Texture p6{ U"Images/ending/6.JPG" };

		pictures << p1;
		pictures << p2;
		pictures << p3;
		pictures << p4;
		pictures << p5;
		pictures << p6;

		text = reader.readLines();
		numLine = 3;
		RectHight = fontsize * (3 * numLine + 1) / 2;
		X = 10;
		Y = WindowHight-X-RectHight;
		printArea = { X,Y,WindowWide -  X,int32(RectHight) };
	}

	void update() override
	{
		if (KeyZ.down())
		{
			if (nowP < size(text)-1)
			{
				if(nowP==3 or nowP==5 or nowP==12 or nowP==25 or nowP==29)
					KindPic++;
				nowP++;
			}
		}
		texts=text[nowP].split(',');
		
	}

	void draw() const override
	{
		pictures[KindPic].scaled(0.6).drawAt(WindowWide / 2, WindowHight / 2);

		printArea.draw(ColorF(Palette::Black,0.5));
		for (auto& i : step(size(texts)))
		{
			sub(texts[i]).draw(X + fontsize / 2, Y + fontsize / 2 + fontsize * 3 * i / 2);
		}
	}
private:
	int32 X;
	int32 Y;
	int32 fontsize = 20;
	double RectHight;
	int32 numLine;
	int32 nowP = 0;
	Array<Texture> Back_pic;
	Font sub{ fontsize };
	TextReader reader{ U"Ending.txt" };
	Array<Texture> pictures;
	Array<String> text;
	Array<String> texts;
	Rect printArea;
	int32 KindPic=0;
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

class Credit : public App::Scene
{
private:
	enum {
		nameBig,
		nameSmall
	};

	Font PrintTitleFont{ 80,Typeface::Bold };
	double PrintTitleTime = 9;
	double PrintTitleTimer = 0;

	int32 Bigsize = 30;
	int32 Smallsize = 25;

	Font BigName{ Bigsize };
	Font NomalName{ Smallsize };

	int32 ScrollSpeed = 20;

	int32 SmallGyouSpace = 30;//名前の行のスペース
	int32 BigGyouSpace = 60;

	Array<std::pair<int32, String>>m_Credits{
		{nameBig,U"弾幕エアホッケー　　スタッフ"},
		{nameSmall,U"プログラム   安田"},
		{nameSmall,U"作画   安田"},
		{nameBig,U"お借りしたキャラクター"},
		{nameSmall,U"アンナちゃん   りゅーの様から"},
		{nameSmall,U"ティムソートくん    WithBall様から"},
		{nameBig,U"開発環境　/  ツール"},
		{nameSmall,U"VS2019  C++  Siv3d"},
		{nameBig,U"テストプレイヤー"},
		{nameSmall,U"友人　KYT"},
		{nameSmall,U"怪しい5人衆"},
		{nameSmall,U"サークルの方々"},
		{nameBig,U"ゲームクリア係"},
		{nameSmall,U"あなた"},
		{nameSmall,U"おめでとう！！"},
	};
	Array<double>CreditY;//各クレジットのy座標

	int32 PrintNum;//クレジットをいくつ表示するか。

public:

	Credit(const InitData& init) :IScene(init)
	{
		CreditY << WindowHight + Bigsize + BigGyouSpace;
		PrintNum = 1;
	}

	void update() override
	{
		const double t = Scene::DeltaTime();

		if (PrintTitleTimer < PrintTitleTime)
		{
			PrintTitleTimer += t;
		}

		for (auto& y : CreditY)
			y -= t*ScrollSpeed;

		if (PrintNum < size(m_Credits))
		{
			if (m_Credits[PrintNum - 1].first == nameSmall)
			{
				if (m_Credits[PrintNum].first == nameBig)
				{
					if (CreditY[PrintNum - 1] < WindowHight - BigGyouSpace)
					{
						PrintNum++;
						CreditY << WindowHight + Bigsize;
					}
				}
				else if (CreditY[PrintNum - 1] < WindowHight - SmallGyouSpace)
				{
					PrintNum++;
					CreditY << WindowHight + Smallsize;
				}
			}
			else
			{
				if (CreditY[PrintNum - 1] < WindowHight - BigGyouSpace)
				{
					PrintNum++;
					CreditY << WindowHight + Bigsize;
				}
			}
		}
	}

	void draw() const override
	{
		if (PrintTitleTimer < PrintTitleTime)
		{
			if (PrintTitleTimer < PrintTitleTimer - 1)
				PrintTitleFont(U"Thank you for playing!").drawAt(WindowWide / 2, WindowHight / 2 - 100, ColorF(Palette::Yellow, Min(PrintTitleTimer/4, 1.0)));
			else
				PrintTitleFont(U"Thank you for playing!").drawAt(WindowWide / 2, WindowHight / 2 - 100, ColorF(Palette::Yellow, PrintTitleTime-PrintTitleTimer));
		}
		for (auto k : step(PrintNum))
		{
			if (m_Credits[k].first == nameSmall)
			{
				NomalName(m_Credits[k].second).drawAt(WindowWide / 2, CreditY[k]);
				/*
				for (auto& name : m_Credits[k].second)
				{
					NomalName(name).drawAt()
				}*/
			}
			else
			{
				BigName(m_Credits[k].second).drawAt(WindowWide / 2, CreditY[k]);
			}
		}
	}
};

void Main()
{
	//ResetRanking();//ハイスコアランキングをリセットしたいときはここのコメントを外す

	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	Window::Resize(WindowWide, WindowHight);

	FontAsset::Register(U"Titlefont", 80, Typeface::Heavy);
	FontAsset::Register(U"Danmaku", 100, Typeface::Heavy);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);

	App manager;

	manager.add<Title>(State::Title);

	manager.add<Story>(State::Story);

	manager.add<Game>(State::Game);

	manager.add<Ranking>(State::Ranking);

	manager.add<GameClear>(State::GameClear);

	manager.add<Credit>(State::Credit);

	manager.add<Ending>(State::Ending);

	manager.init(State::Credit);

	while (System::Update())
	{
		
		if (!manager.update())
		{
			break;
		}

	}
}

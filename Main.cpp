#include <Siv3D.hpp>
#include"data.h"
#include"Mallet.h"
#include"Player.h"
#include"Pac.h"
#include"Enemy.h"
#include"ButtonManager.h"
#include"TypeManager.h"
#include"Common.h"

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
	Font Scorefont{ 50 };
	bool oneTime = true;
	
public:
	
	Game(const InitData& init)
		:IScene(init),Score(0)
	{
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
			delete t_manager;
			changeScene(State::GameClear);
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
	
	}
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
			changeScene(State::GameClear);
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

	App manager;

	manager.add<Title>(State::Title);

	manager.add<Game>(State::Game);

	manager.add<GameClear>(State::GameClear);
	
	while (System::Update())
	{

		
		if (!manager.update())
		{
			break;
		}
	}
}

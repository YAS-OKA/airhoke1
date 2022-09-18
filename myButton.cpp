#include "stdafx.h"
#include "myButton.h"

//ゲームスタート
Start::Start()
{
	
}

Start::Start(m_Button button) :b(button)
{

}

Start::~Start() {}

void Start::Registation(String name, Vec2 pos, int32 hight, int32 wideth, Color c, bool state, int32 Cnum)
{

}

m_Button Start::GetButton()
{
	return b;
}

void Start::Update()
{
	if (KeyZ.down())
	{
		isZpushed = true;
	}
	if (isZpushed)
	{
		PushedCounter += Scene::DeltaTime();
	}
	if (PushedCounter > ActButtonTime)
	{
		changeSc = true;
		isZpushed = false;
		PushedCounter = 0;
	}
}

void Start::Draw()
{
	if (isZpushed)
	{
		FlashTimer += Scene::DeltaTime();

		if (FlashTimer > FlashInterval*2)
		{
			FlashTimer = 0;
		}
		else
		{
			if (FlashTimer < FlashInterval)
			{
				//何も表示しない
			}
			else
			{
				Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
			}
		}
	}
	else
	{
		//ｚボタンが押されてなければ
		Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
	}
}

//ポーズ状態解除、プレイヤーのlifeをマックス
Retry::Retry()
{

}

Retry::Retry(m_Button button) :b(button)
{

}

Retry::~Retry() {}

void Retry::Registation(String name, Vec2 pos, int32 hight, int32 wideth, Color c, bool state, int32 Cnum)
{

}

m_Button Retry::GetButton()
{
	return b;
}

void Retry::Update()
{
	if (KeyZ.down())
	{
		isZpushed = true;
	}
	if (isZpushed)
	{
		PushedCounter += Scene::DeltaTime();
	}
	if (PushedCounter > ActButtonTime)
	{
		retry = true;
		isZpushed = false;
		PushedCounter = 0;
	}
}

void Retry::Draw()
{
	if (isZpushed)
	{
		FlashTimer += Scene::DeltaTime();

		if (FlashTimer > FlashInterval * 2)
		{
			FlashTimer = 0;
		}
		else
		{
			if (FlashTimer < FlashInterval)
			{
				//何も表示しない
			}
			else
			{
				Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
			}
		}
	}
	else
	{
		//ｚボタンが押されてなければ
		Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
	}
	
}

//最初から始める
ReBegin::ReBegin()
{

}

ReBegin::ReBegin(m_Button button) :b(button)
{

}

ReBegin::~ReBegin() {}

void ReBegin::Registation(String name, Vec2 pos, int32 hight, int32 wideth, Color c, bool state, int32 Cnum)
{

}

m_Button ReBegin::GetButton()
{
	return b;
}

void ReBegin::Update()
{
	if (KeyZ.down())
	{
		isZpushed = true;
	}
	if (isZpushed)
	{
		PushedCounter += Scene::DeltaTime();
	}
	if (PushedCounter > ActButtonTime)
	{
		rebegin = true;
		isZpushed = false;
		PushedCounter = 0;
	}
}

void ReBegin::Draw()
{
	if (isZpushed)
	{
		FlashTimer += Scene::DeltaTime();

		if (FlashTimer > FlashInterval * 2)
		{
			FlashTimer = 0;
		}
		else
		{
			if (FlashTimer < FlashInterval)
			{
				//何も表示しない
			}
			else
			{
				Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
			}
		}
	}
	else
	{
		//ｚボタンが押されてなければ
		Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
	}	
}

//ポーズ状態解除
Restart::Restart()
{

}

Restart::Restart(m_Button button) :b(button)
{

}

Restart::~Restart() {}

void Restart::Registation(String name, Vec2 pos, int32 hight, int32 wideth, Color c, bool state, int32 Cnum)
{

}

m_Button Restart::GetButton()
{
	return b;
}

void Restart::Update()
{
	if (KeyZ.down())
	{
		isZpushed = true;
	}
	if (isZpushed)
	{
		PushedCounter += Scene::DeltaTime();
	}
	if (PushedCounter > ActButtonTime)
	{
		pause = false;
		isZpushed = false;
		PushedCounter = 0;
	}
}

void Restart::Draw()
{
	if (isZpushed)
	{
		FlashTimer += Scene::DeltaTime();

		if (FlashTimer > FlashInterval * 2)
		{
			FlashTimer = 0;
		}
		else
		{
			if (FlashTimer < FlashInterval)
			{
				//何も表示しない
			}
			else
			{
				Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
			}
		}
	}
	else
	{
		//ｚボタンが押されてなければ
		Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
	}	
}

//タイトル画面に戻る
BackToTitle::BackToTitle()
{

}

BackToTitle::BackToTitle(m_Button button): b(button)
{

}

BackToTitle::~BackToTitle()
{
	
}

void BackToTitle::Registation(String name, Vec2 pos, int32 hight, int32 wideth, Color c, bool state, int32 Cnum)
{

}

m_Button BackToTitle::GetButton()
{
	return b;
}

void BackToTitle::Update()
{
	if (KeyZ.down())
	{
		isZpushed = true;
	}
	if (isZpushed)
	{
		PushedCounter += Scene::DeltaTime();
	}
	if (PushedCounter > ActButtonTime)
	{
		BackChangeSc = true;
		isZpushed = false;
		PushedCounter = 0;
	}
	
}

void BackToTitle::Draw()
{
	if (isZpushed)
	{
		FlashTimer += Scene::DeltaTime();

		if (FlashTimer > FlashInterval * 2)
		{
			FlashTimer = 0;
		}
		else
		{
			if (FlashTimer < FlashInterval)
			{
				//何も表示しない
			}
			else
			{
				Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
			}
		}
	}
	else
	{
		//ｚボタンが押されてなければ
		Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
	}
}

//ゲームを終了
Quit::Quit()
{

}

Quit::Quit(m_Button button) :b(button)
{

}

Quit::~Quit() {}

void Quit::Registation(String name, Vec2 pos, int32 hight, int32 wideth, Color c, bool state, int32 Cnum)
{

}

m_Button Quit::GetButton()
{
	return b;
}

void Quit::Update()
{
	if (KeyZ.down())
	{
		isZpushed = true;
	}
	if (isZpushed)
	{
		PushedCounter += Scene::DeltaTime();
	}
	if (PushedCounter > ActButtonTime)
	{
		System::Exit();
		isZpushed = false;
		PushedCounter = 0;
	}
}

void Quit::Draw()
{
	if (isZpushed)
	{
		FlashTimer += Scene::DeltaTime();

		if (FlashTimer > FlashInterval * 2)
		{
			FlashTimer = 0;
		}
		else
		{
			if (FlashTimer < FlashInterval)
			{
				//何も表示しない
			}
			else
			{
				Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
			}
		}
	}
	else
	{
		//ｚボタンが押されてなければ
		Rect{ int32(b.pos.x),int32(b.pos.y),b.wideth,b.hight }.draw(ColorF(Palette::Black, 0.2));
	}
}


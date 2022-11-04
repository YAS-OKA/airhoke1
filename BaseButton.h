#pragma once
class BaseButton
{
protected:
	bool isZpushed = false;
	double PushedCounter = 0;
	double FlashTimer = 0;
	double FlashInterval = 0.05;
	double ActButtonTime = 0.5;
	bool flag = false;
	const Audio push{ U"Audios/button06.mp3" };
	const Audio driftButton{ U"Audios/ボタン移動.mp3" };
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool Getflag();
	void Setflag(bool tf);

	bool GetisZpushed();

	Audio GetAudioDriftButton() { return driftButton; };
};


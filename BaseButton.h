#pragma once
class BaseButton
{
protected:
	bool isZpushed = false;
	double PushedCounter = 0;
	double FlashTimer = 0;
	double FlashInterval = 0.05;
	double ActButtonTime = 0.5;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool GetisZpushed();
};


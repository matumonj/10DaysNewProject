#pragma once
#include"Sprite.h"
#include"Input.h"
class TutorialSprite
{
public:
	~TutorialSprite();
	static TutorialSprite* GetInstance();
private:
	static const int TaskNum = 6;
	Sprite* Task[TaskNum];
	enum TaskMenu {//‰º‚Ì”z—ñ—p—ñ‹“Œ^‚Æ‚©‚Ô‚ç‚È‚¢‚æ‚¤‚É
		TNONE,
		THELLO,
		TMOVE,
		TSETTING,
		TATTACK,
		TGETKEY,
		TEND
	};
	enum {
		HELLO,
		WALK,
		ATTACK,
		SETTING,
		GETKEY,
		CLEAR,
	};
	
	float SpriteSizeX[TaskNum] = { 0 };
	float SpriteAlpha[TaskNum];
	float t[TaskNum];
	TaskMenu task = THELLO;
	float Movement = 0;
	bool Jump;
	bool ClearWalk;
	bool ClearAttack;
	bool ClearSetting;
	bool GetChest;
	bool AllTaskClear;

	bool MassageCheck[TaskNum];
	Input* input;
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void Ease_SpriteSize_Up(float& x,float& t,int index);
	void NextTask(float t,TaskMenu nexttask,bool nextjudg);

	bool GetClearSetting() { return ClearSetting; }
};


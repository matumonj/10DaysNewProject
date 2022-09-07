#pragma once
#include"Input.h"
#include"Sprite.h"
class CustomButton
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	~CustomButton();
	static CustomButton* GetInstance();
private:
	Input* input;
	bool CustomButtonJudg;
	Sprite* Controller;
	//コントローラーボタン画像[アクション数=2][ボタン数=4]
	Sprite* ButtonSprite[4][4];
	Sprite* SelectSprite;
	Sprite* ErrorSprite;
	static const int menuNum = 4;
	Sprite* MenuSprite[menuNum];
	Sprite* ButtonFrame[menuNum];
	Sprite* Custommenu;
	XMFLOAT2 MenuSpriteSize = { 400,300 };
	XMFLOAT2 JumpSpritePosition = { 100,100 };
	XMFLOAT2 AttackSpritePosition = { 100,300 };
	XMFLOAT2 SAttackSpritePosition = { 100,500 };
	XMFLOAT2 TAttackSpritePosition = { 100,700 };
	XMFLOAT2 SelectSpritePosition[menuNum] = {
		{JumpSpritePosition.x - 100,JumpSpritePosition.y},
		{AttackSpritePosition.x - 100, AttackSpritePosition.y},
		{SAttackSpritePosition.x - 100, SAttackSpritePosition.y},
		{TAttackSpritePosition.x - 100, TAttackSpritePosition.y}
	};
private:
	XMFLOAT3 ButtonPosition[4] = {};
	int SelectNum = JUMP;
	int i = 0;
public:

	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
	//解放 Spriteもuniqueptr使いたいけど**=Sprite::Create(...)の部分どうするか
	void Fainalize();
	//ボタン設定
	void Custom_Button(bool customflag,int index);
	//設定反映部分
	void ConsiderationButton(int index);
	//コントローラーボタン描画
	void Custom_Draw();

	void ErrorJudg();
	//ボタン重複チェック用
	bool Check();

public:
	//Getter
	bool GetCustomButtonJudg() { return CustomButtonJudg; }

	//Setter
	void SetCustomButtonJudg(bool flag) { CustomButtonJudg = flag; }

private:

public:
	enum  {//各ボタン番号
		BUTTON_X=0,
		BUTTON_Y=1,
		BUTTON_A=2,
		BUTTON_B=3
	};

	enum {//各アクション番号
		JUMP=0,
		ATTACK=1,
		SATTACK=2,
		TATTACK=3,
		NONE,
	};
private:
	//アクション総数
	static const int ActionMax = 4;
	//ジャンプボタン設定フラグ
	bool JumpCustomFlag;
	bool AttackCustomFlag;
	bool SAttackCustomFlag;
	bool TAttackCustomFlag;
	bool ErrorFlag;
	//エラースプライトのアルファ値
	float ErrorSpriteAlpha=0;
	enum SelectButton {//どのアクションにどのボタン割り当てられたか保存するやつ
		SBUTTON_Y,
		SBUTTON_X,
		SBUTTON_A,
		SBUTTON_B
	};
	//各アクションの構造体(対応ボタンと、発動フラグ)
	struct ActionButton
	{
		//今選択されているボタン
		SelectButton selectButton_Before;
		SelectButton OldselectButton;
		bool judg = false;
	};
	ActionButton actionButton[ActionMax];

public:
	SelectButton GetActionButton_JUMP() {
		return actionButton[JUMP].selectButton_Before;
	}
	SelectButton GetActionButton_ATTACK() {
		return actionButton[ATTACK].selectButton_Before;
	}
	SelectButton GetActionButton_ATTACK2() {
		return actionButton[SATTACK].selectButton_Before;
	}
	SelectButton GetActionButton_ATTACK3() {
		return actionButton[TATTACK].selectButton_Before;
	}
	bool GetJumpAction() { return actionButton[JUMP].judg; }
	bool GetAttackAction() { return actionButton[ATTACK].judg; }
	void SetJumpAction(bool flag) { actionButton[JUMP].judg = flag; }
};


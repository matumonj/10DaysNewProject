#pragma once
#include"Input.h"
#include"Sprite.h"
#include<memory>
#include"ConfigSprite.h"
class SistemConfig
{
public:
	~SistemConfig();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	Sprite*SelectSprite;

	//ConfigSpriteに用意してるスプライトの数
	static const int MaxSprite = 2;

	Input* input;
	ConfigSprite* configSprite;

	//コンフィグ画面へ
	bool m_ConfigFlag;
	//スプライト座標指定用
	int m_number = 0;
	//画面がすぐ切り替わらないようにするためのカウンタ
	int count = 0;
	
public:
	static SistemConfig* GetInstance();

	enum Config
	{
		HUDRAYOUT,
		CUSTOMBUTTON,
		ENEMYHP,
		SWORDSELECT,
		END
	};
	Config GetNowSelect() { return config; }
	Config config;
	float sAlpha = 0;
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画
	void Draw();

private:
	Config NowSelectButton();
	bool EndConfigJudg;
public:
	bool GetEndConfig() { return EndConfigJudg; }
	bool GetConfigJudgMent() { return m_ConfigFlag; }
};


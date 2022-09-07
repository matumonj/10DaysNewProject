#pragma once
#include<memory>
#include"Sprite.h"
class ConfigSprite
{
public:
	~ConfigSprite();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	//コンフィグ内に用意するスプライトの枚数
	static const int MaxSprite = 3;
	//各スプライト間の間隔
	const float Space = 200.0f;
	//HUDレイアウト
	Sprite*RayOutSprite;
	//敵の体力表示
	Sprite*EnemyHPSelectSprite;
	//剣
	Sprite* SwordSelectSprite;
	Sprite* MenuSprite;
	XMFLOAT2 SpritePosition[MaxSprite] = { {300,200},{300,350},{300,500} };
public:
	static ConfigSprite* GetInstance();

	XMFLOAT2 GetSpritePosition(int number) { return SpritePosition[number]; }
	void Initialize();

	void Update();

	void Draw();
};


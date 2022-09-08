#pragma once
#include"Sprite.h"
class Feed
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	static Feed* GetInstance();
	~Feed();
public:

	enum feedtype {
		FEEDIN,
		FEEDOUT
	};

	void initialize();

	void Update_White(feedtype type);

	void Update_Black(feedtype type);

	void Draw();

	float GetAlpha() { return feedalpha; }
private:
	Sprite* FeedSprite;
	XMFLOAT3 rgbcolor = {1,1,1};
	float feedalpha=0;
	feedtype type;
};


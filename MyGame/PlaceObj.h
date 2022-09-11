#include"WinApp.h"
#include"Object3d.h"
#include"Model.h"

class PlaceObj
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
	static PlaceObj* GetInstance();
	void Init();

	void Update();

	void Draw();
	XMVECTOR wDivision(XMVECTOR vec, XMMATRIX mat);
private:
	Object3d* obj;
	Model* mod;
	XMVECTOR Pos3d;
	POINT p;
	float x, y;
public:
	XMVECTOR Getpos() { return Pos3d; }
};
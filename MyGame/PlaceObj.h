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
	void Init();

	void Update();

	XMVECTOR wDivision(XMVECTOR vec, XMMATRIX mat);
private:
	POINT p;
};
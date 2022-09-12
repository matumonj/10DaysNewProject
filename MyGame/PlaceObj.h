#include"WinApp.h"
#include"Object3d.h"
#include"Model.h"
#include"Sprite.h"
#include"Player.h"
#include"Bench.h"
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
	void Update(Sushi* sushis);
	void Draw();
private:
	enum {
		NON_CHARA = 0,
		ONE_GIRL,
		TWO_CAT,
		THREE_DOG,
		FOUR_BIRD,
		MAX_CHARA
	};

	enum {
		LEFT_UP = 0,
		LEFT_CENTER,
		LEFT_BOTTOM,
		RIGHT_UP,
		RIGHT_CENTER,
		RIGHT_BOTTOM,
		CENTER_UP,
		CENTER_BOTTOM,
		MAXBENCH,
	};

private:
	Object3d* obj;
	Model* mod;
	Sprite* CharaSprite[MAX_CHARA];
	XMFLOAT3 DebPos;
	bool Createf;
	XMVECTOR Pos3d;
	XMVECTOR Pos3dz;
	POINT p;
	float x, y;
	bool Clickf[MAX_CHARA];

	std::vector<Player*>players;


	struct BenchState {
		XMFLOAT2 Position_2d;
		XMFLOAT3 Position_3d;
		int SitChara=NON_CHARA;
		float LeaveLimit;
		float LeaveLimit_Max;
	};
	int ClickChara;

	BenchState benchState[MAXBENCH];
public:

	XMVECTOR Getpos() { return Pos3d; }
	void CreateObj(const int& charanum);
	void SpriteStartPos(const int& charanum);
	void PlaceChara(const int& charanum);
	void SetIconSpritePos();
	void LeaveStore();
	//ÉxÉìÉ`ÉLÉÉÉâ
private:
	std::vector<std::unique_ptr<Bench>> Benchs;
	XMFLOAT3 BenchPos[MAXBENCH]
		= {
 {-15,-43,20},{-15,-43,10}, {-15,-43,0}
,{ 15,-43,20},{ 15,-43,10}, { 15,-43,0},
 {0,-43,20},{0,-43,0}};

};
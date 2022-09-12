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
	Object3d* obj;
	Model* mod;
	Sprite* CharaSprite[4];
	bool Createf;
	XMVECTOR Pos3d;
	XMVECTOR Pos3dz;
	POINT p;
	float x, y;
	bool Clickf[4];

	std::vector<Player*>players;
private:
	enum  {
		ONE_GIRL,
		TWO_CAT,
		THREE_DOG,
		FOUR_BIRD
	};
	enum SittingChara {
		NON,
		PLAYER,
		CAT,
		DOG,
		BIRD
	};
	enum ClickChara {
		CNON,
		CPLAYER,
		CCAT,
		CDOG,
		CBIRD
	};
	struct BenchState {
		XMFLOAT2 Position_2d;
		XMFLOAT3 Position_3d;
		SittingChara schara=NON;
	};
	ClickChara cChara;

	BenchState Bench_LU;//ç∂è„
	BenchState Bench_LB;//
	BenchState Bench_LC;//
	BenchState Bench_RU;// 
	BenchState Bench_RB;//
	BenchState Bench_RC;//
	BenchState Bench_CU;//
	BenchState Bench_CB;//

	
	public:

	XMVECTOR Getpos() { return Pos3d; }
	void CreateObj(int charanum);
	void SpriteStartPos(int charanum);
	void PlaceChara(int charanum);
	void SetIconSpritePos();
	//ÉxÉìÉ`ÉLÉÉÉâ
private:
	std::vector<std::unique_ptr<Bench>> Benchs;
	XMFLOAT3 BenchPos[2][3]
		= {
		{ {15,-43,20}, {0,-43,20}, {-15,-43,20}},
		{ {15,-43,0}, {15,-43,0}, {-15,-43,0}},
	};
};
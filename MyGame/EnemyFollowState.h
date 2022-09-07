#pragma once
#include"EnemyState.h"
#include"Enemy.h"
class EnemyFollowState :public EnemyState
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ğÈ—ª
	using XMVECTOR = DirectX::XMVECTOR;

public:
	void Initialize(Enemy* enemy)override;

	void Update(Enemy* enemy)override;

private:
	float RotY;
};

#include "SushiMove.h"
#include"Collision.h"
#include"mHelper.h"

SushiMove* SushiMove::GetInstance()
{
	static SushiMove ins;
	return &ins;
}
void SushiMove::Wave1or2move(Sushi* sushi)
{
	switch (SMove)
	{
	case SushiMove::GATE:
		rot.y = 0;
		position = GatePos;
		SMove = LANE;

		scale = { 2,2,2 };
		break;
	case SushiMove::LANE:
		//ˆÚ“®ƒxƒNƒgƒ‹‚ğy²ü‚è‚ÌŠp“x‚Å‰ñ“]
		//RotState();]
		Wave1or2Rot();
		move = { 0,0,0.1f,0 };

		matRot = XMMatrixRotationY(XMConvertToRadians(rot.y));

		move = XMVector3TransformNormal(move, matRot);

		position = { position.x + move.m128_f32[0],position.y,	position.z + move.m128_f32[2] };
		//”pŠüğŒ
		isDump = Collision::GetLength(position, GarbagepPos) < 2.0f;
		//‰ñ“]”¼Œa
		if (isDump) {
			SMove = DUMP;
		}

		break;
	case SushiMove::DUMP:
		for (int i = 0; i < 5; i++) {
			RotTime[i] = 0;
		}
		position.y -= 0.2f;
		if (position.y < -60) {
			SMove = DEAD;
		}
		break;
	case SushiMove::DEAD:
		sushi->SetDead(true);
		
		break;
	default:
		break;
	}

	sushi->SetPos(position);
	sushi->SetRot(rot);
}

void SushiMove::Wave3move(Sushi* sushi)
{
	switch (SMove)
	{
	case SushiMove::GATE:
		rot.y = -90;
		position = GatePos_Right;
		SMove = LANE;

		break;
	case SushiMove::LANE:
		Wave3Rot();
		//ˆÚ“®ƒxƒNƒgƒ‹‚ğy²ü‚è‚ÌŠp“x‚Å‰ñ“]
		//RotState();
		move = { 0,0,0.1f,0 };

		matRot = XMMatrixRotationY(XMConvertToRadians(rot.y));

		move = XMVector3TransformNormal(move, matRot);

		position = { position.x + move.m128_f32[0],position.y,	position.z + move.m128_f32[2] };
		//”pŠüğŒ
		isDump = Collision::GetLength(position, GarbagepPos) < 2.0f;
		//‰ñ“]”¼Œa
		if (isDump) {
			SMove = DUMP;
		}
		break;
	case SushiMove::DUMP:
		for (int i = 0; i < 5; i++) {
			RotTime[i] = 0;
		}
		position.y -= 0.2f;
		if (position.y < -60) {
			SMove = DEAD;
		}
		break;
	case SushiMove::DEAD:
		scale.x -= 0.2f;
		scale.y -= 0.2f;
		scale.z -= 0.2f;
		if (scale.x < 0) {
			//delete HPTex;
			//Destroy_unique(SushiObj);
		}
		break;
	default:
		break;
	}
	sushi->SetPos(position);
	sushi->SetRot(rot);
}

void SushiMove::Wave1or2Rot()
{
	if (Collision::GetLength(position, { 0,-40,5 }) < 1.0f) {
		RotTime[0] += 0.2f;
		if (RotTime[0] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[0], 0, 90);
		}
	}
	if (Collision::GetLength(position, { 20,-40,5 }) < 1.0f) {
		RotTime[1] += 0.2f;
		if (RotTime[1] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[1], 90, 0);
		}
	}
	if (Collision::GetLength(position, { 20,-40,27 }) < 1.0f) {
		RotTime[2] += 0.2f;
		if (RotTime[2] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[2], 0, -90);
		}
	}
	if (Collision::GetLength(position, { -20,-40,27 }) < 1.0f) {
		RotTime[3] += 0.2f;
		if (RotTime[3] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[3], -90, -180);
		}
	}
	if (Collision::GetLength(position, { -20,-40,5 }) < 1.0f) {
		RotTime[4] += 0.2f;
		if (RotTime[4] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[4], -180, -270);
		}
	}
}
void SushiMove::Wave3Rot()
{
	if (Collision::GetLength(position, { 20,-40,10 }) < 1.0f) {
		RotTime[0] += 0.2f;
		if (RotTime[0] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[0], -90, 0);
		}
	}
	if (Collision::GetLength(position, { 20,-40,27}) < 1.0f) {
		RotTime[1] += 0.2f;
		if (RotTime[1] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[1], 0, -90);
		}
	}
	if (Collision::GetLength(position, { -20,-40,27}) < 1.0f) {
		RotTime[2] += 0.2f;
		if (RotTime[2] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[2], -90, -180);
		}
	}
	if (Collision::GetLength(position, { -20,-40,5 }) < 1.0f) {
		RotTime[3] += 0.2f;
		if (RotTime[3] <= 1.0f) {
			rot.y = Easing::EaseOut(RotTime[3], -180, -270);
		}
	}
}
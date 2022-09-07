
#include "CameraControl.h"
#include<windows.h>
#include"Feed.h"
#include"SceneManager.h"
#include"PlayerControl.h"
CameraControl* CameraControl::GetInstance()
{
	static CameraControl instance;
	return &instance;
}
void CameraControl::Initialize(DebugCamera* camera)
{
	this->camera = new DebugCamera(WinApp::window_width, WinApp::window_height);//(/*input*/);
	input = Input::GetInstance();
}

void CameraControl::Load(DebugCamera* camera)
{
	
}

void CameraControl::Update(DebugCamera* camera)
{
	
	nowCount = GetTickCount();
	elapsedCount = nowCount - startCount;
	float elapsedTime = static_cast<float>(elapsedCount) / 1000.0f;

	timerate = elapsedTime / maxtime;


	if (input->Pushkey(DIK_RIGHT)) {
		charaAngle += 0.5f;
		cameraAngle -= 0.5f;
		PlayerControl::GetInstance()->GetPlayer()->SetCharaRotation(charaAngle);
	} else if (input->Pushkey(DIK_LEFT) || input->RightTiltStick(input->Left)) {
		cameraAngle += 0.5f;
		charaAngle -= 0.5f;
		PlayerControl::GetInstance()->GetPlayer()->SetCharaRotation(charaAngle);
	}
	if (cameraAngle >= 360 + 90 || cameraAngle <= -360) {
		cameraAngle = 0;
	}

		//this->camera->SetEye(CameraPosition);
	this->camera->SetTarget({ PlayerControl::GetInstance()->GetPlayer()->GetPosition() });
	this->camera->Update();

}

void CameraControl::Draw()
{

}

void CameraControl::SetColor(XMFLOAT4 color)
{

}
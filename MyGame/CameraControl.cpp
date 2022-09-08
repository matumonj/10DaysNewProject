
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
	if (input->Pushkey(DIK_RIGHT)) {
		charaAngle += 0.5f;
		cameraAngle -= 0.5f;
			} else if (input->Pushkey(DIK_LEFT) || input->RightTiltStick(input->Left)) {
		cameraAngle += 0.5f;
		charaAngle -= 0.5f;
		}
	if (cameraAngle >= 360 + 90 || cameraAngle <= -360) {
		cameraAngle = 0;
	}

	this->camera->SetEye({0,0,-20});
	this->camera->SetTarget({ 0,0,0 });
	this->camera->Update();

}

void CameraControl::Draw()
{

}

void CameraControl::SetColor(XMFLOAT4 color)
{

}
#include"PlaceObj.h"
#include"CameraControl.h"
void PlaceObj::Init()
{

}

void PlaceObj::Update()
{
	XMMATRIX matViewPort = XMMatrixIdentity();
	matViewPort.r[0].m128_f32[0] = (float)WinApp::window_width / 2.0f;
	matViewPort.r[1].m128_f32[1] = -1.0f * (float)(WinApp::window_height / 2.0f);
	matViewPort.r[2].m128_f32[2] = 1.0f;
	matViewPort.r[3].m128_f32[0] = (float)WinApp::window_width / 2.0f;
	matViewPort.r[3].m128_f32[1] = (float)WinApp::window_height / 2.0f;
	matViewPort.r[3].m128_f32[3] = 1.0f;
	//マウス座標の取得
	GetCursorPos(&p);
	ScreenToClient(FindWindowA("DirectX", nullptr), &p);
	
	HWND hwnd = WinApp::GetIns()->GetHwnd();
	ScreenToClient(hwnd, &p);
	XMMATRIX matVPV = CameraControl::GetInstance()->GetCamera()->GetViewMatrix() *
		CameraControl::GetInstance()->GetCamera()->GetProjectionMatrix() * matViewPort;

	XMMATRIX matVPVIn = XMMatrixInverse(nullptr, matVPV);

	XMVECTOR posnear = { (float)p.x,(float)p.y,0 };

	XMVECTOR posfar = { (float)p.x,(float)p.y,1 };

	posnear = wDivision(posnear, matVPVIn);
	posfar = wDivision(posfar, matVPVIn);
	XMVECTOR mouseDirection = posfar - posnear;
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 40.0f;
	
	XMVECTOR Pos3d = (mouseDirection + posnear) * kDistanceTestObject;

}


XMVECTOR PlaceObj::wDivision(XMVECTOR vec, XMMATRIX mat)
{
	float x, y, z, w;

	x = (vec.m128_f32[0] * mat.r[0].m128_f32[0]) + (vec.m128_f32[1] * mat.r[1].m128_f32[0]) + (vec.m128_f32[2] * mat.r[2].m128_f32[0]) + (1.0f * mat.r[3].m128_f32[0]);
	y = (vec.m128_f32[0] * mat.r[0].m128_f32[1]) + (vec.m128_f32[1] * mat.r[1].m128_f32[1]) + (vec.m128_f32[2] * mat.r[2].m128_f32[1]) + (1.0f * mat.r[3].m128_f32[1]);
	z = (vec.m128_f32[0] * mat.r[0].m128_f32[2]) + (vec.m128_f32[1] * mat.r[1].m128_f32[2]) + (vec.m128_f32[2] * mat.r[2].m128_f32[2]) + (1.0f * mat.r[3].m128_f32[2]);
	//w = (vec.m128_f32[0] * mat.r[0].m128_f32[2]) + (vec.m128_f32[1] * mat.r[1].m128_f32[2]) + (vec.m128_f32[2] * mat.r[2].m128_f32[2]) + (1.0f * mat.r[3].m128_f32[2]);
	w = 1;
	//w = z;
	x = x / w;
	y = y / w;
	z = z / w;

	return XMVECTOR{ x, y, z, w };
}
#include"PlaceObj.h"
#include"CameraControl.h"

PlaceObj* PlaceObj::GetInstance()
{
	static PlaceObj ins;
	return &ins;
}
void PlaceObj::Init()
{
	mod = Model::CreateFromOBJ("Tuna");
	obj = new Object3d();
	obj->SetModel(mod);
	obj->Initialize(CameraControl::GetInstance()->GetCamera());
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
	x=Input::GetInstance()->GetMousePoint().x;
	y = Input::GetInstance()->GetMousePoint().y;
	XMMATRIX matVPV = CameraControl::GetInstance()->GetCamera()->GetViewMatrix() *
		CameraControl::GetInstance()->GetCamera()->GetProjectionMatrix() * matViewPort;

	XMMATRIX matVPVIn = XMMatrixInverse(nullptr, matVPV);

	XMVECTOR posnear = { x,y,-20 };

	XMVECTOR posfar = { x,y,100 };

	posnear = wDivision(posnear, matVPVIn);
	posfar = wDivision(posfar, matVPVIn);
	XMVECTOR mouseDirection = posfar - posnear;
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = Collision::GetLength(obj->GetPosition(), CameraControl::GetInstance()->GetCamera()->GetEye());
	
	Pos3d = (mouseDirection + posnear)*(kDistanceTestObject+2);
 obj->SetScale({ 3,3,3 });
 obj->SetPosition({ Pos3d.m128_f32[0],-20, Pos3d.m128_f32[1]});
 obj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
}

void PlaceObj::Draw()
{
	obj->PreDraw();
	obj->Draw();
	obj->PostDraw();
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
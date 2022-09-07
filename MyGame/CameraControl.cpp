
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
	file.open("Param_CSV/CameraPoints.csv");

	popcom << file.rdbuf();

	file.close();

	while (std::getline(popcom, line)) {
		std::istringstream line_stream(line);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Points_Quantity") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			Quantity = quantity;
			break;
		}
	}
	Num.resize(Quantity);
	pos.resize(Quantity);
	for (int i = 0; i < Quantity; ++i) {
		while (std::getline(popcom, line)) {
			std::istringstream line_stream(line);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("POP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				pos[i] = { x,y,z };
				break;
			}
		}
	}
	points.push_back(pos[0]);
	points.push_back(pos[0]);
	for (int i = 1; i < Quantity - 1; i++) {
		points.push_back(pos[i]);
	}
	int quantity_end = Quantity - 1;
	points.push_back(pos[quantity_end]);
	points.push_back(pos[quantity_end]);

	//Load_ChestPosition.resize(Quantity);
	this->camera->SetEye(pos[0]);
	UpdateRange = 200;
	startCount = GetTickCount();
}

void CameraControl::Update(DebugCamera* camera)
{
	
	nowCount = GetTickCount();
	elapsedCount = nowCount - startCount;
	float elapsedTime = static_cast<float>(elapsedCount) / 1000.0f;

	timerate = elapsedTime / maxtime;
	if (timerate >= 1) {
		if (startindex < points.size() - 3)
		{
			startindex++;
			timerate -= 1;

			startCount = GetTickCount();
		} else
		{
			timerate = 1;
		}
	}

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

	
	CameraPosition.x = PlayerControl::GetInstance()->GetPlayer()->GetPosition().x + cosf((float)(cameraAngle) * 3.14f / 180.0f) * 25;
	CameraPosition.z = PlayerControl::GetInstance()->GetPlayer()->GetPosition().z + sinf((float)(cameraAngle) * 3.14f / 180.0f) * 25;;
	CameraPosition.y = PlayerControl::GetInstance()->GetPlayer()->GetPosition().y + CameraHeight;

		//this->camera->SetEye(CameraPosition);
	this->camera->SetTarget({ PlayerControl::GetInstance()->GetPlayer()->GetPosition() });
	this->camera->Update();

	if(Tstate==SPLINE){
		this->camera->SetEye(SplinePosition(points, startindex, timerate));
	}
	else if (Tstate == PLAYER) {
		this->camera->SetEye(CameraPosition);
	}
}

XMFLOAT3 CameraControl::SplinePosition(const std::vector<XMFLOAT3>& points, size_t startindex, float t)
{
	size_t n = points.size() - 2;
	if (startindex > n)return points[n];
	if (startindex < 1)return points[1];

	XMFLOAT3 p0 = points[startindex - 1];
	XMFLOAT3 p1 = points[startindex];
	XMFLOAT3 p2 = points[startindex + 1];
	XMFLOAT3 p3 = points[startindex + 2];

	XMFLOAT3 a, b, c, d, e, f, g, h, i;
	XMFLOAT3 a1, b1, c1, d1, b4;
	float ext, ext2;
	ext = (t * t);
	ext2 = (t * t * t);
	a = XMFLOAT3(p1.x * 2, p1.y * 2, p1.z * 2);
	b = XMFLOAT3((-p0.x + p2.x) * t, (-p0.y + p2.y) * t, (-p0.z + p2.z) * t);
	c = XMFLOAT3(2 * p0.x, 2 * p0.y, 2 * p0.z);
	d = XMFLOAT3(5 * p1.x, 5 * p1.y, 5 * p1.z);
	e = XMFLOAT3(4 * p2.x, 4 * p2.y, 4 * p2.z);
	f = XMFLOAT3(-p0.x, -p0.y, -p0.z);
	g = XMFLOAT3(3 * p1.x, 3 * p1.y, 3 * p1.z);
	h = XMFLOAT3(3 * p2.x, 3 * p2.y, 3 * p2.z);

	//1‚¬‚å‚¤‚ß
	a1 = { a.x + b.x,a.y + b.y,a.z + b.z };
	//2
	b1 = { c.x - d.x,c.y - d.y ,c.z - d.z };
	c1 = { (b1.x + e.x - p3.x) * ext ,(b1.y + e.y - p3.y) * ext  ,(b1.z + e.z - p3.z) * ext };

	d1 = { (f.x + g.x - h.x + p3.x) * ext2,(f.y + g.y - h.y + p3.y) * ext2,(f.z + g.z - h.z + p3.z) * ext2 };
	b4 = { (a1.x + c1.x),(a1.y + c1.y)  ,(a1.z + c1.z) };
	XMFLOAT3 ys;
	ys = { b4.x + d1.x,b4.y + d1.y ,b4.z + d1.z };
	XMFLOAT3 position = { 0.5f * ys.x,0.5f * ys.y ,0.5f * ys.z };
	/*	XMFLOAT3 position = 0.5f * ((2 * p1) + (-p0 + p2) * t +
		(2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) +
		(-p0 + 3 * p1 - 3 * p2 + p3) * (t * t * t));
*/
//return position;
	return position;
}

void CameraControl::Draw()
{

}

void CameraControl::SetColor(XMFLOAT4 color)
{

}
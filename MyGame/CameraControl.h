#include"DebugCamera.h"
#include<windows.h>
#include "ControlBase.h"
#include"Input.h"
class CameraControl :
    public ControlBase
{
public:
    static CameraControl* GetInstance();
	void Load(DebugCamera* camera)override;

	void Initialize(DebugCamera* camera)override;

	void Update(DebugCamera* camera)override;

	void Draw()override;

    DebugCamera* GetCamera() { return camera; }
    enum TargetState {
        PLAYER,
        TUTORIAL,
        SPLINE
    };
private:
    Input* input;
    DebugCamera*camera;
    int pointsindex = 6;
    std::vector<XMFLOAT3>p;
    XMFLOAT3 p0 = { -100, 0, 0 };
    XMFLOAT3 p1 = { -10, 0, 50 };
    //XMFLOAT3 p2(10, 0, -50);
    //XMFLOAT3 p3(100, 0, 0);
    XMFLOAT3 pos1;
    XMFLOAT3 pos2;
    XMFLOAT3 start = { -100, 0, 0 };
    XMFLOAT3 p2 = { -50, 50, 50 };
    XMFLOAT3 p3 = { 50, -30, -50 };
    XMFLOAT3 end = { 100, 0, 0
    };
    size_t startindex = 1;
    std::vector<XMFLOAT3>points;// { start, start, p2, p3, end, end };
    long long startCount = 0;
    long long nowCount = 0;
    long long elapsedCount = 0;
    //XMFLOAT3 start(-100, 0, 0);
    //XMFLOAT3 end(100, 0, 0);
    float maxtime = 6;
    float timerate;

    long long time = 0.00000f;
    long long j = time;

private:
    bool splinef;
    std::vector<std::unique_ptr<XMFLOAT3>>cpoints;
    std::vector <XMFLOAT3>Load_CameraPoints;

    XMFLOAT3 SplinePosition(const std::vector<XMFLOAT3>& points, size_t startindex, float t);

    TargetState Tstate;
    XMFLOAT3 CameraPosition;
    float cameraAngle=-90;
    float charaAngle;
    float CameraDis = 25;
    float CameraHeight=9;
public: 

    XMFLOAT3 CameraPosIndex(int index) { return points[index]; }
    void SetCameraState(TargetState state) { Tstate = state; }
    void move(XMFLOAT3& pos);
    void SetColor(XMFLOAT4 color)override;
   
};

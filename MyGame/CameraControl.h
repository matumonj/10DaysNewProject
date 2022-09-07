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
   
    size_t startindex = 1;
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
    float cameraAngle=-90;
    float charaAngle;
    float CameraDis = 25;
    float CameraHeight=9;
public: 

    void move(XMFLOAT3& pos);
    void SetColor(XMFLOAT4 color)override;
   
};

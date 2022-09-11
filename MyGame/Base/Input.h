#pragma once
#include<Windows.h>
#include<wrl.h>
#include<dinput.h>
#include"WinApp.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
using namespace Microsoft::WRL;

class Input
{
private:

	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keypre[256] = {};


	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};

	WinApp* winapp = nullptr;
public:
	static Input* GetInstance();
	~Input();
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};
	
	//ゲームパッド（ボタン）
	enum ButtonKind
	{
		Button_A,
		Button_B,
		Button_X,
		Button_Y,
		Button_LB,
		Button_RB,
		Select,
		Start,
		Button_LeftStick,
		Button_RightStick,
		Cross_Up,
		Cross_Down,
		Cross_Right,
		Cross_Left,
		ButtonMax
	};

	//スティック
	enum StickKind
	{
		Up, Down, Right, Left
	};

	//初期化
	void Initialize(WinApp* winapp);
	//更新
	void update();
	//キーの押下をチェック
	bool Pushkey(BYTE keyNumber);
	//キーのトリガー判定
	bool TriggerKey(BYTE keyNumber);


	/// <summary>
	/// キーの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseLeft();

	/// <summary>
	/// キーの中ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// キーの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// キーの中ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseMiddle();

	/// <summary>
	/// マウス移動量を取得
	/// </summary>
	/// <returns>マウス移動量</returns>
	MouseMove GetMouseMove();
	POINT mpoint;
public:
	//ゲームパッド
	bool LeftTiltStick(int stick);
	bool LeftTriggerStick(int stick);
	bool RightTiltStick(int stick);
	bool RightTriggerStick(int stick);
	bool PushButton(int Button);
	bool TriggerButton(int Button);
	bool PushCrossKey(int CrossKey);
	bool TriggerCrossKey(int CrossKey);
	POINT GetMousePoint();
public:
	const LONG& GetPositionX() { return  gamePadState2.lX; }
	const LONG& GetPositionY() { return  gamePadState2.lY; }
	const float& GetPosX() { return posX; }
	const float& GetPosY() { return posY; }

	private:
		//ゲームパッドデバイス
		ComPtr<IDirectInputDevice8> devGamePad;
		DIJOYSTATE2 gamePadState = {};
		DIJOYSTATE2 oldGamePadState = {};
		DIJOYSTATE2 gamePadState2 = {};
		DIJOYSTATE2 oldGamePadState2 = {};
		bool is_push[32] = {};
		//スティックの無反応範囲
		LONG unresponsive_range = 640;
		LONG unresponsive_range2 = 200;
		float posX = 0;
		float posY = 0;

};


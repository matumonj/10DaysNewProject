#pragma once
#include<fstream>
#include<string>
#include<sstream>
#include<ostream>
#include <iostream>
#include"Model.h"
#include"Object3d.h"
#include"DebugCamera.h"
class CreateObjManager
{
protected:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	virtual ~CreateObjManager();

	virtual void Initialize(DebugCamera*camera)=0;

	virtual void ArgMent(DebugCamera* camera)=0;

	virtual void Update(DebugCamera* camera)=0;

	virtual void FileWriting()=0;

	virtual void ImGui_Draw()=0;

	virtual void Draw()=0;

	virtual bool ErrorJudg()=0;
	
protected:
	std::vector<int>Number;
	std::ifstream file;
	std::stringstream popcom;
	//配置フラグ
	bool ArgmentFlag;
	//削除フラグ
	bool DeleteFlag;
	//配置オブジェクト、モデル
	Model* Model;
	Object3d* Obj;

	//
	std::vector<XMFLOAT3>Position;
	std::vector<XMFLOAT3>Rotation;
	std::vector<XMFLOAT3>Scale;
	//
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scl;

};


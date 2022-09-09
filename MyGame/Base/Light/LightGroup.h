#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

#include "DirectionalLight.h"
#include "PointLight.h"
#include"SpotLight.h"
/// <summary>
/// ���C�g
/// </summary>
class LightGroup
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �萔
	// ���s�����̐�
	static const int DirLightNum = 3;
	// �_�����̐�
	static const int PointLightNum = 3;

	static const int SpotLightNum = 3;

public: // �T�u�N���X

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		// �����̐F
		XMFLOAT3 ambientColor;
		float pad1;
		// ���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		// �_�����p
		PointLight::ConstBufferData pointLights[PointLightNum];
		//�X�|�b�g���C�g
		SpotLight::ConstBufferData spotLights[SpotLightNum];
	};
public:
	//�X�|�b�g���C�g
	void SetSpotLightActive(int index, bool active);
	void SetSpotLightDir(int index, const XMVECTOR& lightdir);
	void SetSpotLightPos(int index, const XMFLOAT3& lightpos);
	void SetSpotLightColor(int index, const XMFLOAT3& lightcolor);
	void SetSpotLightAtten(int index, const XMFLOAT3& lightAtten);
	void SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle);

	SpotLight spotLights[SpotLightNum];
public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize();

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static LightGroup* Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ComPtr<ID3D12Device> device;
	static ComPtr<ID3D12GraphicsCommandList> cmdList;
public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(UINT rootParameterIndex);

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// �W���̃��C�g�ݒ�
	/// </summary>
	void DefaultLightSetting();

	/// <summary>
	/// �����̃��C�g�F���Z�b�g
	/// </summary>
	/// <param name="color">���C�g�F</param>
	void SetAmbientColor(const XMFLOAT3& color);

	/// <summary>
	/// ���s�����̗L���t���O���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="active">�L���t���O</param>
	void SetDirLightActive(int index, bool active);

	/// <summary>
	/// ���s�����̃��C�g�������Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightdir">���C�g����</param>
	void SetDirLightDir(int index, const XMVECTOR& lightdir);

	/// <summary>
	/// ���s�����̃��C�g�F���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightcolor">���C�g�F</param>
	void SetDirLightColor(int index, const XMFLOAT3& lightcolor);

	/// <summary>
	/// �_�����̗L���t���O���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="active">�L���t���O</param>
	void SetPointLightActive(int index, bool active);

	/// <summary>
	/// �_�����̃��C�g���W���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightpos">���C�g���W</param>
	void SetPointLightPos(int index, const XMFLOAT3& lightpos);

	/// <summary>
	/// �_�����̃��C�g�F���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightcolor">���C�g�F</param>
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);

	/// <summary>
	/// �_�����̃��C�g���������W�����Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightatten">���C�g���������W��</param>
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

	void LightSetting();

	void SpotLightUpdate();

	void SetSpotLightPos(float pos[3]) { for (int i = 0; i < 3; i++) { spotLightpos[i] = pos[i]; } }

	void SetSpotLightColor(float color[3]) { for (int i = 0; i < 3; i++) { spotLightColor[i] = color[i]; } }

private: // �����o�ϐ�

	int SpotLightflag = false;
private://�X�|�b�g���C�g
	float spotLightDir[3] = { 0,-1,0 };
	float spotLightpos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;

	// �����̐F
	XMFLOAT3 ambientColor = { 1,1,1 };

	// ���s�����̔z��
	DirectionalLight dirLights[DirLightNum];

	// �_�����̔z��
	PointLight pointLights[PointLightNum];

	// �_�[�e�B�t���O
	bool dirty = false;
};

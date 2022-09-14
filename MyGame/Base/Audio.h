#pragma once

#include <Windows.h>
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <wrl.h>

#include<fstream>
#include<cassert>
#include<string>
#include<list>

/// <summary>
/// �I�[�f�B�I�R�[���o�b�N
/// </summary>
class XAudio2VoiceCallback : public IXAudio2VoiceCallback {
public:
	// �{�C�X�����p�X�̊J�n��
	//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
	void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
	// �{�C�X�����p�X�̏I����
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
	// �o�b�t�@�X�g���[���̍Đ����I��������
	STDMETHOD_(void, OnStreamEnd) (THIS) {};
	// �o�b�t�@�̎g�p�J�n��
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
	// �o�b�t�@�̖����ɒB������
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
		// �o�b�t�@���������
		delete[] pBufferContext;
	};
	// �Đ������[�v�ʒu�ɒB������
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
	// �{�C�X�̎��s�G���[��
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

/// <summary>
/// �I�[�f�B�I
/// </summary>
class Audio {
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public: // �T�u�N���X
	// �`�����N�w�b�_
	struct Chunk 	{
		char	id[4]; // �`�����N����ID
		int		size;  // �`�����N�T�C�Y
	};

	// RIFF�w�b�_�`�����N
	struct RiffHeader 	{
		Chunk	chunk;   // "RIFF"
		char	type[4]; // "WAVE"
	};

	// FMT�`�����N
	struct FormatChunk 	{
		Chunk		chunk; // "fmt "
		WAVEFORMAT	fmt;   // �g�`�t�H�[�}�b�g
	};

public: // �����o�֐�
	static Audio* GetInstance();
	std::list< Audio>audios;
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize();
	// �T�E���h�t�@�C���̓ǂݍ��݂ƍĐ�
	void LoadSound(int texnumber, const char* filename);
	void PlayWave(const char* filename, const float Volume);
	void LoopWave(int texnumber, float Volume);
	void StopWave(int texnumber);
private: // �����o�ϐ�
	static const int srvCount = 10;
	// �T�E���h�ԍ�
	int texNumber = 0;
	RiffHeader riff[srvCount] = {};
	FormatChunk format[srvCount] = {};
	Chunk data[srvCount] = {};
	char* pBuffer[srvCount] = {}; 
	WAVEFORMATEX wfex[srvCount]{};
	IXAudio2SourceVoice* pSourceVoice[srvCount] = { nullptr };
	XAUDIO2_BUFFER buf[srvCount]{};
	char fileStamp[srvCount][50]{};
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	XAudio2VoiceCallback voiceCallback;
};


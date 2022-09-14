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
/// オーディオコールバック
/// </summary>
class XAudio2VoiceCallback : public IXAudio2VoiceCallback {
public:
	// ボイス処理パスの開始時
	//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
	void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
	// ボイス処理パスの終了時
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
	// バッファストリームの再生が終了した時
	STDMETHOD_(void, OnStreamEnd) (THIS) {};
	// バッファの使用開始時
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
	// バッファの末尾に達した時
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
		// バッファを解放する
		delete[] pBufferContext;
	};
	// 再生がループ位置に達した時
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
	// ボイスの実行エラー時
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

/// <summary>
/// オーディオ
/// </summary>
class Audio {
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public: // サブクラス
	// チャンクヘッダ
	struct Chunk 	{
		char	id[4]; // チャンク毎のID
		int		size;  // チャンクサイズ
	};

	// RIFFヘッダチャンク
	struct RiffHeader 	{
		Chunk	chunk;   // "RIFF"
		char	type[4]; // "WAVE"
	};

	// FMTチャンク
	struct FormatChunk 	{
		Chunk		chunk; // "fmt "
		WAVEFORMAT	fmt;   // 波形フォーマット
	};

public: // メンバ関数
	static Audio* GetInstance();
	std::list< Audio>audios;
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize();
	// サウンドファイルの読み込みと再生
	void LoadSound(int texnumber, const char* filename);
	void PlayWave(const char* filename, const float Volume);
	void LoopWave(int texnumber, float Volume);
	void StopWave(int texnumber);
private: // メンバ変数
	static const int srvCount = 10;
	// サウンド番号
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


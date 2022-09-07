#include "Audio.h"
#include <fstream>
#include <cassert>

#pragma comment(lib,"xaudio2.lib")

bool Audio::Initialize() {
	HRESULT result;

	// XAudioエンジンのインスタンスを生成
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result) {
		assert(0);
		return false;
	}

	// マスターボイスを生成
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	if FAILED(result) {
		assert(0);
		return false;
	}

	return true;
}

void Audio::PlayWave(const char* filename, const float Volume) {
	HRESULT result;
	// ファイルストリーム
	std::ifstream file;
	// Waveファイルを開く
	file.open(filename, std::ios_base::binary);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	// RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	// Dataチャンクの読み込み
	Chunk data;
	file.read((char*)&data, sizeof(data));

	// Dataチャンクのデータ部（波形データ）の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// Waveファイルを閉じる
	file.close();

	WAVEFORMATEX wfex{};
	// 波形フォーマットの設定
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	// 波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &wfex, 0, 2.0f, &voiceCallback);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}

	// 再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)pBuffer;
	buf.pContext = pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = data.size;
	pSourceVoice->SetVolume(Volume);
	// 波形データの再生
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}
	XAUDIO2_VOICE_STATE xaudio2state;
	pSourceVoice->GetState(&xaudio2state);
	result = pSourceVoice->Start(0);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}
}
void Audio::LoopWave(const char* filename, float Volume) {
	HRESULT result;
	// ファイルストリーム
	std::ifstream file;
	// Waveファイルを開く
	file.open(filename, std::ios_base::binary);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	// RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	// Dataチャンクの読み込み
	Chunk data;
	file.read((char*)&data, sizeof(data));

	// Dataチャンクのデータ部（波形データ）の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// Waveファイルを閉じる
	file.close();

	WAVEFORMATEX wfex{};
	// 波形フォーマットの設定
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	// 波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &wfex, 0, 2.0f, &voiceCallback);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}

	// 再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)pBuffer;
	buf.pContext = pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	buf.AudioBytes = data.size;
	pSourceVoice->SetVolume(Volume);
	// 波形データの再生
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}

	result = pSourceVoice->Start(0);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}
}


#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>
#include"Texture.h"
class DebugTxt
{

public:
	// デバッグテキスト用のテクスチャ番号を指定
	static const int maxCharCount = 256;	// 最大文字数
	static const int fontWidth = 9;			// フォント画像内1文字分の横幅
	static const int fontHeight = 18;		// フォント画像内1文字分の縦幅
	static const int fontLineCount = 14;	// フォント画像内1行分の文字数

	DebugTxt();
	~DebugTxt();

	void Initialize(UINT texnumber);

	void Print(const std::string& text, float x, float y, float size);

	void DrawAll();

private:
	// スプライトデータの配列
	Sprite* spriteDatas[maxCharCount] = {};
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
};


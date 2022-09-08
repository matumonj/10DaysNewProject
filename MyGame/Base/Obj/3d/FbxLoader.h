#pragma once

#include "fbxsdk.h"
#include "f_Model.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

#include <wrl.h>
using namespace Microsoft::WRL;
class FbxLoader
{
private:	//エイリアス
//std::を省略
	using string = std::string;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();
	/// <summary>
	///初期化
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	void Initialize();
	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();
	/// <summary>
	/// ファイルからFBXモデル読み込み
	/// </summary>
	/// <param name="modelName"></param>
	f_Model* LoadModelFromFile(const string modelName);

	/// <summary>
	/// 再帰的にノード構成を解析
	/// </summary>
	/// <param name="modle"></param>
	/// <param name="fbxNode">解析対象のノード</param>
	void ParseNodeRecursive(f_Model* model, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="model">読み込み先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	void ParseMesh(f_Model* model, FbxNode* fbxNode);

	/// <summary>
	/// FBXの行列をXMMatrixに変換
	/// </summary>
	/// <param name="dst">書き込み先</param>
	/// <param name="src">元となるFBX行列</param>
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);

	//頂点座標読み取り
	void ParseMeshVertices(f_Model* model, FbxMesh* fbxMesh);
	//面積情報読み取り
	void ParseMeshFaces(f_Model* model, FbxMesh* fbxMesh);
	//マテリアル読み取り
	void ParseMaterial(f_Model* model, FbxNode* fbxNode);
	//テクスチャ読み込み
	void LoadTexture(f_Model* model, const std::string& fullpath);
	//スキニング情報の読み取り
	void ParseSkin(f_Model* model, FbxMesh* fbxMesh);

	//ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);

private:
	XMMATRIX nodes;
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	//D3D12デバイス
	ComPtr<ID3D12Device> device = nullptr;
	//FBXマネージャ
	FbxManager* fbxManager = nullptr;
	//FBXインポータ
	FbxImporter* fbxImporter = nullptr;
	Node HandNode;
	FbxDouble3 hrotation;// = fbxNode->LclRotation.Get();
	FbxDouble3 hscaling;// = fbxNode->LclScaling.Get();
	FbxDouble3 htranslation;// = fbxNode->LclTranslation.Get();

public:	//定数
	XMMATRIX Hand;
	XMMATRIX GetHand() {
		return Hand;
	}
	XMFLOAT3 Getahand();
	XMMATRIX GetNode() { return nodes; }
	//モデル格納ルートパス
	static const string baseDirectory;
	//テクスチャがない場合の標準テクスチャファイル名
	static const string defaultTextureFileName;
};
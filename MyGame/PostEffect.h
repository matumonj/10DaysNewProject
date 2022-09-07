#pragma once
#include "Sprite.h"

class PostEffect :
    public Sprite
{
private:
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
    //テクスチャバッファ
    //ComPtr<ID3D12Resource>texBuff;
    //変更後
    ComPtr<ID3D12Resource>texBuff[2];
    //SRV用でスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descheapSRV;
    //深度バッファ    
    ComPtr<ID3D12Resource>depthBuff;
    //RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapRTV;
    //DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapDSV;
    //グラフィックスパイプライン
    ComPtr<ID3D12PipelineState>pipelineState;
    //ルートシグネチャ
    ComPtr<ID3D12RootSignature>rootSignature;
    //デバイス
    static ComPtr<ID3D12Device> device;
    static ComPtr<ID3D12GraphicsCommandList> cmdList;
private:
    //画面クリアカラー
    static const float clearColor[4];

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// パイプライン生成
    /// </summary>
    /// <param name="cmdList"></param>
    void CreateGraphicsPipeline();
    ///初期化
    void Initialize();

    /// <summary>
    /// 描画コマンド
    /// </summary>
    /// <param name="cmdList"></param>
    void Draw();

    /// <summary>
    /// シーン描画前処理
    /// </summary>
    /// <param name="cmdList"></param> 
    void PreDrawScene();

    /// <summary>
   /// シーン描画後処理
   /// </summary>
   /// <param name="cmdList"></param>
    void PostDrawScene();

};




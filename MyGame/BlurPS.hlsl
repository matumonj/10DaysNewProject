#include"Blur.hlsli"
Texture2D<float4> bokeTexture : register(t0);  // ボケ画像
Texture2D<float4> depthTexture : register(t1); // 深度テクスチャ

//Texture2D<float4> sceneTexture : register(t0); // シーンテクスチャ
sampler Sampler : register(s0);

float4 main(PSInput In) : SV_Target0
{
    // step-12 ボケ画像書き込み用のピクセルシェーダーを実装
     // カメラ空間での深度値をサンプリング
     float depth = depthTexture.Sample(Sampler, In.uv);

// カメラ空間での深度値が200以下ならピクセルキル
//      -> ボケ画像を描きこまない
clip(depth - 200.0f);

// ボケ画像をサンプリング
float4 boke = bokeTexture.Sample(Sampler, In.uv);

// 深度値から不透明度を計算する
// 深度値800からボケが始まり、深度値2000で最大のボケ具合になる
//  -> つまり、深度値2000で不透明度が1になる
boke.a = min(1.0f, (depth - 800.0f) / 2000.0f);

// ボケ画像を出力
return boke;
}
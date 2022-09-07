#include"PostEffectTest.hlsli"
//Texture2D<float4> bokeTexture : register(t1);  // ボケ画像
//Texture2D<float4> depthTexture : register(t0); // 深度テクスチャ
Texture2D<float4> tex : register(t0);  // ボケ画像
Texture2D<float4> tex1 : register(t1); // 深度テクスチャ

SamplerState smp:register(s0);
float4 main(Output input) : SV_TARGET
{
    // step-12 ボケ画像書き込み用のピクセルシェーダーを実装
   // カメラ空間での深度値をサンプリング
  // float depth = bokeTexture.Sample(Sampler, input.uv);

// カメラ空間での深度値が200以下ならピクセルキル
//      -> ボケ画像を描きこまない
//clip(depth+(0));

// ボケ画像をサンプリング
//float4 boke =depthTexture.Sample(Sampler, input.uv);
//boke.a =  min(1.0f, (depth + 1.0f) / 2.0f);

// 深度値から不透明度を計算する
// 深度値800からボケが始まり、深度値2000で最大のボケ具合になる
//  -> つまり、深度値2000で不透明度が1になる
float4 coltex0 = tex.Sample(smp, input.uv);
float4 coltex1 = tex1.Sample(smp, input.uv);

float4 col = coltex0;
float4 feed = { 0.5,0.5,0.5,1 };
	col = coltex1*feed;

return float4(col.rgb, 1);
// ボケ画像を出力
//return boke;
}
cbuffer cbuff0 : register(b0)
{
    float4 color;
    matrix viewproj; //ビュープロジェクション行列
    matrix world; //ワールド行列
    float3 cameraPos; //カメラ座標（ワールド座標）
};

//バーテックスバッファーの入力
struct VSInput
{
    float4 pos : POSITION; //位置
    float3 normal : NORMAL; //頂点法線
    float2 uv : TEXCOORD; //テクスチャー座標
    uint4 boneIndices : BONEINDICES;    //ボーンの番号
    float4 boneWeights : BONEWEIGHTS;   //ボーンのスキンウェイト
};

//頂点シェーダーからピクセルシェーダーへのやり方に使用する構造体
struct VSOutput
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float3 normal : NORMAL; //法線
    float2 uv : TEXCOORD; //uv値
    //float depth : TEXCOORD2; // カメラ空間でのZ値
};

//ボーンの最大数
static const int MAX_BONES = 88;

cbuffer skinning : register(b3) //ボーンのスキニング行列が入る
{
    matrix matSkinning[MAX_BONES];
}


struct PSOutPut
{
    float4 target0:SV_TARGET0;
    float4 target1:SV_TARGET1;
};

struct PSInPut
{
    float4 pos : POSITION; //位置
    float3 normal : NORMAL; //頂点法線
    float2 uv : TEXCOORD; //テクスチャー座標
    // step-7 カメラ空間でのZ値を記録する変数を追加
    float3 depthInView : TEXCOORD2; // カメラ空間でのZ値

};
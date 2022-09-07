#include "light.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 0番スロットに設定されたテクスチャ

SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutPut main(GSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	PSOutPut output;
	
	float3 light = normalize(float3(1, -1, 1));
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 1.0f;
	//float4 texcolor = float4(tex.Sample(smp, input.uv));
	//変更後
	//return tex.Sample(smp, input.uv) * color;
	float4 nc = { 0.1,0.1,0.1,1 };
float4 c = { 0.4,0.4,0.4,1 };
float dist = length(cameraPos - input.worldpos);
//float dist = length(float3(0, -20, 0) - input.worldpos);
	float4 addcol = float4(lerp(nc.rgb, c.rgb, dist/100),0.0);
	float3 fc = { 0.1,0.1,0.1 };
	
	//	float4 coltex0= tex.Sample(smp, input.uv);
	if (flag) {
		output.target0 = float4(texcolor.rgb*fc, texcolor.a) + addcol;
		output.target1 = float4(0, 0, 0, 1);
	}
	else {
		output.target0 = float4(texcolor.rgb * brightness, texcolor.a) ;
		output.target1 = float4(texcolor.rgb * brightness, texcolor.a);
	}
		// output.depth= input.depth;

		return output;
		// シェーディングによる色で描画
		//return shadecolor * texcolor;
}
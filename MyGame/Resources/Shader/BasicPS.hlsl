#include"Header.hlsli"
//#include"Header.hlsli"

//#include"header.hlsli"
Texture2D<float4>tex:register(t0);

SamplerState smp:register(s0);

//float4 main(output input) :sv_target
//{
//	return float4(input.uv,1,1);
//}
float4 main(Output input) : SV_TARGET
{
	float3 light = normalize(float3(1,-1,1));
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 1.0f;
	float4 texcolor = float4(tex.Sample(smp, input.uv));
	return float4(1,0,0,1);
	//return float4(input.normal,1);
//return float4(tex.sample(smp,input.uv))*color;
}


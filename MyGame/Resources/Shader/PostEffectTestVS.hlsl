#include"PostEffectTest.hlsli"
Output main(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	Output output;
	output.svpos = pos;
	output.uv = uv;
	return output;
}
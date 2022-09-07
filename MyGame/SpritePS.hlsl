#include"Sprite.hlsli"
Texture2D<float4>tex:register(t0);

SamplerState smp:register(s0);
float4 main(Output input) : SV_TARGET
{
	return tex.Sample(smp,input.uv) * color;
//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
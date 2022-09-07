cbuffer cbuff0:register(b0)
{
	float4 color;
	matrix mat;
};

struct Output
{
	float4 svpos:SV_POSITION;
	float2 uv:TEXCOORD;
};
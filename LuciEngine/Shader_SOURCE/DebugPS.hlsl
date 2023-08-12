#include "globals.hlsli"

struct VSIn
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

struct VSOut
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
	float4 color = Color;
	return color;
}
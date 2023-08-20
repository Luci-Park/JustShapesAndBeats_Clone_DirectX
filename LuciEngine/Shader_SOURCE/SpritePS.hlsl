#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4)0.0f;
    float2 uv = In.UV;
    if (Flip.x > 0.5) uv.x = 1 - uv.x;
    if (Flip.y > 0.5) uv.y = 1 - uv.y;
    color = albedoTexture.Sample(anisotropicSampler, uv);
    if (color.a <= 0.0f)
        discard;
    else
    {
        color.x *= Tint.x;
        color.y *= Tint.y;
        color.z *= Tint.z;
        color.w *= Tint.w;
        color = saturate(color);
        color = lerp(color, Color, Interpolation);
    }

    return color;
}
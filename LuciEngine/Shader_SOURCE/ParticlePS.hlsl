#include "globals.hlsli"

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};

//spritePS¿Í µ¿ÀÏ
float4 main(GSOut In) : SV_TARGET
{
    uint id = In.Instance;
    float4 color = (float4) 0.0f;
    float2 uv = In.UV;
    color = albedoTexture.Sample(anisotropicSampler, uv);
    if (color.a <= 0.0f)
        discard;
    else
    {
        float t = particles[id].time / particles[id].lifeTime;
        float4 tint = lerp(particleStartTint, particleEndTint, t);
        color.x *= tint.x;
        color.y *= tint.y;
        color.z *= tint.z;
        color.w *= tint.w;
        color = saturate(color);
    }

    return color;
}
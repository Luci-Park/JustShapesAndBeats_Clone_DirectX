//PS = Pixel Shader
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

Texture2D Tex : register(t0); //t = texture buffer
SamplerState pointSampler : register(s0); // s = samplers
SamplerState anisotropicSampler : register(s1); // s = samplers

float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float)0.0f;
    color = Tex.Sample(anisotropicSampler, In.UV);

    return color;
}
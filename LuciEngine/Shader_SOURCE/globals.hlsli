

cbuffer Transform : register(b0)
{
	row_major matrix WorldMatrix;
	row_major matrix ViewMatrix;
	row_major matrix ProjectionMatrix;
}

cbuffer Grid : register(b1)
{
	float4 CameraPosition;
	float2 CameraScale;
	float2 Resolution;
}

cbuffer MeshRenderer : register(b2)
{
	float4 Tint;
	float4 Color;
    float2 Flip;
	float Interpolation;
    uint mrpadd;
}

cbuffer ParticleSystem : register(b3)
{
    float4  particleStartTint;
    float4  particleEndTint;
    float4  particleStartRotation;
    float4  particleEndRotation;
    float   particleLifetime;
    float   particleElapsedTime;
    float   particleDeltaTime;
    
    float   particleStartSize;
    float   particleEndSize;
    float   particleStartSpeed;
    float   particleEndSpeed;
    
	uint elementCount;
}

cbuffer Noise : register(b4)
{
    float4 noiseTextureSize;
}

Texture2D albedoTexture : register(t0);
Texture2D noiseTexture : register(t15);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

struct Particle
{
	float4  position;
	float4  direction;
	float   lifeTime;
	float   time;
	float   speed;
	uint    active;
};

struct ParticleShared
{
    uint ActiveSharedCount;
};

StructuredBuffer<Particle> particles : register(t14);

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

float4 GaussianBlur(float2 UV)
{
    float4 Out = (float4) 0.0f;
    
    if (1.f < UV.x)
        UV.x = frac(UV.x);
    else if (UV.x < 0.0f)
        UV.x = 1.0f + frac(UV.x);
        
    if (1.f < UV.y)
        UV.y = frac(UV.y);
    else if (UV.y < 0.0f)
        UV.y = 1.0f + frac(UV.y);
    
    int2 iUV = UV * noiseTextureSize.xy;
    iUV -= int2(2, 2);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            Out += noiseTexture[idx] * GaussianFilter[i][j];
        }
    }
    
    return Out;
}
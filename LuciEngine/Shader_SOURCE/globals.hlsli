

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

cbuffer Material : register(b2)
{
	float4 Color;
}

Texture2D albedoTexture : register(t0);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);
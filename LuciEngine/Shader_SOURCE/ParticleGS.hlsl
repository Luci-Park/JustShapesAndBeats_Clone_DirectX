#include "globals.hlsli"

struct VSOut
{
    float4 LocalPos : SV_Position;
    uint Instance : SV_InstanceID;
};

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};

//Get a vertex, change to a square mesh
//and we are gpuinstancing
[maxvertexcount(6)]
void main(point VSOut In[1], inout TriangleStream<GSOut> output)
{
    uint id = In[0].Instance;
    if (particles[id].active == 0) //is particle active?
        return;
    
    GSOut Out[4] = { (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f };
  
    float3 Corners[4] =
    {
        float3(-0.5f, 0.5f, 0.f),
        float3(0.5f, 0.5f, 0.f),
        float3(0.5f, -0.5f, 0.f),
        float3(-0.5f, -0.5f, 0.f)
    };
    
    float t = particles[id].time / particles[id].lifeTime;
    float scale = lerp(particleStartSize, particleEndSize, t);
    
    float4x4 transformMatrix = CreateRotationMatrix(particles[id].rotation, float3(0, 0, 1));
    transformMatrix = mul(transformMatrix, CreateScaleMatrix(scale));
    transformMatrix = mul(transformMatrix, CreateTranslationMatrix(particles[id].position));
    if(particleInWorldSpace == 0)
        transformMatrix = mul(transformMatrix, WorldMatrix);
    for (int i = 0; i < 4; i++)
    {
        Out[i].Instance = In[0].Instance;
        float4 world = mul(float4(Corners[i], 1.0f), transformMatrix);
        float4 view = mul(world, ViewMatrix);
        float4 proj = mul(view, ProjectionMatrix);
        Out[i].Pos = proj;
    }
    
    //Set Texture Coordinates
        Out[0].UV = float2(0.0f, 0.0f);
    Out[1].UV = float2(1.0f, 0.0f);
    Out[2].UV = float2(1.0f, 1.0f);
    Out[3].UV = float2(0.0f, 1.0f);
 
    
    
    // 0 -- 1
    // | \  |
    // 3 -- 2
    output.Append(Out[0]);
    output.Append(Out[1]);
    output.Append(Out[2]);
    output.RestartStrip();

    output.Append(Out[0]);
    output.Append(Out[2]);
    output.Append(Out[3]);
    output.RestartStrip();
}
#include "globals.hlsli"


struct VSIn
{
    float3 LocalPos : POSITION;
    uint Instance : SV_InstanceID;
};

struct VSOut
{
    float4 LocalPos : SV_Position;
    uint Instance : SV_InstanceID;
};

//particle�� ������ ��
VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    Out.LocalPos = float4(In.LocalPos, 1.0f);
    Out.Instance = In.Instance;
    
    return Out;
}
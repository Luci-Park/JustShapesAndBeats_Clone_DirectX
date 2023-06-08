//VS = vertexshader
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

//cbuffer = constant buffer
//buffer slot 0�� �ִ� ���� transform�̶� �̸� ���ڴ�.
//�ش� buffer���� float4¥���� �ϳ� ���� �����̴�
cbuffer Transform : register(b0)
{
    float4 Pos;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;

    Out.Pos = float4(In.Pos, 1.0f);
    Out.Pos.x += Pos.x;
    
    Out.Color = In.Color;

    return Out;
}
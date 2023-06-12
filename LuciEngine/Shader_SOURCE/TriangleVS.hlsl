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
//buffer slot 0에 있는 놈을 transform이라 이름 짓겠다.
//해당 buffer에는 float4짜리가 하나 있을 예정이다
cbuffer Transform : register(b0)
{
    float4 Pos;
    float4 Color;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;

    Out.Pos = float4(In.Pos, 1.0f);
    Out.Pos.x *= Pos.w;
    Out.Pos.y *= Pos.w;

    Out.Pos.x += Pos.x;
    Out.Pos.y += Pos.y;
    
    Out.Color = Color;

    return Out;
}
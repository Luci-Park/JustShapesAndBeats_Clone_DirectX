//VS = vertexshader
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

//cbuffer = constant buffer
//buffer slot 0에 있는 놈을 transform이라 이름 짓겠다.
//해당 buffer에는 float4짜리가 하나 있을 예정이다
cbuffer Transform : register(b0)
{
    float4 Position;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;

    Out.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.x += 0.4f; //inputPosX; -> 상수버퍼를 통해서 이데이터가 넘와야한다.
    //Out.Pos.x += Position.x;
    //Out.Pos.y += Position.y;
    Out.UV = In.UV;
    Out.Color = In.Color;
    return Out;
}
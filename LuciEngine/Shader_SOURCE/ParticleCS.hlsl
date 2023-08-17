#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

[numthreads(128, 1, 1)]// run with 128 thread each dimension
void main(uint3 DTid : SV_DispatchThreadID)
{
    //thread termination check => �Ҵ���� ���� element�� �۵����� �ʴ´�.
	if (elementCount <= DTid.x)
		return;

    //is particle active
    if (ParticleBuffer[DTid.x].active == 0)
    {
        //thread�� particle�� �� ����
        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;
            
            // ������ ����ȭ Interlock ���� �Լ�            
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);
            
            if (origin == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        
        if (ParticleBuffer[DTid.x].active == 1)
        {
            // ���������� ��ġ�� ������ �����Ѵ�.
            // ���ø��� �õ��� UV �� ����Ѵ�.
            float4 vRandom = (float4) 0.f;

            float2 vUV = float2((float) DTid.x / elementCount, 0.5f);
            vUV.x += elapsedTime;
            vUV.y += sin((vUV.x + elapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;

            vRandom = float4
            (
                  GaussianBlur(vUV + float2(0.f, 0.f)).x
                , GaussianBlur(vUV + float2(0.1f, 0.f)).x
                , GaussianBlur(vUV + float2(0.2f, 0.f)).x
                , GaussianBlur(vUV + float2(0.3f, 0.f)).x
            );
            
            ParticleBuffer[DTid.x].position.xyz = vRandom.xyz * 3.0f;
            ParticleBuffer[DTid.x].position.x -= 0.65f;
            ParticleBuffer[DTid.x].position.y -= 1.4f;
            ParticleBuffer[DTid.x].position.z = 0.0f;
        }
    }
    else
    {
        //ParticleBuffer[DTid.x].position 
        //   += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
        
        // �ð��� üũ�ؼ� ���� �ð�(����)�� ������
        // active = 0;
    }
}
#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

void InitializeParticle(int id)
{
    ParticleBuffer[id].active = 1;
    ParticleBuffer[id].time = 0;
    ParticleBuffer[id].lifeTime = particleLifetime;
    ParticleBuffer[id].rotation = particleStartRotation;
    
    // 랜덤값으로 위치와 방향을 설정한다.
    // 샘플링을 시도할 UV 를 계산한다.=> 노이즈로부터의 sampling
    
    float4 vRandom = (float4) 0.f;

    float2 vUV = float2((float) id / elementCount, 0.5f);
    vUV.x += particleElapsedTime;
    vUV.y += sin((vUV.x + particleElapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;

    vRandom = float4
            (
                  GaussianBlur(vUV + float2(0.f, 0.f)).x
                , GaussianBlur(vUV + float2(0.1f, 0.f)).x
                , GaussianBlur(vUV + float2(0.2f, 0.f)).x
                , GaussianBlur(vUV + float2(0.3f, 0.f)).x
            );
            
    ParticleBuffer[id].position.xyz = vRandom.xyz * 3.0f;
    ParticleBuffer[id].position.x -= 0.65f;
    ParticleBuffer[id].position.y -= 1.4f;
    ParticleBuffer[id].position.z = 0.0f;
}
[numthreads(128, 1, 1)]// run with 128 thread each dimension
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint id = DTid.x;
    //thread termination check => 할당되지 않은 element는 작동하지 않는다.
    if (elementCount <= id)
		return;

    //if particle is not active
    if (ParticleBuffer[id].active == 0)
    {
        //if there are active particles to process
        while (ParticleSharedBuffer[0].ActiveSharedCount > 0)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;// <- process one particle at one time
            
            // 쓰레드 동기화 Interlock 관련 함수            
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);//activeSharedCount을 origin에서 exchange로 바꾸기 시도.
            
            if (origin == exchange) // activeSharedCount update을 성공했다면 particle initialize
            {
                InitializeParticle(id);
                break;
            }
        }
    }
    else
    {
        ParticleBuffer[id].time += particleDeltaTime;
        float t = ParticleBuffer[id].time / ParticleBuffer[id].lifeTime;
        if(t >= 1.0f)
            ParticleBuffer[id].active = 0;
        else
        {   
            float3 moveDirection = ParticleBuffer[id].direction * particleStartSpeed;
            moveDirection += float3(0, -particleGravityRate, 0);
            float3 moveRate = moveDirection * particleDeltaTime;
            
            ParticleBuffer[id].position += moveRate;
            ParticleBuffer[id].rotation += particleRotationSpeed * particleDeltaTime;
        }
        
    }
}


#include "LParticleShader.h"
#include "LStructedBuffer.h"
#include "LConstantBuffer.h"
#include "LParticleSystem.h"
#include "LRenderer.h"
#include "LTime.h"
namespace lu::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
	{
	}
	ParticleShader::~ParticleShader()
	{
	}
	void ParticleShader::Binds()
	{
		mParticleBuffer->BindUAV(0);
		mSharedBuffer->BindUAV(1);

		mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void ParticleShader::clear()
	{
		mParticleBuffer->clear();
		mSharedBuffer->clear();
	}
	void ParticleShader::SetParticles(StructedBuffer* particleBuffer, ParticleSystem* ps)
	{
		mParticleBuffer = particleBuffer;
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::ParticleSystem];

		renderer::ParticleSystemCB data = {};
		data.startTint = ps->mStartTint;
		data.endTint = ps->mEndTint;
		data.startRot = ps->mStartRotation;
		data.endRot = ps->mEndRotation;
		data.lifeTime = ps->mLifeTime;
		data.elapsedTime = ps->mElapsedTime;
		data.deltaTime = Time::DeltaTime();
		
		data.startSize = ps->mStartSize;
		data.endSize = ps->mEndSize;
		data.startSpeed = ps->mStartSpeed;
		data.endSpeed = ps->mEndSpeed;
		data.elementCount = ps->mMaxParticles;

		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
	}
}
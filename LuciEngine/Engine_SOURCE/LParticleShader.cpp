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
	void ParticleShader::SetParticles(StructedBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;
		
	}
}
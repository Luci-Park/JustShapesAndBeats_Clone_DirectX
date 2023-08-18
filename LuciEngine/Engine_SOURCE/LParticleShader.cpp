#include "LParticleShader.h"
#include "LStructedBuffer.h"
#include "LConstantBuffer.h"
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
	void ParticleShader::Clear()
	{
		mParticleBuffer->Clear();
		mSharedBuffer->Clear();
	}
	void ParticleShader::SetParticleBuffer(StructedBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::ParticleSystem];

		static float elapsedTime = 0.0f;
		elapsedTime += Time::DeltaTime();

		renderer::ParticleSystemCB data = {};
		data.elementCount = mParticleBuffer->GetStride();
		data.elapsedTime = elapsedTime;
		data.deltaTime = Time::DeltaTime();

		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
	}
}
#pragma once
#include "LComputeShader.h"
namespace lu
{
	class ParticleSystem;
}
namespace lu::graphics
{
	class StructedBuffer;
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void clear() override;

		void SetParticles(StructedBuffer* particleBuffer);
		void SetSharedBuffer(StructedBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }
	private:
		StructedBuffer* mParticleBuffer;
		StructedBuffer* mSharedBuffer;

	};
}


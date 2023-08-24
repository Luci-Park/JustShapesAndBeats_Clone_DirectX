#pragma once
#include "LComputeShader.h"
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

		void SetParticleBuffer(StructedBuffer* particleBuffer);
		void SetSharedBuffer(StructedBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }
	private:
		StructedBuffer* mParticleBuffer;
		StructedBuffer* mSharedBuffer;

	};
}


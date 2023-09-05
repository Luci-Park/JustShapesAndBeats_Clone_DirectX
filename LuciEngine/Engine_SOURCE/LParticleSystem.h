#pragma once
#include "LMeshRenderer.h"

namespace lu::graphics
{
	class StructedBuffer;
	class ParticleShader;
}
namespace lu
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		Vector4 mStartTint;
		Vector4 mEndTint;
		Quaternion mStartRotation;
		Quaternion mEndRotation;
		float mLifeTime;
		float mElapsedTime;
		float mStartSize;
		float mEndSize;
		float mStartSpeed;
		float mEndSpeed;
		bool mbLoop;
		bool mbAsBurst;
		UINT mMaxParticles;
	private:
		graphics::StructedBuffer* mParticleBuffer;
		graphics::StructedBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mParticleShader;
	};
}

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

		void SetLifeTime(float time) { mLifeTime = time; }
		void SetSize(float start, float end) { mStartSize = start; mEndSize = end; }
		void SetSpeed(float start, float end) { mStartSpeed = start; mEndSpeed = end; }
		void SetTint(Color start, Color end) { mStartTint = start, mEndTint = end; }
		void SetRotation(float start, float speed) { mStartRotation = start, mRotationSpeed = speed; }
	private:
		void BindConstantBuffer();
	public:
		Color mStartTint;
		Color mEndTint;
		float mStartRotation;
		float mRotationSpeed;
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

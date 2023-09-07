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
		//in degrees
		void SetAngle(float angle1, float angle2) { mAngle1 = angle1, mAngle2 = angle2; }
	private:
		void BindConstantBuffer();
	public:
		Color mStartTint;
		Color mEndTint;
		float mAngle1;
		float mAngle2;
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
		bool mbParticleInWorldSpace;
	private:
		graphics::StructedBuffer* mParticleBuffer;
		graphics::StructedBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mParticleShader;
	};
}

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
		enum class Space { local, world };
		struct Burst
		{
			double time;
			UINT count;
			bool complete = false;
		};
		ParticleSystem();
		~ParticleSystem();

		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetLifeTime(float time) { mLifeTime = time; }
		void SetSize(float start, float end) { mStartSize = start; mEndSize = end; }
		void SetStartSpeed(float speed) { mStartSpeed = speed;}
		void SetTint(Color start, Color end) { mStartTint = start, mEndTint = end; }
		void SetRotation(float start, float speed) { mStartRotation = start, mRotationSpeed = speed; }
		//in degrees
		void SetAngle(float angle1, float angle2) { mAngle1 = angle1, mAngle2 = angle2; }
		void SetGravity(float gravity) { mGravityModification = gravity; }
		void SetWorldSpace(Space space) { mbParticleInWorldSpace = (int)space; }

		void Play() { mIsPlaying = true; }
		void Stop() { mIsPlaying = false; }
	private:
		void BindConstantBuffer();
	public:
		double Duration;
		bool Loop;
		float RateOverTime;
		float RateOverDistance;
		std::vector<Burst> Bursts;
		UINT MaxParticles;
	private:
		graphics::StructedBuffer* mParticleBuffer;
		graphics::StructedBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mParticleShader;
		
		bool mIsPlaying;

		Color mStartTint;
		Color mEndTint;
		float mLifeTime;
		float mElapsedTime;

		float mAngle1;
		float mAngle2;
		float mStartRotation;
		float mRotationSpeed;
		
		float mStartSize;
		float mEndSize;
		float mStartSpeed;
		
		float mGravityModification;
		bool mbParticleInWorldSpace;
	};
}

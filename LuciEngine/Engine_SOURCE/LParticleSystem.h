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

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructedBuffer* mBuffer;
		graphics::StructedBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mParticles;
		std::shared_ptr<Texture> mTexture;

		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartSpeed;
		float mEndSpeed;
		float mLifeTime;
		double mTime;
		bool mbLoop;
		bool mbAsBurst;
		UINT mMaxParticles;
	};
}

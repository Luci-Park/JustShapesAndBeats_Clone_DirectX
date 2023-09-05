#include "LParticleSystem.h"
#include "LStructedBuffer.h"
#include "LParticleShader.h"
#include "LTime.h"
#include "LResources.h"
#include "LTransform.h"
#include "LGameObject.h"

namespace lu
{
	ParticleSystem::ParticleSystem()
		: mStartTint(Color::white)
		, mEndTint(Color::white)
		, mStartRotation(Quaternion::Identity)
		, mEndRotation(Quaternion::Identity)
		, mLifeTime(10)
		, mElapsedTime(1)
		, mStartSize(100)
		, mEndSize(100)
		, mStartSpeed(20)
		, mEndSpeed(20)
		, mbLoop(false)
		, mbAsBurst(false)
		, mMaxParticles(1000)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mParticleShader = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector3::Left * 40;
			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);

			particles[i].lifeTime = 0;
			particles[i].time = 0;
			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
		}

		mParticleBuffer = new graphics::StructedBuffer();
		mParticleBuffer->Create(sizeof(Particle), 1000, eResourceViewType::UAV, particles);

		mSharedBuffer = new graphics::StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eResourceViewType::UAV, nullptr, true);

	}
	ParticleSystem::~ParticleSystem()
	{
		delete mSharedBuffer;
		delete mParticleBuffer;
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = 0.5f;
		//mElapsedTime += Time::DeltaTime();

		if (mElapsedTime > AliveTime)
		{
			float f = (mElapsedTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mElapsedTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = mMaxParticles;
			mSharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			mSharedBuffer->SetData(&shareData, 1);
		}

	}
	void ParticleSystem::Render()
	{
		Owner()->mTransform->BindConstantBuffer();
		mParticleShader->SetParticles(mParticleBuffer, this);
		mParticleShader->SetSharedBuffer(mSharedBuffer);
		mParticleShader->OnExecute();

		mParticleBuffer->BindSRV(eShaderStage::VS, 14);
		mParticleBuffer->BindSRV(eShaderStage::GS, 14);
		mParticleBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mParticleBuffer->clear();
		GetMaterial()->clear();
	}
}
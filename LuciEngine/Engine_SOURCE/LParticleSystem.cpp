#include "LParticleSystem.h"
#include "LStructedBuffer.h"
#include "LParticleShader.h"
#include "LTime.h"
#include "LResources.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LConstantBuffer.h"
#include "LRenderer.h"
namespace lu
{
	ParticleSystem::ParticleSystem()
		: Duration(5)
		, Loop(true)
		, RateOverTime(10)
		, RateOverDistance(0)
		, Bursts(0)
		, MaxParticles(1000)
		, mbParticleInWorldSpace(true)
		, mLifeTime(10)
		, mGravityModification(0)
		, mStartTint(Color::white)
		, mEndTint(Color::white)
		, mAngle1(0)
		, mAngle2(0)
		, mStartRotation(0)
		, mRotationSpeed(0)
		, mElapsedTime(1)
		, mStartSize(100)
		, mEndSize(100)
		, mStartSpeed(20)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mParticleShader = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector3 pos = Vector3::Left * 40;
			particles[i].velocity = Vector3(0, 1, 0);
			particles[i].velocity.Normalize();
			particles[i].lifeTime = 0;
			particles[i].time = 0;
			particles[i].position = pos;
			particles[i].active = 0;
			particles[i].rotation = 0;
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
		if (!mIsPlaying) return;
		if (mElapsedTime > Duration)
		{
			if (!Loop)
			{
				mIsPlaying = false;
				return;
			}
			mElapsedTime = 0;
		}
		static double frequencyTimer = 0;
		double frequency = 1.0 / RateOverTime;

		mElapsedTime += Time::DeltaTime();
		frequencyTimer += Time::DeltaTime();
		if (frequencyTimer >= frequency)
		{
			frequencyTimer -= frequencyTimer;
			ParticleShared sharedData = {};
			sharedData.sharedActiveCount = 1000;
			mSharedBuffer->SetData(&sharedData, 1);
		}

	}
	void ParticleSystem::Render()
	{
		Owner()->mTransform->BindConstantBuffer();
		BindConstantBuffer();

		mParticleShader->SetParticles(mParticleBuffer);
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
	void ParticleSystem::BindConstantBuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::ParticleSystem];

		renderer::ParticleSystemCB data = {};
		data.lifeTime = mLifeTime;
		data.elapsedTime = mElapsedTime;
		data.deltaTime = Time::DeltaTime();

		data.particleAngle1 = XMConvertToRadians(mAngle1);
		data.particleAngle2 = XMConvertToRadians(mAngle2);

		data.startTint = mStartTint;
		data.endTint = mEndTint;
		data.startRot = XMConvertToRadians(mStartRotation);
		data.rotSpeed = XMConvertToRadians(mRotationSpeed);
		data.startSize = mStartSize;
		data.endSize = mEndSize;
		data.startSpeed = mStartSpeed;
		data.elementCount = MaxParticles;
		data.isParticleInWorldSpace = mbParticleInWorldSpace;
		data.gravityRate = mGravityModification;
		cb->SetData(&data);
		for (int i = 0; i < (int)eShaderStage::End; i++)
			cb->Bind((eShaderStage)i);
	}
}
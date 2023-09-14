#include "LParticleSystem.h"
#include "LStructedBuffer.h"
#include "LParticleShader.h"
#include "LTime.h"
#include "LResources.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LConstantBuffer.h"
#include "LRenderer.h"
#include "LFontWrapper.h"
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
		, mElapsedTime(0)
		, mStartSize(100)
		, mEndSize(100)
		, mStartSpeed(20)
		, mOffset(Vector3::Zero)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mParticleShader = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector3 pos = Vector3::Down * 20;
			particles[i].velocity = Vector3(RealRandom<float>( - 10, 10), RealRandom<float>(-10, 10), 0);
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
		static double frequencyTimer = 0;
		static Vector3 prevPos; 
		static bool posSet = false;
		static double lifeTimeTimer = mLifeTime;
		if (!posSet)
		{
			posSet = true;
			prevPos = Owner()->mTransform->GetPosition();
		}

		if (!mIsPlaying) return;

		lifeTimeTimer -= Time::DeltaTime();
		mElapsedTime += Time::DeltaTime();

		if (mElapsedTime > Duration)
		{
			mElapsedTime -= mElapsedTime;
			frequencyTimer -= frequencyTimer;
			lifeTimeTimer = mLifeTime;
			prevPos = Owner()->mTransform->GetPosition();
			for (int i = 0; i < Bursts.size(); i++)
			{
				Bursts[i].complete = false;
			}
			if (!Loop)
			{
				mIsPlaying = false;
				return;
			}
		}

		int numberOfParticles = 0;

		if (RateOverTime > 0)
		{
			double frequency = 1.0 / RateOverTime;

			frequencyTimer += Time::DeltaTime();
			if (frequencyTimer >= frequency)
			{
				frequencyTimer -= frequencyTimer;
				numberOfParticles++;
			}
		}
		if (RateOverDistance > 0)
		{
			Vector3 current = Owner()->mTransform->GetPosition();
			float delta = abs(Vector3::Distance(prevPos, current));
			numberOfParticles += delta * RateOverDistance;
			prevPos = current;
		}
		for (int i = 0; i < Bursts.size(); i++)
		{
			if (Bursts[i].complete) continue;
			if (mElapsedTime >= Bursts[i].time)
			{
				numberOfParticles += Bursts[i].count;
				//Bursts[i].complete = true;
			}
		}
		if (numberOfParticles > 0)
		{
			ParticleShared sharedData = {};
			sharedData.sharedActiveCount = numberOfParticles;
			mSharedBuffer->SetData(&sharedData, 1);
			lifeTimeTimer = mLifeTime;
		}
	}
	void ParticleSystem::Render()
	{
		FontWrapper::DrawFont(std::to_wstring(mElapsedTime), 10.f, 30.f, 20, FONT_RGBA(255, 0, 255, 255));
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
		data.offset = mOffset;
		cb->SetData(&data);
		for (int i = 0; i < (int)eShaderStage::End; i++)
			cb->Bind((eShaderStage)i);
	}
}
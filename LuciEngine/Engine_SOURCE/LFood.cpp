#include "LFood.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu
{
	Food::Food()
	{		
		mPos.x = (GetRandomInt(0, application.GetWidth()) - (application.GetWidth() * 0.5)) / (application.GetWidth() * 0.5);
		mPos.y = (GetRandomInt(0, application.GetHeight()) - (application.GetHeight() * 0.5)) / (application.GetHeight() * 0.5);
		mData.pos.x = mPos.x;
		mData.pos.y = mPos.y;
		mData.pos.z = 0;
		mData.pos.w = mRadius;
		mData.color = Vector4(GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, 1.0f);
	}
	Food::~Food()
	{
	}
	void Food::Initialize()
	{
	}
	void Food::Update()
	{
		if (DoesCollideWithPlayer())
		{
			player->AddMass();
			mState = Dead;
		}
	}
	void Food::LateUpdate()
	{
	}
	void Food::Render()
	{
		renderer::constantBuffer->SetData(&mData);
		renderer::constantBuffer->Bind(eShaderStage::VS);
		GameObject::Render();
	}
	bool Food::DoesCollideWithPlayer()
	{
		Vector2 playerPos = player->GetPos();
		float playerRadius = player->GetRadius();
		float distance = Vector2::DistanceSquared(mPos, playerPos);
		float thresholdSq = playerRadius * playerRadius;
		return distance < thresholdSq;
	}
}
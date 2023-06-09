#include "LFood.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu
{
	Food::Food()
	{
		mPos.x = (GetRandomInt(0, application.GetWidth()) - (application.GetWidth() * 0.5)) / (application.GetWidth() * 0.5);
		mPos.y = (GetRandomInt(0, application.GetHeight()) - (application.GetHeight() * 0.5)) / (application.GetHeight() * 0.5);
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
		Vector4 pos;
		pos.x = mPos.x;
		pos.y = mPos.y;
		pos.z = 0;
		pos.w = mRadius;
		renderer::constantBuffer->SetData(&pos);
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
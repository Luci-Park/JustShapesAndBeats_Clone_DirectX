#include "TryThisStage.h"
#include "LTransform.h"
#include "LAnimator.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LResources.h"
#include "LObject.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
namespace lu::JSAB
{
#pragma region Alarm
	void TryThisAlarm::Initialize()
	{
		Script::Initialize();

		auto mMr = Owner()->AddComponent<MeshRenderer>();
		auto mat = Resources::Load<Material>(L"AlarmMat", L"TT_Alarm_1");
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);
		mTransform->SetScale({ (float)mat->GetTexture()->GetRatioWidth(250.f), 250.f, 1 });
		
		auto mCol = Owner()->AddComponent<Collider2D>();
		mCol->SetSize({ 0.1, 0.6 });

		auto mAnim = Owner()->AddComponent<Animator>();
		auto ani = mAnim->CreateAnimation(L"Idle");
		float duration = 0.345 * 6 ;
		for (int i = 1; i <= 36; i++)
		{
			ani->AddTextureKey(duration * (i - 1) / 36, Resources::Find<Texture>(L"TT_Alarm_" + std::to_wstring(i)));
		}
		mAnim->PlayAnimation(L"Idle", true);
	}

#pragma endregion

#pragma region Concrete

	TryThisConcrete::TryThisConcrete()
	{
		mBaseTexture = Resources::Find<Texture>(L"TT_Concrete");
		mBaseMesh = Resources::Find<Mesh>(L"RectMesh");
		mBaseMat = Resources::Load<Material>(L"ConcreteMat", L"TT_Concrete");
		mBaseMat->SetRenderingMode(eRenderingMode::CutOut);
	}

	void TryThisConcrete::SetWithYScale(float Yscale, int num)
	{
		float x = mBaseTexture->GetRatioWidth(Yscale);
		float fullWidth = num * x;
		float startX = -fullWidth * 0.5;
		for (int i = 0; i < num; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			auto mMr = c->AddComponent<MeshRenderer>()->SetMesh(mBaseMesh)->SetMaterial(mBaseMat);
			auto mCol = c->AddComponent<Collider2D>();
			c->mTransform->SetScale({ x, Yscale, 1 });
			c->mTransform->SetLocalPosition(startX + x * 0.5 + x * i, 0, 0);
		}
	}
	void TryThisConcrete::SetWithXScale(float Xscale, int num)
	{
		float y = mBaseTexture->GetRatioHeight(Xscale);
		float fullWidth = num * Xscale;
		float startX = -fullWidth * 0.5;
		for (int i = 0; i < num; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			auto mMr = c->AddComponent<MeshRenderer>()->SetMesh(mBaseMesh)->SetMaterial(mBaseMat);
			auto mCol = c->AddComponent<Collider2D>();
			c->mTransform->SetScale({ Xscale, y, 1 });
			c->mTransform->SetLocalPosition(startX + Xscale * 0.5 + Xscale * i, 0, 0);
		}
	}
	void TryThisConcrete::SetWithFullXScale(float fullXscale, int num)
	{
		float x = fullXscale / num;
		float fullWidth = x * num;
		float y = mBaseTexture->GetRatioHeight(x);
		float startX = -fullWidth * 0.5;
		for (int i = 0; i < num; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			auto mMr = c->AddComponent<MeshRenderer>()->SetMesh(mBaseMesh)->SetMaterial(mBaseMat);
			auto mCol = c->AddComponent<Collider2D>();
			c->mTransform->SetScale({ x, y, 1 });
			c->mTransform->SetLocalPosition(startX + x * 0.5 + x * i, 0, 0);
		}
	}
#pragma endregion

#pragma region Main Stage
	void TryThisStage::Initialize()
	{
		auto b = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisAlarm>();
		b->Owner()->AddComponent<gui::TransformWidget>();
		b->mTransform->SetPosition(-378.12823, 238.92798, 1);

		b = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisAlarm>();
		b->Owner()->AddComponent<gui::TransformWidget>();
		b->mTransform->SetPosition(378.12823, 238.92798, 1);

		auto c = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisConcrete>();
		c->SetWithXScale(173, 11);
		c->mTransform->SetPosition(251.39134, 299.66867, 0);

		c = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisConcrete>();
		c->SetWithXScale(173, 8);
		c->mTransform->SetPosition(15.540734, -299.66867, 0);
	}
#pragma endregion
}
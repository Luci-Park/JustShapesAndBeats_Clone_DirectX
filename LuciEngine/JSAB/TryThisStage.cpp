#include "TryThisStage.h"
#include "LTransform.h"
#include "LAnimator.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LResources.h"
#include "LObject.h"
#include "LTime.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
namespace lu::JSAB
{
#pragma region Alarm
	void TryThisAlarm::Initialize()
	{
		Script::Initialize();
		Owner()->SetTag(eTagType::Bullet);
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		auto mat = Resources::Load<Material>(L"AlarmMat", L"TT_Alarm_1");
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);
		mTransform->SetScale({ (float)mat->GetTexture()->GetRatioWidth(250.f), 250.f, 1 });
		
		auto mCol = Owner()->AddComponent<Collider2D>();
		mCol->SetSize({ 0.1, 0.6 });

		auto mAnim = Owner()->AddComponent<Animator>();
		auto ani = mAnim->CreateAnimation(L"Idle");
		float duration = 0.345 * 5 ;
		for (int i = 1; i <= 36; i++)
		{
			ani->AddTextureKey(duration * (i - 1) / 36, Resources::Find<Texture>(L"TT_Alarm_" + std::to_wstring(i)));
		}
		mAnim->PlayAnimation(L"Idle", true);
		mbMove = false;

	}

	void TryThisAlarm::Update()
	{
		if (mbMove)
		{
			float dur = 1;
			float t = mTime / dur;
			if (t > 1)
			{
				mbMove = false;
			}
			else
			{
				Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, mTime / dur);
				mTime += Time::DeltaTime();
			}
		}
	}

	void TryThisAlarm::MoveY(float y)
	{
		mStartPos = mTransform->GetPosition();
		mEndPos = mStartPos;
		mEndPos.y = y;
		mbMove = true;
		mTime = 0;
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
			c->SetTag(eTagType::Bullet);
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
			c->SetTag(eTagType::Bullet);
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
			c->SetTag(eTagType::Bullet);
			auto mMr = c->AddComponent<MeshRenderer>()->SetMesh(mBaseMesh)->SetMaterial(mBaseMat);
			auto mCol = c->AddComponent<Collider2D>();
			c->mTransform->SetScale({ x, y, 1 });
			c->mTransform->SetLocalPosition(startX + x * 0.5 + x * i, 0, 0);
		}
	}

	void SmallConcrete::Initialize()
	{
		Script::Initialize();
		Owner()->SetTag(eTagType::Bullet);
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		auto mat = Resources::Load<Material>(L"TT_MidConcreteMat", L"TT_MidConcrete");
		mat->SetRenderingMode(eRenderingMode::CutOut);
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);
		mTex = mat->GetTexture();

		Owner()->AddComponent<Collider2D>();
	}
	void SmallConcrete::SetScale(float height)
	{
		Vector3 scale = Vector3::One;
		scale.y = height;
		scale.x = mTex->GetRatioWidth(height);
		mTransform->SetScale(scale);
	}
#pragma endregion

#pragma region Cog
	void TryThisCog::Initialize()
	{
		Script::Initialize();
		Owner()->SetTag(eTagType::Bullet);
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		auto mat = Resources::Load<Material>(L"CogMat", L"TT_CogwCenter");
		mat->SetRenderingMode(eRenderingMode::CutOut);
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);
		mTransform->SetScale(230, 230, 1);

		auto mCol = Owner()->AddComponent<Collider2D>(); 
		mCol->SetType(eColliderType::Circle);

	}
	void TryThisCog::Update()
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotateSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed); 
	}
	void TryThisCog::RotateClockwise()
	{
		mRotateSpeed = 0.4 * -1;
	}
	void TryThisCog::RotateCounterClockwise()
	{
		mRotateSpeed = 0.4 * 1;
	}


	void TryThisSmallCog::Initialize()
	{
		Script::Initialize();
		Owner()->SetTag(eTagType::Bullet);
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		auto mat = Resources::Load<Material>(L"SmallCogMat", L"TT_Cog");
		mat->SetRenderingMode(eRenderingMode::CutOut);
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);
		mTransform->SetScale(230, 230, 1);

		auto mCol = Owner()->AddComponent<Collider2D>();
		mCol->SetType(eColliderType::Circle);
	}
	void TryThisSmallCog::Update()
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotateSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
	}
	void TryThisSmallCog::RotateClockwise()
	{
		mRotateSpeed = 0.4 * -1;
	}
	void TryThisSmallCog::RotateCounterClockwise()
	{
		mRotateSpeed = 0.4 * 1;
	}
#pragma endregion

#pragma region Box
	void TryThisBox::Initialize()
	{
		Script::Initialize();
		Owner()->SetTag(eTagType::Bullet);
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		auto mat = Resources::Load<Material>(L"TTBoxMat", L"TT_Square");
		mat->SetRenderingMode(eRenderingMode::CutOut);
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);
		auto mCol = Owner()->AddComponent<Collider2D>();
	}
#pragma endregion

#pragma region Main Stage
	void TryThisStage::Initialize()
	{
		Script::Initialize();
		{
			auto b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisAlarm>();
			b->mTransform->SetPosition(-378.12823, 238.92798, 1);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisAlarm>();
			b->mTransform->SetPosition(378.12823, 238.92798, 1);
		}
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisConcrete>();
			c->SetWithXScale(173, 11);
			c->mTransform->SetPosition(251.39134, 299.66867, 0.1);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisConcrete>();
			c->SetWithXScale(173, 8);
			c->mTransform->SetPosition(15.540734, -299.66867, 0.1);
		}
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(843.27734, -255.55699, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(-0.96418345));
			c->SetScale(120);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(1229.2201, -255.55699, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(0.96418345));
			c->SetScale(120);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(1582.6373, -198.6486, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(1.2140691));
			c->SetScale(47);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(1707.9832, 162.35658, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(1.2140691));
			c->SetScale(47);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(2114.8176, 357.08084, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(0.38196132));
			c->SetScale(100);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(3419.9263, -199.32034, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(0.9037276));
			c->SetScale(90);

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<SmallConcrete>();
			c->mTransform->SetPosition(3847.6663, 286.44406, 0);
			c->mTransform->SetRotation(Quaternion::Create2DRotationRadian(-0.13085163));
			c->SetScale(130);
		}

		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(683.698, -391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(862.18964, -271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1040.68128, -391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1219.17292, -271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1397.66456, -391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1576.1562, -271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1754.64784, -391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1933.13948, -271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(2144.605, -226.85527, -0.1);
			c->RotateClockwise();
		}
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(683.698 +100, 391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(862.18964 + 100, 271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1040.68128 + 100, 391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1219.17292 + 100, 271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1397.66456 + 100, 391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1576.1562 + 100, 271.06842, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1754.64784 + 100, 391.1525, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(1896.6936, 179.13712, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCog>();
			c->mTransform->SetPosition(2116.4617, 220.25175, -0.1);
			c->RotateClockwise();
		}

		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(2600.2168, -156.3647, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(2431.9104, 159.90042, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(2732.457, 244.14793, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(2940.5437, 205.99867, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(2811.3777, -250.6197, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(2991.4177, -340.90198, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(3217.2358, -379.2216, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(3510.0347, 351.6227, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(3530.8364, -384.67654, -0.1);
			c->RotateCounterClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(3570.8772, -173.51685, -0.1);
			c->RotateClockwise();

			c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisSmallCog>();
			c->mTransform->SetPosition(3784.0598, -217.13567, -0.1);
			c->RotateCounterClockwise();
		}
		{
			auto b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(460, 230, 1);
			b->mTransform->SetPosition(2441.9324, -253.68369, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(460, 230, 1);
			b->mTransform->SetPosition(2441.9324, 253.68369, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 720, 1);
			b->mTransform->SetPosition(2691.589, 0, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 720, 1);
			b->mTransform->SetPosition(2944.4692, 0, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(250, 200, 1);
			b->mTransform->SetPosition(2809.3938, -328.86993, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(270.4656, 40, 1);
			b->mTransform->SetPosition(3099.162, 53.087395, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 332.4656, 1);
			b->mTransform->SetPosition(3111.978, 238.7123, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(270.4656, 40, 1);
			b->mTransform->SetPosition(3099.162, 53.087395, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 720, 1);
			b->mTransform->SetPosition(3254.183, -286.51807, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(271, 40, 1);
			b->mTransform->SetPosition(3409.6912, -25.571535, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 720, 1);
			b->mTransform->SetPosition(3564.805, 0, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(520, 40, 1);
			b->mTransform->SetPosition(3839.4453, 195.37105, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 720, 1);
			b->mTransform->SetPosition(4117.0557, 0, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(460, 230, 1);
			b->mTransform->SetPosition(4366.8765, -253.68369, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(460, 230, 1);
			b->mTransform->SetPosition(4366.8765, 253.68369, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(40, 720, 1);
			b->mTransform->SetPosition(4614.5376, 0, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(520, 40, 1);
			b->mTransform->SetPosition(3845.6409, -341.3028, -0.2);
		}
		{
			mWall = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			mWall->mTransform->SetScale(200, 1000, 1);
			mWall->mTransform->SetPosition(4534.5376, 0, -0.2);

			auto b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(200, 1000, 1);
			b->mTransform->SetPosition(5934.5376, 0, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(2000, 200, 1);
			b->mTransform->SetPosition(5244.5376, 400, -0.2);

			b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisBox>();
			b->mTransform->SetScale(2000, 200, 1);
			b->mTransform->SetPosition(5244.5376, -400, -0.2);

		}
		{
			mAlarm1 = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisAlarm>();
			mAlarm1->mTransform->SetPosition(-378.12823 + 5234.5376, 238.92798, 1);

			mAlarm2 = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisAlarm>();
			mAlarm2->mTransform->SetPosition(378.12823 + 5234.5376, 238.92798, 1);

			mCase = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisCrystal>();
			mCase->mTransform->SetPosition(5234.5376, -76.47402, 1);
		}
		DeActivate();
	}
	void TryThisStage::Reset()
	{
		mWall->Owner()->SetActive(false);
		mAlarm1->mTransform->SetPosition(-378.12823 + 5234.5376, 238.92798, 1);
		mAlarm2->mTransform->SetPosition(378.12823 + 5234.5376, 238.92798, 1);
		mCase->mTransform->SetPosition(5234.5376, -76.47402, 1);
	}
	void TryThisStage::RoomEnter()
	{
		mWall->Owner()->SetActive(true);
		mAlarm1->MoveY(238.92798);
		mAlarm2->MoveY(238.92798);
		mCase->Activate();
	}
	void TryThisStage::Activate()
	{
		Owner()->SetActive(true);
		Reset();
	}
	void TryThisStage::DeActivate()
	{
		Owner()->SetActive(false);
	}
#pragma endregion
}
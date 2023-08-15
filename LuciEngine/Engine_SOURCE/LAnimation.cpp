#include "LAnimation.h"
#include "LTime.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LCollider2D.h"
#include "LMeshRenderer.h"
namespace lu
{
	Animation::Animation(GameObject* owner)
		:Resource(enums::eResourceType::Animation)
	{
		mAni = owner->GetComponent <Animator>();
		mTr = owner->GetComponent<Transform>();
		mCd = owner->GetComponent<Collider2D>();
		mMr = owner->GetComponent<MeshRenderer>();
		mTimelines = std::vector<Timeline*>((UINT)eAnimationType::End, nullptr);
		SetAnimationFunctions();
	}
	Animation::~Animation()
	{
		for (int i = 0; i < (UINT)eAnimationType::End; i++)
		{
			if (mTimelines[i])
			{
				delete mTimelines[i];
				mTimelines[i] = nullptr;
			}
		}
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete) return;

		mTime += Time::DeltaTime();
		for (int i = 0; i < (UINT)eAnimationType::End; i++)
		{
			Timeline* timeline = mTimelines[i];
			if (timeline == nullptr) continue;
			if (timeline->IsComplete()) continue;

			//do something
			
		}
		if (mTime > mDuration)
		{
			mbComplete = true;
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
	}
	void Animation::AnimTrPos(Timeline* timeline)
	{
	}
	void Animation::SetAnimationFunctions()
	{
		animFunctions = std::vector<std::function<void(Timeline * timeline)>>((UINT)eAnimationType::End);
		animFunctions[(UINT)eAnimationType::TrPosition] = ([this](Timeline* timeline) { this->AnimTrPos(timeline); });
		animFunctions[(UINT)eAnimationType::TrScale] = ([this](Timeline* timeline) { this->AnimTrScale(timeline); });
		animFunctions[(UINT)eAnimationType::TrRotation] = ([this](Timeline* timeline) { this->AnimTrRot(timeline); });
		animFunctions[(UINT)eAnimationType::TrLocalPosition] = ([this](Timeline* timeline) { this->AnimTrLocPos(timeline); });
		animFunctions[(UINT)eAnimationType::TrLocalScale] = ([this](Timeline* timeline) { this->AnimTrLocScale(timeline); });
		animFunctions[(UINT)eAnimationType::TrLocalRotation] = ([this](Timeline* timeline) { this->AnimTrLocRot(timeline); });
		animFunctions[(UINT)eAnimationType::CdCenter] = ([this](Timeline* timeline) { this->AnimCdCenter(timeline); });
		animFunctions[(UINT)eAnimationType::CdSize] = ([this](Timeline* timeline) { this->AnimCdSize(timeline); });
		animFunctions[(UINT)eAnimationType::CdRotation] = ([this](Timeline* timeline) { this->AnimCdRotation(timeline); });
		animFunctions[(UINT)eAnimationType::CdActive] = ([this](Timeline* timeline) { this->AnimCdActive(timeline); });
		animFunctions[(UINT)eAnimationType::MrTexture] = ([this](Timeline* timeline) { this->AnimMrText(timeline); });
		animFunctions[(UINT)eAnimationType::MrColor] = ([this](Timeline* timeline) { this->AnimMrColor(timeline); });
		animFunctions[(UINT)eAnimationType::MrInterpolation] = ([this](Timeline* timeline) { this->AnimMrColorpolation(timeline); });
		animFunctions[(UINT)eAnimationType::MrTint] = ([this](Timeline* timeline) { this->AnimMrTint(timeline); });
		animFunctions[(UINT)eAnimationType::MrActive] = ([this](Timeline* timeline) { this->AnimTrActive(timeline); });
		animFunctions[(UINT)eAnimationType::ScFunc] = ([this](Timeline* timeline) { this->AnimScFunc(timeline); });
	}
}
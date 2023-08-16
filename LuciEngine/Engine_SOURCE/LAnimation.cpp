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
			mAnimFunctions[i](timeline);			
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
		for (int i = 0; i < (UINT)eAnimationType::End; i++)
		{
			if(mTimelines[i])
				mTimelines[i]->Reset();
		}
	}
	void Animation::AddKeyFrame(KeyFrame keyframe)
	{
		Timeline* timeline;
		if (mTimelines[(UINT)keyframe.type] == nullptr)
		{
			timeline = new Timeline();
			mTimelines[(UINT)keyframe.type] = std::move(timeline);
		}
		else timeline = mTimelines[(UINT)keyframe.type];
		if (keyframe.timestamp > mDuration) mDuration = keyframe.timestamp;
		timeline->keyframes.push_back(keyframe);
		std::sort(timeline->keyframes.begin(), timeline->keyframes.end());
	}
	void Animation::AnimTrPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetPosition(keyframe->vector3Value);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->vector3Value, next->vector3Value, t);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetScale(keyframe->vector3Value);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->vector3Value, next->vector3Value, t);
			mTr->SetScale(pos);
		}
	}
	void Animation::AnimTrRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetRotation(keyframe->quatValue);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->quatValue, next->quatValue, t);
			mTr->SetRotation(rot);
		}
	}
	void Animation::AnimTrLocPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalPosition(keyframe->vector3Value);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->vector3Value, next->vector3Value, t);
			mTr->SetLocalPosition(pos);
		}
	}
	void Animation::AnimTrLocScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalScale(keyframe->vector3Value);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->vector3Value, next->vector3Value, t);
			mTr->SetLocalScale(pos);
		}
	}
	void Animation::AnimTrLocRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalRotation(keyframe->quatValue);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->quatValue, next->quatValue, t);
			mTr->SetLocalRotation(rot);
		}
	}
	void Animation::AnimCdCenter(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mCd->SetCenter(keyframe->vector2Value);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->vector2Value, next->vector2Value, t);
			mCd->SetCenter(pos);
		}
	}
	void Animation::AnimCdSize(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mCd->SetSize(keyframe->vector2Value);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->vector2Value, next->vector2Value, t);
			mCd->SetSize(pos);
		}
	}
	void Animation::AnimCdActive(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			KeyFrame* keyframe = &timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mCd->SetActive(keyframe->boolValue);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrText(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			KeyFrame* keyframe = &timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mMr->GetMaterial()->SetTexture(keyframe->textureValue);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrColor(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			KeyFrame* keyframe = &timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetColor(keyframe->colorValue);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrColorpolation(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mMr->SetInterpolation(keyframe->floatValue);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->SetInterpolation(prev->floatValue + t*(next->floatValue - prev->floatValue));
		}
	}
	void Animation::AnimMrTint(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			KeyFrame* keyframe = &timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mMr->GetMaterial()->SetTint(keyframe->colorValue);
		}
		else
		{
			KeyFrame* prev = &timeline->keyframes[timeline->currIndex - 1];
			KeyFrame* next = &timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->GetMaterial()->SetTint(Color::Lerp(prev->colorValue, next->colorValue, t));
		}
	}
	void Animation::AnimMrActive(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			KeyFrame* keyframe = &timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetActive(keyframe->boolValue);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimScFunc(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			KeyFrame* keyframe = &timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				keyframe->func();
				timeline->currIndex++;
			}
		}
	}
	void Animation::SetAnimationFunctions()
	{
		mAnimFunctions = std::vector<std::function<void(Timeline * timeline)>>((UINT)eAnimationType::End);
		mAnimFunctions[(UINT)eAnimationType::TrPosition] = ([this](Timeline* timeline) { this->AnimTrPos(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrScale] = ([this](Timeline* timeline) { this->AnimTrScale(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrRotation] = ([this](Timeline* timeline) { this->AnimTrRot(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrLocalPosition] = ([this](Timeline* timeline) { this->AnimTrLocPos(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrLocalScale] = ([this](Timeline* timeline) { this->AnimTrLocScale(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrLocalRotation] = ([this](Timeline* timeline) { this->AnimTrLocRot(timeline); });
		mAnimFunctions[(UINT)eAnimationType::CdCenter] = ([this](Timeline* timeline) { this->AnimCdCenter(timeline); });
		mAnimFunctions[(UINT)eAnimationType::CdSize] = ([this](Timeline* timeline) { this->AnimCdSize(timeline); });
		mAnimFunctions[(UINT)eAnimationType::CdActive] = ([this](Timeline* timeline) { this->AnimCdActive(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrTexture] = ([this](Timeline* timeline) { this->AnimMrText(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrColor] = ([this](Timeline* timeline) { this->AnimMrColor(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrInterpolation] = ([this](Timeline* timeline) { this->AnimMrColorpolation(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrTint] = ([this](Timeline* timeline) { this->AnimMrTint(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrActive] = ([this](Timeline* timeline) { this->AnimMrActive(timeline); });
		mAnimFunctions[(UINT)eAnimationType::ScFunc] = ([this](Timeline* timeline) { this->AnimScFunc(timeline); });
	}
}
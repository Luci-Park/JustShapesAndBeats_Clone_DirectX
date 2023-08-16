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
			Vector3Key* keyframe = (Vector3Key*)&timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetPosition(keyframe->value);
		}
		else
		{
			Vector3Key* prev = (Vector3Key*) & timeline->keyframes[timeline->currIndex - 1];
			Vector3Key* next = (Vector3Key*) & timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = (Vector3Key*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetScale(keyframe->value);
		}
		else
		{
			Vector3Key* prev = (Vector3Key*) & timeline->keyframes[timeline->currIndex - 1];
			Vector3Key* next = (Vector3Key*) & timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetScale(pos);
		}
	}
	void Animation::AnimTrRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			QuaternionKey* keyframe = (QuaternionKey*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetRotation(keyframe->value);
		}
		else
		{
			QuaternionKey* prev = (QuaternionKey*)& timeline->keyframes[timeline->currIndex - 1];
			QuaternionKey* next = (QuaternionKey*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->value, next->value, t);
			mTr->SetRotation(rot);
		}
	}
	void Animation::AnimTrLocPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = (Vector3Key*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalPosition(keyframe->value);
		}
		else
		{
			Vector3Key* prev = (Vector3Key*)&timeline->keyframes[timeline->currIndex - 1];
			Vector3Key* next = (Vector3Key*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetLocalPosition(pos);
		}
	}
	void Animation::AnimTrLocScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = (Vector3Key*)&timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalScale(keyframe->value);
		}
		else
		{
			Vector3Key* prev = (Vector3Key*)&timeline->keyframes[timeline->currIndex - 1];
			Vector3Key* next = (Vector3Key*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetLocalScale(pos);
		}
	}
	void Animation::AnimTrLocRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			QuaternionKey* keyframe = (QuaternionKey*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalRotation(keyframe->value);
		}
		else
		{

			QuaternionKey* prev = (QuaternionKey*)&timeline->keyframes[timeline->currIndex - 1];
			QuaternionKey* next = (QuaternionKey*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->value, next->value, t);
			mTr->SetLocalRotation(rot);
		}
	}
	void Animation::AnimCdCenter(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector2Key* keyframe = (Vector2Key*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mCd->SetCenter(keyframe->value);
		}
		else
		{
			Vector2Key* prev = (Vector2Key*)& timeline->keyframes[timeline->currIndex - 1];
			Vector2Key* next = (Vector2Key*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->value, next->value, t);
			mCd->SetCenter(pos);
		}
	}
	void Animation::AnimCdSize(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector2Key* keyframe = (Vector2Key*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mCd->SetSize(keyframe->value);
		}
		else
		{
			Vector2Key* prev = (Vector2Key*)&timeline->keyframes[timeline->currIndex - 1];
			Vector2Key* next = (Vector2Key*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->value, next->value, t);
			mCd->SetSize(pos);
		}
	}
	void Animation::AnimCdActive(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			BoolKey* keyframe = (BoolKey*) & timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mCd->SetActive(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrText(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			KeyFrame* baseKeyFrame = &timeline->keyframes[timeline->currIndex];
			TextureKey* textureKey = dynamic_cast<TextureKey*>(baseKeyFrame);
			if (mTime >= textureKey->timestamp)
			{
				mMr->GetMaterial()->SetTexture(textureKey->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrColor(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			ColorKey* keyframe = (ColorKey*) & timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetColor(keyframe->value);
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
			FloatKey* keyframe = (FloatKey*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mMr->SetInterpolation(keyframe->value);
		}
		else
		{
			FloatKey* prev = (FloatKey*) & timeline->keyframes[timeline->currIndex - 1];
			FloatKey* next = (FloatKey*) & timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->SetInterpolation(prev->value + t*(next->value - prev->value));
		}
	}
	void Animation::AnimMrTint(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			ColorKey* keyframe = (ColorKey*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mMr->GetMaterial()->SetTint(keyframe->value);
		}
		else
		{
			ColorKey* prev = (ColorKey*)&timeline->keyframes[timeline->currIndex - 1];
			ColorKey* next = (ColorKey*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->GetMaterial()->SetTint(Color::Lerp(prev->value, next->value, t));
		}
	}
	void Animation::AnimMrActive(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			BoolKey* keyframe = (BoolKey*)&timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetActive(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimScFunc(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex].timestamp < mTime)
		{
			FuncKey* keyframe = (FuncKey*) & timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				keyframe->value();
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
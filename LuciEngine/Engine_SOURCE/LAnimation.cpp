
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
		mTr = owner->mTransform;
		mCd = owner->GetComponent<Collider2D>();
		mMr = owner->GetComponent<MeshRenderer>();
		mTimelines = std::vector<Timeline*>((UINT)eAnimationType::End);
		SetAnimationFunctions();
	}
	Animation::~Animation()
	{
		for (int i = 0; i < mTimelines.size(); i++)
			if (mTimelines[i])
			{
				delete mTimelines[i];
				mTimelines[i] = nullptr;
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

	void Animation::AddPositionXKey(double timestamp, float x)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrPosX);
		if (timestamp > mDuration)
			mDuration = timestamp;
		timeline->AddFloatKey(timestamp, x);
	}

	void Animation::AddPositionYKey(double timestamp, float y)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrPosY);
		if (timestamp > mDuration)
			mDuration = timestamp;
		timeline->AddFloatKey(timestamp, y);
	}

	void Animation::AddPositionZKey(double timestamp, float z)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrPosZ);
		if (timestamp > mDuration)
			mDuration = timestamp;
		timeline->AddFloatKey(timestamp, z);
	}

	void Animation::AddPositionKey(double timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrPosition);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddScaleKey(double timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrScale);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddRotationKey(double timestamp, Quaternion quaternion)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrRotation);
		if (timestamp > mDuration)
			mDuration = timestamp;
		QuaternionKey* key = new QuaternionKey();
		key->timestamp = timestamp;
		key->value = quaternion;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddLocalPositionKey(double timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrLocalPosition);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddLocalScaleKey(double timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrLocalScale);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddLocalRotationKey(double timestamp, Quaternion quaternion)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrLocalRotation);
		if (timestamp > mDuration)
			mDuration = timestamp;
		QuaternionKey* key = new QuaternionKey();
		key->timestamp = timestamp;
		key->value = quaternion;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColliderCenterKey(double timestamp, Vector2 vector2)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::CdCenter);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector2Key* key = new Vector2Key();
		key->timestamp = timestamp;
		key->value = vector2;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColliderSizeKey(double timestamp, Vector2 vector2)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::CdSize);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector2Key* key = new Vector2Key();
		key->timestamp = timestamp;
		key->value = vector2;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColliderActiveKey(double timestamp, bool active)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::CdActive);
		if (timestamp > mDuration)
			mDuration = timestamp;
		BoolKey* key = new BoolKey();
		key->timestamp = timestamp;
		key->value = active;
		timeline->keyframes.push_back(key);
	}
	
	void Animation::AddTextureKey(double timestamp, std::shared_ptr<graphics::Texture> texture)
	{		
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrTexture);
		if (timestamp > mDuration)
			mDuration = timestamp;
		TextureKey* key = new TextureKey();
		key->timestamp = timestamp;
		key->value = texture;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddAlphaKey(double timestamp, float alpha)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrAlpha);
		if (timestamp > mDuration)
			mDuration = timestamp;
		timeline->AddFloatKey(timestamp, alpha);
	}
	void Animation::AddColorKey(double timestamp, Color color)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrColor);
		if (timestamp > mDuration)
			mDuration = timestamp;
		ColorKey* key = new ColorKey();
		key->timestamp = timestamp;
		key->value = color;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddInterpolationKey(double timestamp, float interpolation)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrInterpolation);
		if (timestamp > mDuration)
			mDuration = timestamp;
		FloatKey* key = new FloatKey();
		key->timestamp = timestamp;
		key->value = interpolation;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddTintKey(double timestamp, Color color)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrTint);
		if (timestamp > mDuration)
			mDuration = timestamp;
		ColorKey* key = new ColorKey();
		key->timestamp = timestamp;
		key->value = color;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddRendererActiveKey(double timestamp, bool active)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrActive);
		if (timestamp > mDuration)
			mDuration = timestamp;
		BoolKey* key = new BoolKey();
		key->timestamp = timestamp;
		key->value = active;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddFunctionKey(double timestamp, std::function<void()> function)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::ScFunc);
		if (timestamp > mDuration)
			mDuration = timestamp;
		FuncKey* key = new FuncKey();
		key->timestamp = timestamp;
		key->value = function;
		timeline->keyframes.push_back(key);

	}

	Timeline* Animation::GetTimlineOfType(eAnimationType type)
	{
		if (mTimelines[(UINT)type] == nullptr)
			mTimelines[(UINT)type] = new Timeline();

		return mTimelines[(UINT)type];
	}
	void Animation::AnimTrPosX(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		Vector3 pos = mTr->GetPosition();
		if (timeline->currIndex == 0)
		{
			FloatKey* keyframe = dynamic_cast<FloatKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
			{
				pos.x = keyframe->value;
				mTr->SetPosition(pos);
			}
		}
		else
		{
			FloatKey* prev = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex - 1]);
			FloatKey* next = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			pos.x = prev->value + t * (next->value - prev->value);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrPosY(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		Vector3 pos = mTr->GetPosition();
		if (timeline->currIndex == 0)
		{
			FloatKey* keyframe = dynamic_cast<FloatKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
			{
				pos.y = keyframe->value;
				mTr->SetPosition(pos);
			}
		}
		else
		{
			FloatKey* prev = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex - 1]);
			FloatKey* next = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			pos.y = prev->value + t * (next->value - prev->value);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrPosZ(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		Vector3 pos = mTr->GetPosition();
		if (timeline->currIndex == 0)
		{
			FloatKey* keyframe = dynamic_cast<FloatKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
			{
				pos.z = keyframe->value;
				mTr->SetPosition(pos);
			}
		}
		else
		{
			FloatKey* prev = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex - 1]);
			FloatKey* next = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			pos.z = prev->value + t * (next->value - prev->value);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mTr->SetPosition(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mTr->SetScale(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetScale(pos);
		}
	}
	void Animation::AnimTrRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			QuaternionKey* keyframe = dynamic_cast<QuaternionKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mTr->SetRotation(keyframe->value);
		}
		else
		{
			QuaternionKey* prev = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex - 1]);
			QuaternionKey* next = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->value, next->value, t);
			mTr->SetRotation(rot);
		}
	}
	void Animation::AnimTrLocPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mTr->SetLocalPosition(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetLocalPosition(pos);
		}
	}
	void Animation::AnimTrLocScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mTr->SetLocalScale(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetLocalScale(pos);
		}
	}
	void Animation::AnimTrLocRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			QuaternionKey* keyframe = dynamic_cast<QuaternionKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mTr->SetLocalRotation(keyframe->value);
		}
		else
		{

			QuaternionKey* prev = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex - 1]);
			QuaternionKey* next = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->value, next->value, t);
			mTr->SetLocalRotation(rot);
		}
	}
	void Animation::AnimCdCenter(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector2Key* keyframe = dynamic_cast<Vector2Key*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mCd->SetCenter(keyframe->value);
		}
		else
		{
			Vector2Key* prev = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector2Key* next = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->value, next->value, t);
			mCd->SetCenter(pos);
		}
	}
	void Animation::AnimCdSize(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector2Key* keyframe = dynamic_cast<Vector2Key*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mCd->SetSize(keyframe->value);
		}
		else
		{
			Vector2Key* prev = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector2Key* next = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->value, next->value, t);
			mCd->SetSize(pos);
		}
	}
	void Animation::AnimCdActive(Timeline* timeline)
	{
		while (!timeline->IsComplete() && timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			BoolKey* keyframe = dynamic_cast<BoolKey*>(timeline->keyframes[timeline->currIndex]);
			if (mTime >= keyframe->timestamp)
			{
				mCd->SetActive(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrText(Timeline* timeline)
	{
		while (!timeline->IsComplete() && timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			TextureKey* textureKey = dynamic_cast<TextureKey*>(timeline->keyframes[timeline->currIndex]);
			if (mTime >= textureKey->timestamp)
			{
				mMr->GetMaterial()->SetTexture(textureKey->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrColorAlpha(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		Color c = mMr->GetColor();
		if (timeline->currIndex == 0)
		{
			FloatKey* keyframe = dynamic_cast<FloatKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
			{
				c = Color(c.R(),c.G(), c.B(), keyframe->value);
				mMr->SetColor(c);
			}
		}
		else
		{
			FloatKey* prev = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex - 1]);
			FloatKey* next = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			c = Color(c.R(), c.G(), c.B(), prev->value + t * (next->value - prev->value));
			mMr->SetColor(c);
		}
	}
	void Animation::AnimMrColor(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			ColorKey* keyframe = dynamic_cast<ColorKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mMr->SetColor(keyframe->value);
		}
		else
		{
			ColorKey* prev = dynamic_cast<ColorKey*>(timeline->keyframes[timeline->currIndex - 1]);
			ColorKey* next = dynamic_cast<ColorKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->SetColor(Color::Lerp(prev->value, next->value, t));
		}
	}
	void Animation::AnimMrColorpolation(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			FloatKey* keyframe = dynamic_cast<FloatKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mMr->SetInterpolation(keyframe->value);
		}
		else
		{
			FloatKey* prev = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex - 1]);
			FloatKey* next = dynamic_cast<FloatKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->SetInterpolation(prev->value + t*(next->value - prev->value));
		}
	}
	void Animation::AnimMrTint(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			ColorKey* keyframe = dynamic_cast<ColorKey*>(timeline->keyframes[0]);
			if (mTime >= keyframe->timestamp)
				mMr->GetMaterial()->SetTint(keyframe->value);
		}
		else
		{
			ColorKey* prev = dynamic_cast<ColorKey*>(timeline->keyframes[timeline->currIndex - 1]);
			ColorKey* next = dynamic_cast<ColorKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->GetMaterial()->SetTint(Color::Lerp(prev->value, next->value, t));
		}
	}
	void Animation::AnimMrActive(Timeline* timeline)
	{
		while (!timeline->IsComplete() && timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			BoolKey* keyframe = dynamic_cast<BoolKey*>(timeline->keyframes[timeline->currIndex]);
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetActive(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimScFunc(Timeline* timeline)
	{
		while (!timeline->IsComplete() && timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			FuncKey* keyframe = dynamic_cast<FuncKey*>(timeline->keyframes[timeline->currIndex]);
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
		mAnimFunctions[(UINT)eAnimationType::TrPosX] = ([this](Timeline* timeline) { this->AnimTrPosX(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrPosY] = ([this](Timeline* timeline) { this->AnimTrPosY(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrPosZ] = ([this](Timeline* timeline) { this->AnimTrPosZ(timeline); });

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
		mAnimFunctions[(UINT)eAnimationType::MrAlpha] = ([this](Timeline* timeline) { this->AnimMrColorAlpha(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrColor] = ([this](Timeline* timeline) { this->AnimMrColor(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrInterpolation] = ([this](Timeline* timeline) { this->AnimMrColorpolation(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrTint] = ([this](Timeline* timeline) { this->AnimMrTint(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrActive] = ([this](Timeline* timeline) { this->AnimMrActive(timeline); });
		mAnimFunctions[(UINT)eAnimationType::ScFunc] = ([this](Timeline* timeline) { this->AnimScFunc(timeline); });
	}
}
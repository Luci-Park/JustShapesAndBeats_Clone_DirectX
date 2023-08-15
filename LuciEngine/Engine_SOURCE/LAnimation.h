#pragma once
#include "LResource.h"
#include "LTexture.h"
namespace lu
{
	class GameObject;
	class Transform;
	class Collider2D;
	class Animator;
	class MeshRenderer;
	class Animation : public Resource
	{
	public:
		enum class eAnimationType;
		struct KeyFrame;
		struct Timeline;
	public:
		Animation(GameObject* owner);
		~Animation();
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();
		
		void Reset();
		bool IsComplete() { return mbComplete; }

		void AddKeyFrame(eAnimationType type, KeyFrame keyFrame);
	private:
		void AnimTrPos(Timeline* timeline);
		void AnimTrScale(Timeline* timeline);
		void AnimTrRot(Timeline* timeline);
		void AnimTrLocPos(Timeline* timeline);
		void AnimTrLocScale(Timeline* timeline);
		void AnimTrLocRot(Timeline* timeline);
		void AnimCdCenter(Timeline* timeline);
		void AnimCdSize(Timeline* timeline);
		void AnimCdActive(Timeline* timeline);
		void AnimMrText(Timeline* timeline);
		void AnimMrColor(Timeline* timeline);
		void AnimMrColorpolation(Timeline* timeline);
		void AnimMrTint(Timeline* timeline);
		void AnimMrActive(Timeline* timeline);
		void AnimScFunc(Timeline* timeline);
		void SetAnimationFunctions();
	private:
		float mTime;
		float mDuration;
		bool mbComplete;
		std::vector<Timeline*> mTimelines;
		std::vector<std::function<void(Timeline* timeline)>> mAnimFunctions;
		Animator* mAni;
		Transform* mTr;
		Collider2D* mCd;
		MeshRenderer* mMr;


		enum class eAnimationType
		{
			TrPosition, TrScale, TrRotation, TrLocalPosition, TrLocalScale, TrLocalRotation,
			CdCenter, CdSize, CdActive,
			MrTexture, MrColor, MrInterpolation, MrTint, MrActive,
			ScFunc,
			End
		};
		struct KeyFrame
		{
			KeyFrame(){}
			~KeyFrame(){}
			KeyFrame(const KeyFrame& other)
				: timestamp(other.timestamp), func(other.func) {}
			float timestamp;
			union
			{
				std::function<void()>func;
				std::shared_ptr<graphics::Texture> textureValue;
				math::Color colorValue;
				math::Vector3 vector3Value;
				math::Vector2 vector2Value;
				math::Quaternion quatValue;
				float floatValue;
				bool boolValue;
			};
			bool operator<(const KeyFrame& other) const
			{
				return timestamp < other.timestamp;
			}
			KeyFrame& operator=(const KeyFrame& other) {
				if (this != &other) {
					timestamp = other.timestamp;
				}
				return *this;
			}
		};

		struct Timeline
		{
			int currIndex = 0;
			std::vector<KeyFrame> keyframes;
			bool IsComplete() { return currIndex >= keyframes.size(); }
		};
	};

}


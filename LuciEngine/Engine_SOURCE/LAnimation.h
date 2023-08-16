#pragma once
#include "LResource.h"
#include "LTexture.h"
namespace lu
{
	using namespace lu::math;
	class GameObject;
	class Transform;
	class Collider2D;
	class Animator;
	class MeshRenderer;
	class Animation : public Resource
	{
	public:

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
		public:
			KeyFrame(){}
			~KeyFrame() {}
			KeyFrame(const KeyFrame& other)
				: timestamp(other.timestamp), type(other.type){
				CopyKeyFrame(other);
			}
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
					type = other.type;
					CopyKeyFrame(other);
				}
				return *this;
			}
			void CopyKeyFrame(const KeyFrame& other)
			{
				switch (type)
				{
				case eAnimationType::TrPosition:
				case eAnimationType::TrScale:
				case eAnimationType::TrLocalPosition:
				case eAnimationType::TrLocalScale:
					vector3Value = other.vector3Value;
					break;
				case eAnimationType::TrRotation:
				case eAnimationType::TrLocalRotation:
					quatValue = other.quatValue;
					break;
				case eAnimationType::CdCenter:
				case eAnimationType::CdSize:
					vector2Value = other.vector2Value;
					break;
				case eAnimationType::CdActive:
				case eAnimationType::MrActive:
					boolValue = other.boolValue;
					break;
				case eAnimationType::MrTexture:
					textureValue = other.textureValue;
					break;
				case eAnimationType::MrColor:
				case eAnimationType::MrTint:
					colorValue = other.colorValue;
					break;
				case eAnimationType::MrInterpolation:
					floatValue = other.floatValue;
					break;
				case eAnimationType::ScFunc:
					func = other.func;
					break;
				default:
					assert(false);
				}

			}

			void SetType(eAnimationType type)
			{
				this->type = type;
				switch (type)
				{
				case eAnimationType::TrPosition:
				case eAnimationType::TrLocalPosition:
					vector3Value = Vector3::Zero;
					break;
				case eAnimationType::TrScale:
				case eAnimationType::TrLocalScale:
					vector3Value = Vector3::One;
					break;
				case eAnimationType::TrRotation:
				case eAnimationType::TrLocalRotation:
					quatValue = Quaternion::Identity;
					break;
				case eAnimationType::CdCenter:
					vector2Value = Vector2::Zero;
					break;
				case eAnimationType::CdSize:
					vector2Value = Vector2::One;
					break;
				case eAnimationType::CdActive:
				case eAnimationType::MrActive:
					boolValue = true;
					break;
				case eAnimationType::MrTexture:
					textureValue = nullptr;
					break;
				case eAnimationType::MrColor:
				case eAnimationType::MrTint:
					colorValue = Color::white;
					break;
				case eAnimationType::MrInterpolation:
					floatValue = 0.0f;
					break;
				case eAnimationType::ScFunc:
					func = nullptr;
					break;
				default:
					assert(false);
				}

			}
			eAnimationType GetType() { return type; }
			private:
				eAnimationType type;

		};

		struct Timeline
		{
			int currIndex = 0;
			std::vector<KeyFrame> keyframes;
			bool IsComplete() { return currIndex >= keyframes.size(); }
			void Reset() { currIndex = 0; }
		};
	public:
		Animation(GameObject* owner);
		~Animation();
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();
		
		void Reset();
		bool IsComplete() { return mbComplete; }

		void AddKeyFrame(KeyFrame keyframe);
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


	};

}


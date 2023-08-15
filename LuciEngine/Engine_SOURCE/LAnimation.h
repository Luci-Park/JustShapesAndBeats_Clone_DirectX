#pragma once
#include "LResource.h"
#include "LTexture.h"
namespace lu
{
	class Animator;
	class Animation : public Resource
	{
	public:
		struct KeyFrame
		{
			float mTime;
			union
			{
				std::function<void()>func;
				graphics::Texture textValue;
				math::Color colorValue;
				math::Vector3 vector3Value;
				math::Vector2 vector2Value;
				math::Quaternion quatValue;
				float floatValue;
				bool boolValue;
			};
		};
		enum eAnimationType
		{
			TrPosition, TrScale, TrRotation, TrLocalPosition, TrLocalScale, TrLocalRotation,
			CdCenter, CdSize, CdRotation, CdActive,
			MrTexture, MrColor, MrInterpolation, MrTint, MrActive,
			ScFunc
		};

	public:
		Animation();
		~Animation();
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }
		void AddKeyFrame(eAnimationType type, KeyFrame keyFrame);

		void Update();
		void LateUpdate();
		void Render();
		
		void Reset();
		bool IsComplete() { return mbComplete; }

	private:

		Animator* mAnimator;
		float mTime;
		float mDuration;
		bool mbComplete;
	};
}


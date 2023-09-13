#pragma once
#include "LResource.h"
#include "LTimeLines.h"
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
			TrPosX, TrPosY, TrPosZ, TrPosition, 
			TrScale, TrRotation, TrLocalPosition, TrLocalScale, TrLocalRotation,
			CdCenter, CdSize, CdActive,
			MrTexture, MrAlpha, MrColor, MrInterpolation, MrTint, MrActive,
			ScFunc,
			End
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
		void SetTime(double time) { mTime = time; }
		double GetTime() { return mTime; }

		void AddPositionXKey(double timestamp, float x);
		void AddPositionYKey(double timestamp, float y);
		void AddPositionZKey(double timestamp, float z);
		void AddPositionKey(double timestamp, Vector3 vector3);

		void AddScaleKey(double timestamp, Vector3 vector3);
		void AddRotationKey(double timestamp, Quaternion quaternion);
		void AddLocalPositionKey(double timestamp, Vector3 vector3);
		void AddLocalScaleKey(double timestamp, Vector3 vector3);
		void AddLocalRotationKey(double timestamp, Quaternion quaternion);
		void AddColliderCenterKey(double timestamp, Vector2 vector2);
		void AddColliderSizeKey(double timestamp, Vector2 vector2);
		void AddColliderActiveKey(double timestamp, bool active);
		void AddTextureKey(double timestamp, std::shared_ptr<graphics::Texture> texture);

		void AddAlphaKey(double timestamp, float alpha);
		void AddColorKey(double timestamp, Color color);
		void AddInterpolationKey(double timestamp, float interpolation);
		void AddTintKey(double timestamp, Color color);
		void AddRendererActiveKey(double timestamp, bool active);
		void AddFunctionKey(double timestamp, std::function<void()> function);
	private:
		Timeline* GetTimlineOfType(eAnimationType type);
		void AnimTrPosX(Timeline* timeline);
		void AnimTrPosY(Timeline* timeline);
		void AnimTrPosZ(Timeline* timeline);
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
		
		void AnimMrColorAlpha(Timeline* timeline);
		void AnimMrColor(Timeline* timeline);

		void AnimMrColorpolation(Timeline* timeline);
		void AnimMrTint(Timeline* timeline);
		void AnimMrActive(Timeline* timeline);
		void AnimScFunc(Timeline* timeline);
		void SetAnimationFunctions();
	private:
		std::vector<Timeline*>mTimelines;
		std::vector < std::function<void(Timeline*)>> mAnimFunctions;

		Transform* mTr;
		Collider2D* mCd;
		MeshRenderer* mMr;
		double mTime;
		float mDuration;
		bool mbComplete;
	};
}


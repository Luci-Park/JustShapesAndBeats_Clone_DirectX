#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
#include "..\\Engine_SOURCE\\LTexture.h"
#include "..\\Engine_SOURCE\\LMesh.h"

namespace lu::JSAB
{
	class TryThisAlarm : public Script
	{
	public:
		TryThisAlarm(){}
		virtual ~TryThisAlarm(){}

		virtual void Initialize();
		virtual void Update();
		void MoveY(float y);

	private:
		Vector3 mStartPos, mEndPos;
		double mTime;
		bool mbMove;
	};

	class TryThisConcrete : public Script
	{
	public:
		TryThisConcrete();
		virtual ~TryThisConcrete() {}

		void SetWithYScale(float Yscale, int num);
		void SetWithXScale(float Xscale, int num);
		void SetWithFullXScale(float fullXscale, int num);
	private:
		std::shared_ptr<graphics::Texture> mBaseTexture;
		std::shared_ptr<Mesh> mBaseMesh;
		std::shared_ptr<Material> mBaseMat;
	};

	class SmallConcrete : public Script
	{
	public:
		SmallConcrete() {}
		virtual ~SmallConcrete() {}
		virtual void Initialize() override;
		void SetScale(float width);
	private:
		std::shared_ptr<Texture> mTex;
	};

	class TryThisCog : public Script
	{
	public:
		TryThisCog() {}
		virtual ~TryThisCog() {}

		virtual void Initialize();
		virtual void Update();
		void RotateClockwise();
		void RotateCounterClockwise();
	private:
		float mRotateSpeed;
	};

	class TryThisSmallCog : public Script
	{
	public:
		TryThisSmallCog() {}
		virtual ~TryThisSmallCog() {}

		virtual void Initialize();
		virtual void Update();
		void RotateClockwise();
		void RotateCounterClockwise();
	private:
		float mRotateSpeed;
	};

	class TryThisBox : public Script
	{
	public:
		TryThisBox() {}
		virtual ~TryThisBox(){}

		virtual void Initialize();
	};

	class TryThisStage : public Script
	{
	public:
		TryThisStage(){}
		virtual ~TryThisStage(){}

		virtual void Initialize();
		void Activate();
		void DeActivate();
	};
}


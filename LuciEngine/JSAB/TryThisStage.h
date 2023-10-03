#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
#include <LTexture.h>
#include <LMesh.h>

namespace lu::JSAB
{
	class TryThisAlarm : public Script
	{
	public:
		TryThisAlarm(){}
		virtual ~TryThisAlarm(){}

		virtual void Initialize();
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

	class TryThisStage : public Script
	{
	public:
		TryThisStage(){}
		virtual ~TryThisStage(){}

		virtual void Initialize();
	};
}


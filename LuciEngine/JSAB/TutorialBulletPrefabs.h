#pragma once
#include "LGameObject.h"

namespace lu
{
	class MeshRenderer;
}

namespace lu::JSAB
{
	class TutorialEightBulletsPrefab : public GameObject
	{
	public:
		TutorialEightBulletsPrefab(){}
		virtual ~TutorialEightBulletsPrefab(){}

		virtual void Initialize() override;
	private:
		void SetMeshRenderer(MeshRenderer* mr);
		void SetEnterEffect(MeshRenderer* mr);
		void CreateEnterEffect();
	};

	class TutorialBurstBulletsPrefab : public GameObject
	{
	public:
		virtual void Initialize() override;
	};

	class TutorialBeatBulletsPrefab : public GameObject
	{
	public:
		virtual void Initialize() override;
	};
	class TutorialRoundBulletsPrefab : public GameObject
	{
	public:
		virtual void Initialize() override;
	};
}


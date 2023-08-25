#pragma once
#include "LGameObject.h"

namespace lu
{
	class MeshRenderer;
	class Animator;
}

namespace lu::JSAB
{
	class TutorialEightBulletsPrefab : public GameObject
	{
	public:
		virtual void Initialize() override;
		virtual void OnEnable();
	private:
		void SetMeshRenderer(MeshRenderer* mr);
		void SetEnterEffect(MeshRenderer* mr);
		void CreateEnterEffect();
		Animator* mEnterEffect;
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


#pragma once
#include "LGameObject.h"
namespace lu
{
	class Animator;
}
namespace lu::JSAB
{
	class TitleObject : public GameObject
	{
	public:
		TitleObject(eLayerType layer):GameObject(layer) {}
		virtual ~TitleObject() {}
		virtual void Initialize() override;
		void OnBeat();
		void SetScaleToOrg();
	private:
		Vector3 orgScale;
		Animator* mAnim;
		bool beat;
	};
}


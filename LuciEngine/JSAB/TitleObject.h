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
		void OnAppear();
	private:
		Vector3 orgScale;
		Animator* mImgAnim;
		Animator* mAnim;
		Animator* mLight;
		bool beat;
	};
}


#pragma once
#include "LGameObject.h"
namespace lu
{
	class Animator;
	class MeshRenderer;
	class Text;
}
namespace lu::JSAB{

	class MenuButtonObject : public GameObject
	{
	public:
		MenuButtonObject(eLayerType layer):GameObject(layer){}
		virtual ~MenuButtonObject(){}

		virtual void Initialize() override;
		void Hide();
		void Show();
		void ShowWithOutAnim();
		void OnFocus();
		void OffFocus();
		void Activate();
		void SetScene(std::wstring sceneName, std::wstring text, Vector2 offset);
	private:
		Animator* mAnim;
		std::wstring mSceneName;
		MeshRenderer* mTag;
		MeshRenderer* mSideTag;
		Text* mText;
		
		std::shared_ptr<Texture> mOnPointTag;
		std::shared_ptr<Texture> mOffPointTag;
		std::shared_ptr<Texture> mOnPointSideTag;
		std::shared_ptr<Texture> mOffPointSideTag;
		

	};
}


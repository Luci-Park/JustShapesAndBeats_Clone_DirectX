#include "MenuButtonObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LObject.h"
#include "LAnimator.h"
#include "LText.h"
#include "LSceneManager.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
namespace lu::JSAB
{
	void MenuButtonObject::Initialize()
	{
		mText = AddComponent<Text>();
		mText->text = L"STORY";
		mText->size = 60;
		float height = 80.0f;
		{
			auto tag = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
			tag->SetName(L"Button Base");
			auto mat = Resources::Load<Material>(L"ButtonTagMat" + std::to_wstring(mColliderID), L"Menu_Tag_Story_OnPoint");
			mTag = tag->AddComponent<MeshRenderer>();
			mTag->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mTag->SetMaterial(mat);

			float width = mat->GetTexture()->GetRatioWidth(height);
			tag->mTransform->SetScale(Vector3(width, height, 1));
			tag->mTransform->SetLocalPosition(Vector3(0, 0, 0));
		}
		{

			auto tag = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
			tag->SetName(L"Button SideTag");
			auto mat = Resources::Load<Material>(L"ButtonSideTagMag" + std::to_wstring(mColliderID), L"Menu_SideTag_Story_OnPoint");
			mSideTag = tag->AddComponent<MeshRenderer>();
			mSideTag->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mSideTag->SetMaterial(mat);
			tag->mTransform->SetLocalPosition(Vector3(0, 0, 2));

			float width = mat->GetTexture()->GetRatioWidth(height);
			tag->mTransform->SetScale(Vector3(width, height, 1));
			tag->mTransform->SetLocalPosition(Vector3(-359.7061, 0, 0));			
		}

		mAnim = AddComponent<Animator>();
		auto a = mAnim->CreateAnimation(L"Appear");
		a->AddScaleKey(0, {0, 1, 1});
		a->AddScaleKey(0.2, { 1.3, 1, 1 });
		a->AddScaleKey(0.5, Vector3::One);

		a = mAnim->CreateAnimation(L"Disappear");
		a->AddScaleKey(0, { 1, 1, 1 });
		a->AddScaleKey(0.2, { 1.3, 1, 1 });
		a->AddScaleKey(0.5, {0, 1, 1});
		a->AddFunctionKey(0.7, std::bind(&GameObject::SetActive, this, false));

		mOnPointSideTag = Resources::Find<Texture>(L"Menu_SideTag_Story_OnPoint");
		mOffPointSideTag = Resources::Find<Texture>(L"Menu_SideTag_Story_OffPoint");
		mOnPointTag = Resources::Find<Texture>(L"Menu_Tag_Story_OnPoint");
		mOffPointTag = Resources::Find<Texture>(L"Menu_Tag_Story_OffPoint");
		GameObject::Initialize();
	}
	void MenuButtonObject::Hide()
	{
		mAnim->PlayAnimation(L"Disappear", false);
	}
	void MenuButtonObject::Show()
	{
		SetActive(true);
		mAnim->PlayAnimation(L"Appear", false);
	}
	void MenuButtonObject::ShowWithOutAnim()
	{
		SetActive(true);
		mTransform->SetScale(Vector3::One);
	}
	void MenuButtonObject::OnFocus()
	{
		mTag->GetMaterial()->SetTexture(mOnPointTag);
		mSideTag->GetMaterial()->SetTexture(mOnPointSideTag);
		Vector3 pos = mTransform->GetPosition();
		pos.x = 480;
		mTransform->SetPosition(pos);
		mText->color = Color::white;
		mAnim->PlayAnimation(L"Appear", false);
	}
	void MenuButtonObject::OffFocus()
	{
		mTag->GetMaterial()->SetTexture(mOffPointTag);
		mSideTag->GetMaterial()->SetTexture(mOffPointSideTag);
		Vector3 pos = mTransform->GetPosition();
		pos.x = 600;
		mTransform->SetPosition(pos);
		mText->color = { 0.5, 0.5, 0.5, 1 };
	}
	void MenuButtonObject::Activate()
	{
		SceneManager::LoadScene(mSceneName);
	}
	void MenuButtonObject::SetScene(std::wstring sceneName, std::wstring text, Vector2 offset)
	{
		mText->text = text;
		mText->offset = offset;
		mSceneName = sceneName;
	}
}
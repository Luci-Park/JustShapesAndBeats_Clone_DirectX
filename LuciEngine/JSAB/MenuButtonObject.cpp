#include "MenuButtonObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LSceneManager.h"
#include "LAnimator.h"
#include "LText.h"
namespace lu::JSAB
{
	void MenuButtonObject::Initialize()
	{
		float height = 80.0f;
		float y = 200;
		{
			GameObject* tag = new GameObject(GetLayer());
			tag->SetName(L"Main Button");
			std::shared_ptr<Material> mat = Resources::Find<Material>(L"Story_Tag");
			if (mat == nullptr)
			{
				mat = std::make_shared<Material>();
				mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
				mat->SetTexture(Resources::Find<Texture>(L"Menu_Tag_Story_OnPoint"));
				Resources::Insert(L"Story_Tag", mat);
				mat->SetRenderingMode(eRenderingMode::Transparent);
			}

			MeshRenderer* mr = tag->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(mat);
			tag->mTransform->SetPosition(Vector3(548.55865, y, 2));
			float width = mat->GetTexture()->GetRatioWidth(height);
			tag->mTransform->SetScale(Vector3(width, height, 1));
			tag->mTransform->SetParent(mTransform);
			/*auto t = tag->AddComponent<Text>();
			t->color = Color::white;
			t->text = L"STORY";
			t->size = 50;*/
			//t->offset.x = 350;
			//t->offset.y = -70;

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, tag);
		}
		{
			GameObject* tag = new GameObject(GetLayer());
			std::shared_ptr<Material> mat = Resources::Find<Material>(L"Story_SideTag");

			if (mat == nullptr)
			{
				mat = std::make_shared<Material>();
				mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
				mat->SetTexture(Resources::Find<Texture>(L"Menu_SideTag_Story_OnPoint"));
				Resources::Insert(L"Story_Tag", mat);
				mat->SetRenderingMode(eRenderingMode::Transparent);
			}

			MeshRenderer* mr = tag->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(mat);
			float width = mat->GetTexture()->GetRatioWidth(height);
			tag->mTransform->SetScale(Vector3(width, height, 1));
			tag->mTransform->SetPosition(Vector3(187.80876, y, 1));
			tag->mTransform->SetParent(mTransform);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, tag);

			mAnim = AddComponent<Animator>();
			auto a = mAnim->CreateAnimation(L"Appear");
			a->AddScaleKey(0, {0, 1, 1});
			a->AddPositionKey(0, { -200, 0, 0 });
			a->AddScaleKey(0.2, { 1.3, 1, 1 });
			a->AddPositionKey(0.3, { 20, 0, 0 });
			a->AddScaleKey(0.5, Vector3::One);
			a->AddPositionKey(0.7, { 0, 0, 0 });

			a = mAnim->CreateAnimation(L"Disappear");
			a->AddScaleKey(0, { 1, 1, 1 });
			a->AddPositionKey(0, { 0, 0, 0 });
			a->AddScaleKey(0.2, { 1.3, 1, 1 });
			a->AddPositionKey(0.3, { 20, 0, 0 });
			a->AddScaleKey(0.5, {0, 1, 1});
			a->AddPositionKey(0.7, { -200, 0, 0 });
			a->AddFunctionKey(0.7, std::bind(&GameObject::SetActive, this, false));
		}
		GameObject::Initialize();
	}
}
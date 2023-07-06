#include "MenuButtonObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LSceneManager.h"
namespace lu::JSAB::Menu
{
	void MenuButtonObject::Initialize()
	{
		{
			GameObject* tag = new GameObject();
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
			tag->mTransform->SetPosition(Vector3(90, 90, 2));
			tag->mTransform->SetScale(Vector3(50, 17, 1));
			tag->mTransform->SetParent(mTransform);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, tag);
		}
		{
			GameObject* tag = new GameObject();
			std::shared_ptr<Material> mat = Resources::Find<Material>(L"Story_SideTag");

			if (mat == nullptr)
			{
				mat = std::make_shared<Material>();
				mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
				mat->SetTexture(Resources::Find<Texture>(L"Story_SideTag"));
				Resources::Insert(L"Story_Tag", mat);
				mat->SetRenderingMode(eRenderingMode::Transparent);
			}

			MeshRenderer* mr = tag->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(mat);
			tag->mTransform->SetPosition(Vector3(80, 90, 2));
			tag->mTransform->SetScale(Vector3(10, 17, 1));
			tag->mTransform->SetParent(mTransform);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, tag);
		}
		GameObject::Initialize();
	}
}
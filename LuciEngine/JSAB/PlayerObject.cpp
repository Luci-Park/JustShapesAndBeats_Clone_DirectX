#include "PlayerObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LSceneManager.h"
#include "Player.h"
#include "LObject.h"
#include "LAnimator.h"
#include "LAnimation.h"
namespace lu::JSAB
{
	PlayerObject::PlayerObject()
	{
	}
	PlayerObject::~PlayerObject()
	{
	}
	void PlayerObject::Initialize()
	{
		SetName(L"Player");
		std::shared_ptr<Material> mat = CreatePlayerMat();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetActive(false);
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);
		
		mTransform->SetScale(Vector3(22.3, 22.3, 1));
		AddComponent<Collider2D>();

		Player* script = AddComponent<Player>();

		{
			GameObject* dashoutline = object::Instantiate<GameObject>(mTransform, eLayerType::Player);
			dashoutline->SetName(L"PlayerOutline");
			dashoutline->mTransform->SetLocalScale({ 1.5f, 1.5f, 1.f });
			std::shared_ptr<Material> outlinemat = CreateDashOutlineMat();
			MeshRenderer* outlinemr = dashoutline->AddComponent<MeshRenderer>();
			outlinemr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			outlinemr->SetMaterial(outlinemat);
			outlinemr->SetColor(Color::white);
			//outlinemr->UseColor(true);
			//dashoutline->SetState(eState::InActive);
			script->SetDashOutline(dashoutline);
			dashoutline->AddComponent<AnimationTester>();
		}
	}
	std::shared_ptr<Material> PlayerObject::CreatePlayerMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"PlayerMat");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"player1"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"PlayerMat", mat);
		}
		return mat;
	}
	std::shared_ptr<lu::Material> PlayerObject::CreateDashOutlineMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"DashOutlineMat");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"player1"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"DashOutlineMat", mat);
		}
		return mat;
	}
	std::shared_ptr<lu::Material> PlayerObject::CreateDashEffectMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"DashEffectMat");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Dash"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"DashEffectMat", mat);
		}
		return mat;
	}
	void Pieces::Initialize()
	{
		float point = 80;
		Vector3 pos[] = {
			{-1, 1, 0},
			{0, 1, 0},
			{1, 1, 0},
			{-1, 0, 0},
			{1, 0, 0},
			{-1, -1, 0},
			{0, -1, 0},
			{1, -1, 0}
		};
		float rot[] = {
			PI * 0.25,
			0,
			PI * -0.25,
			PI * 0.5,
			PI * -0.5,
			PI * 0.75,
			PI,
			PI * -0.75
		};
		for (int i = 1; i <= 8; ++i)
		{
			GameObject* piece = new GameObject();
			std::shared_ptr<Material> mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"PlayerPiece_" + std::to_wstring(i)));
			mat->SetRenderingMode(eRenderingMode::CutOut);

			MeshRenderer* mr = piece->AddComponent<MeshRenderer>();
			mr->SetMaterial(mat);
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

			piece->mTransform->SetScale(Vector3(7, mat->GetTexture()->GetRatioHeight(7), 1));
			piece->mTransform->SetPosition(pos[i - 1] * point);
			pos[i - 1].z + 0.1;
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, piece);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, CreateLight(pos[i-1] * point, rot[i - 1]));
		}
	}
	GameObject* Pieces::CreateLight(Vector3 pos, float rotation)
	{
		GameObject* light = new GameObject();
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"PlayerPiece_Light");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"PlayerPiece_Light"));
			mat->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"PlayerPiece_Light", mat);
		}

		MeshRenderer* mr = light->AddComponent<MeshRenderer>();
		mr->SetMaterial(mat);
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		Vector3 scale = Vector3(mat->GetTexture()->GetRatioWidth(1000), 1000, 1);
		light->mTransform->SetScale(scale);
		light->mTransform->SetPosition(pos);
		light->mTransform->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, rotation));

		return light;
	}
}
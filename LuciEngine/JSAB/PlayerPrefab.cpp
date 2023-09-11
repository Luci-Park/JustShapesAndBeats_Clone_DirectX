#include "PlayerPrefab.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LSceneManager.h"
#include "Player.h"
#include "LObject.h"
#include "LAnimator.h"
#include "LParticleSystem.h"
namespace lu::JSAB
{
	PlayerPrefab::PlayerPrefab(eLayerType layer)
		:GameObject(layer)
	{
	}
	PlayerPrefab::~PlayerPrefab()
	{
	}
	void PlayerPrefab::Initialize()
	{
		SetName(L"Player");
		std::shared_ptr<Material> mat = CreatePlayerMat();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);
		mr->SetColor(Color::magenta);
		
		mTransform->SetScale(Vector3(22.3, 22.3, 1));
		AddComponent<Collider2D>();

		Player* script = AddComponent<Player>();
		{
			auto p = AddComponent<ParticleSystem>();
			p->GetMaterial()->SetTexture(Resources::Find<Texture>(L"player1"));
			p->Duration = 10;
			p->MaxParticles = 1000;
			p->Loop = true;
			p->RateOverTime = 0;
			p->RateOverDistance = 1.2;

			p->SetOffset(Vector3::Zero);
			p->SetAngle(60, -60);
			p->SetLifeTime(1);
			p->SetSize(10, 0);
			p->SetTint({ 1, 1, 1, 0.5 }, { 0, 0, 1, 0.5 });
			p->SetWorldSpace(ParticleSystem::Space::world);
			p->SetGravity(0);
			p->SetStartSpeed(20);
			p->Play();
		}


		{
			GameObject* dashoutline = object::Instantiate<GameObject>(mTransform, eLayerType::Player);
			dashoutline->SetName(L"PlayerOutline");
			dashoutline->mTransform->SetLocalScale({ 1.5f, 1.5f, 1.f });
			std::shared_ptr<Material> outlinemat = CreateDashOutlineMat();
			MeshRenderer* outlinemr = dashoutline->AddComponent<MeshRenderer>();
			outlinemr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			outlinemr->SetMaterial(outlinemat);
			outlinemr->SetColor(Color::white);
			outlinemr->UseColor(true);
			dashoutline->SetState(eState::InActive);
			script->SetDashOutline(dashoutline);
		}
		{
			GameObject* dashBurst = object::Instantiate<GameObject>(eLayerType::Player);
			dashBurst->SetName(L"PlayerBurst");
			dashBurst->mTransform->SetScale({ 22.3* 4, 22.3 * 4, 1 });
			std::shared_ptr<Material> mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTint({0, 1, 1, 1});
			MeshRenderer* mr = dashBurst->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(mat);
			mr->SetActive(false);
			Animator* ani = dashBurst->AddComponent<Animator>();
			Animation* anim = ani->CreateAnimation(L"Burst");
			float duration = 0.2f;
			float startTime = 0;
			float burstStep = 0.2 * 0.2;
			anim->AddRendererActiveKey(0, true);
			anim->AddTextureKey(0, Resources::Find<Texture>(L"Burst1"));
			anim->AddTextureKey(0 + burstStep * 0.5, Resources::Find<Texture>(L"Burst2"));
			anim->AddTextureKey(0 + burstStep, Resources::Find<Texture>(L"Burst3"));
			anim->AddTextureKey(0 + burstStep * 0.5, Resources::Find<Texture>(L"Burst4"));
			anim->AddTextureKey(duration - burstStep, Resources::Find<Texture>(L"Burst5"));
			anim->AddRendererActiveKey(duration, false);
			script->SetDashBurst(dashBurst);
		}

		GameObject* shield = object::Instantiate<GameObject>(eLayerType::Player);
		shield->AddComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(CreateShieldGaugeMat());
		shield->mTransform->SetScale(mTransform->GetScale() * 2.5);
		auto shieldScript = shield->AddComponent<ShieldScript>();

		auto s = object::Instantiate<GameObject>(shield->mTransform, eLayerType::Player);
		s->AddComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(CreateShieldMat());
		
		shieldScript->SetBack(s);
		shieldScript->SetPlayer(mTransform);
		shieldScript->CreateAnimation();
		script->SetShield(shieldScript);
		shieldScript->Owner()->SetActive(false);
	}
	std::shared_ptr<Material> PlayerPrefab::CreatePlayerMat()
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
	std::shared_ptr<lu::Material> PlayerPrefab::CreateDashOutlineMat()
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
	std::shared_ptr<lu::Material> PlayerPrefab::CreateDashEffectMat()
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
	std::shared_ptr<graphics::Material> PlayerPrefab::CreateShieldGaugeMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"ShieldGaugeMat");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Shield1"));
			mat->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ShieldGaugeMat", mat);
		}
		return mat;
	}
	std::shared_ptr<graphics::Material> PlayerPrefab::CreateShieldMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"ShieldMat");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"ShieldBackground"));
			mat->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ShieldMat", mat);
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
			GameObject* piece = object::Instantiate<GameObject>(eLayerType::Player);
			std::shared_ptr<Material> mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"PlayerPiece_" + std::to_wstring(i)));
			mat->SetRenderingMode(eRenderingMode::CutOut);

			MeshRenderer* mr = piece->AddComponent<MeshRenderer>();
			mr->SetMaterial(mat);
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

			piece->mTransform->SetScale(Vector3(7, mat->GetTexture()->GetRatioHeight(7), 1));
			piece->mTransform->SetPosition(pos[i - 1] * point);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, piece);
			CreateLight(pos[i - 1] * point, rot[i - 1]);
		}
	}
	GameObject* Pieces::CreateLight(Vector3 pos, float rotation)
	{
		GameObject* light = object::Instantiate<GameObject>(eLayerType::Player);
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
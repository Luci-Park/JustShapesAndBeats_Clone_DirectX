#include "PlayerPieces.h"
#include "LObject.h"
#include "LResources.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LAnimator.h"
#include "LAudioSource.h"
namespace lu::JSAB
{
	void PlayerPieces::Initialize()
	{
		float point = 50;
		Script::Initialize();
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
		float appearEnd = 0.5;

		mAudio = Owner()->AddComponent<AudioSource>();

		mAnim = Owner()->AddComponent<Animator>();
		auto ani = mAnim->CreateAnimation(L"Opening");
		ani->AddFunctionKey(3, std::bind(&PlayerPieces::Start, this));
		ani->AddFunctionKey(3 + appearEnd + 1.6, std::bind(&PlayerPieces::Finish, this));
		for (int i = 1; i <= 8; i++)
		{
			GameObject* piece = object::Instantiate<GameObject>(eLayerType::Player);
			piece->SetName(L"Piece" + std::to_wstring(i));
			
			auto mr = piece->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->
				SetMaterial(Resources::Load<Material>(L"PlayerPiece_" + std::to_wstring(i), L"PlayerPiece_" + std::to_wstring(i)));
			mr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);
			mr->SetColor(Color::white);
			mr->UseColor(true);
			Vector3 scale = Vector3(10, mr->GetMaterial()->GetTexture()->GetRatioHeight(10), 1);
			piece->mTransform->SetScale(Vector3::Zero);
			piece->mTransform->SetPosition(pos[i - 1] * point);

			mPieces[i - 1] = piece->AddComponent<Animator>();
			auto anim = mPieces[i - 1]->CreateAnimation(L"Appear");
			float fract = appearEnd * 0.125;
			anim->AddScaleKey(0, Vector3::Zero);
			anim->AddScaleKey(fract * (i - 1), Vector3::Zero);
			anim->AddScaleKey(fract * i, scale);
			anim->AddScaleKey(appearEnd + 1.3, scale);
			anim->AddScaleKey(appearEnd + 1.5, Vector3::Zero);

			anim->AddPositionKey(0, Vector3::Zero);
			anim->AddPositionKey(fract * (i - 1), Vector3::Zero);
			anim->AddPositionKey(fract * i, pos[i - 1] * point);
			anim->AddPositionKey(appearEnd, pos[i - 1] * point);
			anim->AddPositionKey(appearEnd + 1.3, pos[i - 1] * (point + 10));
			anim->AddPositionKey(appearEnd + 1.5, Vector3::Zero);
		}
		for (int i = 1; i <= 8; i++)
		{
			GameObject* light = object::Instantiate<GameObject>(eLayerType::Player);
			light->SetName(L"PlayerPieceLight" + std::to_wstring(i));

			auto mr = light->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->
				SetMaterial(Resources::Load<Material>(L"PlayerPieceLightMat", L"PlayerPiece_Light"));
			mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
			mr->GetMaterial()->SetTint(Color::clear);

			Vector3 scale = Vector3(mr->GetMaterial()->GetTexture()->GetRatioWidth(1300), 1300, 1);			
			light->mTransform->SetScale(scale);

			Vector3 position = pos[i - 1] * point;
			position.z = 1;
			light->mTransform->SetPosition(position);
			light->mTransform->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, rot[i -1]));

			mLight[i - 1] = light->AddComponent<Animator>();
			auto anim = mLight[i - 1]->CreateAnimation(L"Appear");
			anim->AddTintKey(0, {1, 1, 1, 0});
			anim->AddTintKey(appearEnd, {1, 1, 1, 0});
			anim->AddTintKey(appearEnd + 1.3, {1, 1, 1, 1});
			anim->AddTintKey(appearEnd + 1.5, { 1, 1, 1, 1 });
			anim->AddTintKey(appearEnd + 1.55, { 1, 1, 1, 0 });

			anim->AddPositionKey(appearEnd, pos[i - 1] * point);
			anim->AddPositionKey(appearEnd + 1.3, pos[i - 1] * (point - 20));
			anim->AddPositionKey(appearEnd + 1.5, Vector3::Zero);
		}

		{
			GameObject* light = object::Instantiate<GameObject>(eLayerType::Player);
			light->SetName(L"PlayerPieceOuterLight");

			auto mr = light->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->
				SetMaterial(Resources::Load<Material>(L"PlayerPieceOuterLightMat", L"PlayerPiece_OuterLight"));
			mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
			light->mTransform->SetScale({ 0, 0, 1});

			light->mTransform->SetPosition({0, 0, -1});
			mOuterLight = light->AddComponent<Animator>();
			auto anim = mOuterLight->CreateAnimation(L"Appear");
			anim->AddTintKey(0, { 1, 1, 1, 0 });
			anim->AddTintKey(appearEnd, { 1, 1, 1, 0 });
			anim->AddTintKey(appearEnd + 1.3, { 1, 1, 1, 1 });
			anim->AddTintKey(appearEnd + 1.5, { 1, 1, 1, 1 });
			anim->AddTintKey(appearEnd + 1.55, { 1, 1, 1, 0 });

			anim->AddScaleKey(appearEnd, {1000, 1000, 1});
			anim->AddScaleKey(appearEnd + 1.3, { 1300, 1300, 1 });
			anim->AddScaleKey(appearEnd + 1.5, Vector3::Zero);
		}

		{
			GameObject* light = object::Instantiate<GameObject>(eLayerType::Player);
			light->SetName(L"PlayerPiece_InnerLight");

			auto mr = light->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->
				SetMaterial(Resources::Load<Material>(L"PlayerPieceInnerLightMat", L"PlayerPiece_InnerLight"));
			mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
			light->mTransform->SetScale({ 0, 0, 1 });

			light->mTransform->SetPosition({ 0, 0, 1 });
			mInnerLight = light->AddComponent<Animator>();
			auto anim = mInnerLight->CreateAnimation(L"Appear");
			anim->AddTintKey(0, { 1, 1, 1, 0 });
			anim->AddTintKey(appearEnd, { 1, 1, 1, 0 });
			anim->AddTintKey(appearEnd + 1.3, { 1, 1, 1, 1 });
			anim->AddTintKey(appearEnd + 1.5, { 1, 1, 1, 1 });
			anim->AddTintKey(appearEnd + 1.55, { 1, 1, 1, 0 });

			anim->AddScaleKey(appearEnd, { 50, 50, 1 });
			anim->AddScaleKey(appearEnd + 1.3, { 100, 100, 1 });
			anim->AddScaleKey(appearEnd + 1.5, Vector3::Zero);
		}
	}
	void PlayerPieces::Activate(std::function<void()> callback)
	{
		mCallback = callback;
		mAnim->PlayAnimation(L"Opening", false);
	}
	void PlayerPieces::Start()
	{
		for (int i = 0; i < 8; i++)
		{
			mPieces[i]->PlayAnimation(L"Appear", false);
			mLight[i]->PlayAnimation(L"Appear", false);
		}
		mInnerLight->PlayAnimation(L"Appear", false);
		mOuterLight->PlayAnimation(L"Appear", false);
		mAudio->PlayOneShot(Resources::Find<AudioClip>(L"SFX_HEX_LEVEL_TRANSITION_OUT_FAST"), 0.5);
	}
	void PlayerPieces::Finish()
	{
		mAudio->PlayOneShot(Resources::Find<AudioClip>(L"SFX_HEX_PLAYER_TRANSITION_FINISH"), 2);
		mCallback();
	}
}
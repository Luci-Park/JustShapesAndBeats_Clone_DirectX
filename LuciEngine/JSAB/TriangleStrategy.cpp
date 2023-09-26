#include "TriangleStrategy.h"
#include "Player.h"
#include "LGameObject.h"
#include "LRigidBody.h"
#include "LTransform.h"
#include "LAudioSource.h"
#include "LAnimator.h"
#include "LResources.h"
#include "TutorialMusicController.h"
#include "LSceneManager.h"
#include "CameraScript.h"
#include "LCamera.h"
namespace lu::JSAB
{
#pragma region StrategyBase
	TriangleStrategy::TriangleStrategy(GameObject* owner)
	{
		mOwner = owner;
	}
#pragma endregion

#pragma region TutorialStrategy
	TutorialStrategy::TutorialStrategy(GameObject* owner, Animator* triangleAnim)
		:TriangleStrategy(owner)
	{
		mRB = owner->GetComponent<Rigidbody>();
		mTransform = owner->mTransform;
		AudioSource* mAudio = owner->GetComponent<AudioSource>();
		mTriangleAnim = triangleAnim;
		mClip = Resources::Find<AudioClip>(L"SFX_HEX_LEVEL_COMPLETE_TUTO_SILENCE");
	}
	void TutorialStrategy::OnAppear()
	{
		mTriangleAnim->PlayAnimation(L"Idle", true);
		mTransform->SetPosition(680, 0, -1);
		mRB->SetVelocity(Vector3::Left * 80);
		mRB->SetDrag(25);
	}
	void TutorialStrategy::OnCollisionEnter(Player* player)
	{
		mPlayer = player;
		player->Hold();
		mRB->SetVelocity(Vector3::Zero);
		Vector3 pos = { 552.243652, 0, -1 };
		mTransform->SetPosition(pos);
		player->mTransform->SetPosition(pos);
		double diff = mMusic->GetDiff();
		diff = std::max(6.928 - diff, 0.0);
		mAudio->SetClip(mClip);
		mAudio->Play();
		mAudio->SetPosition(diff);
		mTriangleAnim->PlayAnimation(L"Burst", false);
		mTriangleAnim->SetTime(diff);
		mMusic->PlayNextPart();
	}
	void TutorialStrategy::OnBurst()
	{
		mPlayer->mTransform->SetPosition(Vector3(-540, 0, -5));
		mPlayer->Release();
		SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->LevelTrans();
	}
#pragma endregion

#pragma region TutorialPrevStrategy

	TutorialStartStrategy::TutorialStartStrategy(GameObject* owner, Animator* triangleAnim)
		:TriangleStrategy(owner)
	{
		mRB = owner->GetComponent<Rigidbody>();
		mTransform = owner->mTransform;
		AudioSource* mAudio = owner->GetComponent<AudioSource>();
		mTriangleAnim = triangleAnim;
		mClip = Resources::Find<AudioClip>(L"SFX_HEX_LEVEL_COMPLETE_TUTO");
	}
	void TutorialStartStrategy::OnAppear()
	{
		mTriangleAnim->PlayAnimation(L"Idle", true);
		mTransform->SetPosition(680, 0, -1);
		mRB->SetVelocity(Vector3::Left * 80);
		mRB->SetDrag(25);
	}
	void TutorialStartStrategy::OnCollisionEnter(Player* player)
	{
		mPlayer = player;
		player->Hold();
		mRB->SetVelocity(Vector3::Zero);
		Vector3 pos = { 552.243652, 0, -1 };
		mTransform->SetPosition(pos);
		player->mTransform->SetPosition(pos);
		mAudio->SetClip(mClip);
		mAudio->Play();
		mTriangleAnim->PlayAnimation(L"Burst", false);
	}
	void TutorialStartStrategy::OnBurst()
	{
		mPlayer->mTransform->SetPosition(Vector3(-540, 0, -5));
		mPlayer->Release();
		SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->LevelTrans();
		mMusic->Play();
	}
#pragma endregion
#pragma region LevelFinStrategy

#pragma endregion
}
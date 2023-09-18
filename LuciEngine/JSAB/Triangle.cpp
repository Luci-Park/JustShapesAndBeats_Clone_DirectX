#include "Triangle.h"
#include "LCollider2D.h"
#include "LGameObject.h"
#include "MusicController.h"
#include "TutorialMusicController.h"
#include "LSceneManager.h"
#include "LRigidBody.h"
#include "LCamera.h"
#include "CameraScript.h"
namespace lu::JSAB
{
	//1.872
	//tuto - 4.146
	//5.354
	void Triangle::OnCollisionEnter(Collider2D* other)
	{
		if(mTriangleAnim == nullptr)
			mTriangleAnim = Owner()->GetComponentInChildren<Animator>();
		if (other->Owner()->GetLayer() == eLayerType::Player)
		{
			mPlayer = other->Owner()->GetComponent<Player>();
			mPlayer->Hold();
			other->Owner()->mTransform->SetPosition(mTransform->GetPosition());
			auto tuto = dynamic_cast<TutorialMusicController*>(MusicController::Instance);
			if (tuto)
			{
				double diff = tuto->GetDiff();
				diff = std::max(6.928 - diff, 0.0);
				mAudio->SetClip(mTuto);
				mAudio->Play();
				mAudio->SetPosition(diff);
				mTriangleAnim->PlayAnimation(L"Burst", false);
				mTriangleAnim->SetTime(diff);
				tuto->PlayNextPart();
			}
		}
	}
	void Triangle::SetClips(std::shared_ptr<AudioClip> tuto, std::shared_ptr<AudioClip> level)
	{
		mTuto = tuto;
		mLevel = level;
	}
	void Triangle::Setup()
	{
		mTriangleAnim = Owner()->GetComponentInChildren<Animator>();
		mAudio = Owner()->GetComponent<AudioSource>();
	}
	void Triangle::TutorialAppear()
	{
		Owner()->SetActive(true);
	}
	void Triangle::LevelAppear()
	{
	}
	void Triangle::OnTutoBurst()
	{
		mPlayer->mTransform->SetPosition(Vector3(-540, 0, -5));
		mPlayer->Release();
		auto tuto = dynamic_cast<TutorialMusicController*>(MusicController::Instance);
		if (tuto)
			tuto->PlayNextPart();
		mTriangleAnim->PlayAnimation(L"Idle", true);
		SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->LevelTrans();
	}
	void Triangle::OnLevelComplete()
	{
	}
}

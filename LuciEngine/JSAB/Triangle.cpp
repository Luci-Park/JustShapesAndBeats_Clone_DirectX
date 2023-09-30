#include "Triangle.h"
#include "LCollider2D.h"
#include "LGameObject.h"
#include "MusicController.h"
#include "TutorialMusicController.h"
#include "LSceneManager.h"
#include "LRigidBody.h"
#include "LCamera.h"
#include "CameraScript.h"
#include "LAnimator.h"
namespace lu::JSAB
{
	InGameTriangle::~InGameTriangle()
	{
		for (int i = 0; i < (UINT)TriangleStrategy::eTriangleStrategyType::End; i++)
		{
			if (mStrategy[i] != nullptr)
			{
				delete mStrategy[i];
				mStrategy[i] = nullptr;
			}
		}
	}
	void InGameTriangle::Initialize()
	{
		mTriangleAnim = Owner()->GetComponentInChildren<Animator>();
		mStrategy[(UINT)TriangleStrategy::eTriangleStrategyType::Tutorial] = new TutorialStrategy(Owner(), mTriangleAnim);
		mStrategy[(UINT)TriangleStrategy::eTriangleStrategyType::PrevTutorial] = new TutorialStartStrategy(Owner(), mTriangleAnim);
		mStrategy[(UINT)TriangleStrategy::eTriangleStrategyType::LevelFinish] = new LevelFinishStrategy(Owner(), mTriangleAnim);

		mCurrStrategy = TriangleStrategy::eTriangleStrategyType::Tutorial;

	}
	void InGameTriangle::OnCollisionEnter(Collider2D* other)
	{
		if (other->Owner()->GetLayer() == eLayerType::Player)
		{
			auto player = other->Owner()->GetComponent<Player>();
			mStrategy[(UINT)mCurrStrategy]->OnCollisionEnter(player);
		}
	}
	void InGameTriangle::Appear()
	{
		mTriangleAnim->PlayAnimation(L"Idle", true);
		mStrategy[(UINT)mCurrStrategy]->OnAppear();
		Owner()->SetActive(true);
	}
	void InGameTriangle::Burst()
	{
		mStrategy[(UINT)mCurrStrategy]->OnBurst();
		Owner()->SetActive(false);
	}
}

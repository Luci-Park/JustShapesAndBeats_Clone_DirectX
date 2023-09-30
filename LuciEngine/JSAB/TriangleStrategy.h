#pragma once
namespace lu
{
	class AudioSource;
	class AudioClip;
	class GameObject;
	class Rigidbody;
	class Transform;
	class Animator;
}
namespace lu::JSAB
{
	class Player;
	class TutorialMusicController;
	class TutorialManager;
	class TriangleStrategy
	{
	public:
		enum class eTriangleStrategyType{PrevTutorial, Tutorial, LevelFinish, End};
		TriangleStrategy(GameObject* owner, Animator* triangleAnim);
		virtual ~TriangleStrategy(){}
		virtual void OnAppear() = 0;
		virtual void OnCollisionEnter(Player* player) = 0;
		virtual void OnBurst() = 0;
	
	protected:
		GameObject* mOwner;
		AudioSource* mAudio;
		Rigidbody* mRB;
		Transform* mTransform;
		Animator* mTriangleAnim;
		Player* mPlayer;
	};

	class TutorialStrategy : public TriangleStrategy
	{
	public:
		TutorialStrategy(GameObject* owner, Animator* triangleAnim);
		virtual ~TutorialStrategy() {}
		virtual void OnAppear() override;
		virtual void OnCollisionEnter(Player* player) override;
		virtual void OnBurst() override;
	private:
		std::shared_ptr<AudioClip> mClip;
		TutorialMusicController* mMusic;
	};

	class TutorialStartStrategy : public TriangleStrategy
	{
	public:
		TutorialStartStrategy(GameObject* owner, Animator* triangleAnim);
		virtual ~TutorialStartStrategy() {}
		virtual void OnAppear() override;
		virtual void OnCollisionEnter(Player* player) override;
		virtual void OnBurst() override;
	private:
		std::shared_ptr<AudioClip> mClip;
		TutorialManager* mManager;
	};

	class LevelFinishStrategy : public TriangleStrategy
	{
	public:
		LevelFinishStrategy(GameObject* owner, Animator* triangleAnim);
		virtual ~LevelFinishStrategy() {}
		virtual void OnAppear() override;
		virtual void OnCollisionEnter(Player* player) override;
		virtual void OnBurst() override;
	private:
		std::shared_ptr<AudioClip> mClip;
		TutorialManager* mManager;
	};
}


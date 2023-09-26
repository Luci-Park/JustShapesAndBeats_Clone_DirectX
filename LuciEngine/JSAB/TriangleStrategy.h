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
	class TriangleStrategy
	{
	public:
		enum class eTriangleStrategyType{PrevTutorial, Tutorial, LevelFinish, End};
		TriangleStrategy(GameObject* owner);
		virtual ~TriangleStrategy(){}
		virtual void OnAppear() = 0;
		virtual void OnCollisionEnter(Player* player) = 0;
		virtual void OnBurst() = 0;
	
	protected:
		GameObject* mOwner;
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
		AudioSource* mAudio;
		Rigidbody* mRB;
		Transform* mTransform;
		Animator* mTriangleAnim;
		std::shared_ptr<AudioClip> mClip;
		Player* mPlayer;
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
		AudioSource* mAudio;
		Rigidbody* mRB;
		Transform* mTransform;
		Animator* mTriangleAnim;
		std::shared_ptr<AudioClip> mClip;
		Player* mPlayer;
		TutorialMusicController* mMusic;
	};
}


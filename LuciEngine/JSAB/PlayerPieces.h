#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
	class AudioSource;
}
namespace lu::JSAB
{
	class PlayerPieces : public Script
	{
	public:
		PlayerPieces():mCallback(nullptr) {}
		~PlayerPieces() {}

		virtual void Initialize() override;

		void Activate(std::function<void()> callback);
		void Start();
		void Finish();
	private:
		Animator* mPieces[8];
		Animator* mLight[8];
		Animator* mOuterLight;
		Animator* mInnerLight;
		Animator* mAnim;
		AudioSource* mAudio;
		std::function<void()> mCallback;
	};
}


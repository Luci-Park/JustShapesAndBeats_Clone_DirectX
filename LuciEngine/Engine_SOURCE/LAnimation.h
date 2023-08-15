#pragma once
#include "LResource.h"
namespace lu
{
	class Animator;
	class Animation : public Resource
	{
	public:
		Animation();
		~Animation();
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();
		
		void Reset();
		bool IsComplete() { return mbComplete; }

	private:
		Animator* mAnimator;
		float mTime;
		bool mbComplete;
	};
}


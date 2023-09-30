#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
#include "Player.h"
#include "TriangleStrategy.h"
namespace lu::JSAB
{
	class InGameTriangle : public Script
	{
	public:
		InGameTriangle() {}
		virtual ~InGameTriangle();
		virtual void Initialize() override;
		virtual void OnCollisionEnter(Collider2D* other) override;
		void SetStrategy(TriangleStrategy::eTriangleStrategyType strategy) { mCurrStrategy = strategy; }
		void Appear();
		void Burst();
	private:
		Animator* mTriangleAnim;
		TriangleStrategy* mStrategy[(UINT)TriangleStrategy::eTriangleStrategyType::End];
		TriangleStrategy::eTriangleStrategyType mCurrStrategy;
	};
}


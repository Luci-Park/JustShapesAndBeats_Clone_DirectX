#pragma once
#include "Bullet.h"
#include "DubwooferSpikeBullet.h"
namespace lu::JSAB
{
	class DubwooferSpikeDropper : public Bullet
	{
	public:
		DubwooferSpikeDropper() {}
		virtual ~DubwooferSpikeDropper() {}

		void DropSpike();
	private:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override {}
		virtual void OnOutro()override {}
		virtual void WhileOutro(double time);
		virtual void OnDeActivate()override{}
	private:
		std::vector<DubwooferSpikeBullet*> mSpikes;
		Vector3 mWaitPos;
		Vector3 mActivePos;
		int prevIdx = -1;

	};
}


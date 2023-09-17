#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialRoundSpikes.h"
#include "TutorialBurst.h"
#include "TutorialBeam.h"
#include "TutorialBeatCircle.h"
#include "TutorialGiantCircle.h"
#include "LObject.h"
#include "LCamera.h"
#include "LAnimator.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
		: mRoundSpikes(40)
		, mBursts(8)
		, mBeams(40)
		, mBeatCircles(8)
		, mGCircles(6)
	{
	}
	void TutorialManager::Initialize()
	{
		mMusic = Owner()->GetComponent<TutorialMusicController>();
		OnStageChange(0);
	}
	void TutorialManager::OnStageChange(int stage)
	{
		if (stage == 0) Stage1();
		if (stage == 1) Stage2();
		if (stage == 2) Stage3();
		if (stage == 3) Stage4();
		if (stage == 4) Stage5();
		if (stage == 5) Stage6();
	}
	void TutorialManager::Stage1()
	{
		double beat[] = {
			0.850, 1.450, 2.100, 2.500, 3.150, 4.200, 4.800, 5.450, 5.850, 6.500, 6.800, 7.150, 7.500
		};
		float posY[] = { -51, 41, 230, -230 };//normal, small high, very high, very low
		int idicies[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2 };

		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		float x = bounds.right + 42 * 0.5;
		float endX = bounds.left - 42 * 0.5;
		for (int i = 0; i < 13; i++)
		{
			Vector3 pos = { x, posY[idicies[i]], 1 };
			Vector3 endPos = { endX, posY[idicies[i]], 1 };
			TutorialRoundSpikes* bullet = mRoundSpikes.GetNext();
			bullet->mTransform->SetPosition(pos);
			bullet->Setup(7, pos, endPos);
			bullet->SetTimeline(mMusic, 0, beat[i], 0);
		}
	}
	void TutorialManager::Stage2()
	{
		double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
		double beat[] = {8.2, 8.95, 9.8, 10.6, 11.5, 12.55, 13.45, 14.25};
		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		float move = 180;
		for (int i = 0; i < 8; i++)
		{
			auto bullet = mBursts.GetNext();
			if (i % 2 == 0)
				bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
			else
				bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
			bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
		}
		
	}
	
	void TutorialManager::Stage3()
	{
		{
			double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
			double beat[] = { 15.128, 15.878, 16.728, 17.528, 18.428, 19.478, 20.378, 21.178 };
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			float move = 180;
			for (int i = 0; i < 9; i++)
			{
				auto bullet = mBursts.GetNext();
				if (i % 2 == 0)
					bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
				else
					bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
				bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
			}
		}
		{
			//double warning[] = { 0.676, 0.76, 1.3, 1.177, 0.908, 0.736, 0.932, 0.981, 0.908, 0.908 };
			double beat[] =	{ 14.850, 15.500, 16.583, 17.235, 17.450, 18.313, 18.959, 20.242, 20.697, 21.025 };
			const float y = application.GetHeight() * 0.5;
			const float x[] = { -60, - 20, 20, 60, 100, 140, 180, 220, 260, 300	};

			for(int i =0; i < 10; i++)
			{
				auto bullet = mBeams.GetNext();
				bullet->mTransform->SetPosition({ x[i], y, 0 });
				bullet->SetTimeline(mMusic, 1.3, beat[i], 0.35);
			}
		}
	}
	void TutorialManager::Stage4()
	{
		{
			double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
			double beat[] = { 28.984, 29.734, 30.584, 31.384, 32.284, 33.334, 34.234, 35.034 };
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			float move = 180;
			for (int i = 0; i < 9; i++)
			{
				auto bullet = mBursts.GetNext();
				if (i % 2 == 0)
					bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
				else
					bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
				bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
			}
		}
		{
			double beat[] ={ 28.701, 29.350, 30.219, 30.868, 31.949, 32.598, 33.677, 34.326};
			float y = application.GetHeight() * 0.5;
			float x[] = { 200, -200, 100, -100 };
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					auto bullet = mBeams.GetNext();
					if(i % 2 == 0)
						bullet->mTransform->SetPosition({ x[j], y, 0 });
					else
						bullet->mTransform->SetPosition({ x[2 + j], y, 0 });
					bullet->SetTimeline(mMusic, 1.3, beat[i], 0.35);
				}
			}
		}
	}
	void TutorialManager::Stage5()
	{
		{
			double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
			double beat[] = {35.912, 36.662, 37.512, 38.312, 39.212, 40.262, 41.162, 41.962};
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			float move = 180;
			for (int i = 0; i < 9; i++)
			{
				auto bullet = mBursts.GetNext();
				if (i % 2 == 0)
					bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
				else
					bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
				bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
			}
		}
		{
			double beat[] ={ 35.403, 36.052, 36.921, 37.57,	38.651,	39.3, 40.379, 41.028 };

			float y = application.GetHeight() * 0.5;
			float x[][3] = { {-300, 0, 300}, {-150, 150, 0}};
			
			for(int i =0; i < 8; i++)
			{
				int num = i % 2 == 0 ? 3 : 2;
				for (int j = 0; j < num; j++)
				{
					auto bullet = mBeams.GetNext();
					bullet->mTransform->SetPosition({ x[i % 2][j], y, 0 });
					bullet->SetTimeline(mMusic, 1.3, beat[i], 0.35);
				}
			}
		}
		{
			double show[] = { 35.629, 38.221 };
			double beat[8] = {36.493, 36.601, 36.709, 36.817, 39.949, 40.057, 40.165, 40.273,};
			Vector3 pos[] = { {-230, 150, 1}, {230, 150, 1}, {-230, -150, 1}, {230, -150, 1} };
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int idx = i * 4 + j;
					auto c = mBeatCircles.GetNext();
					c->mTransform->SetPosition(pos[j]);
					c->FastAnim(true);
					c->SetTimeline(mMusic, beat[idx]- show[i], beat[idx], 0);
				}
			}
		}
	}
	void TutorialManager::Stage6()
	{
		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
		double beat[] = { 42.84, 43.59, 44.44, 45.24, 46.14, 47.19, 48.09, 48.89 };
		float move = 180;
		for (int i = 0; i < 9; i++)
		{
			auto bullet = mBursts.GetNext();
			if (i % 2 == 0)
				bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
			else
				bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
			bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				Vector3 pos = { 200.f * (i ? -1 : 1), bounds.top + 40.f * j, 0 };
				auto bullet = mRoundSpikes.GetNext();
				bullet->Setup(0, pos, pos);
				bullet->SetTimeline(mMusic, 0, beat[0], 0);
			}
		}
	}
	//void TutorialManager::Stage7(double time)
	//{
	//	const double beat[] = {
	//		56.187, 56.624, 59.651 , 60.088
	//	};
	//	static int idx = 0;
	//	if (idx >= 4 && beat[0] >= time)
	//		idx = 0;
	//	if(idx < 4 && beat[idx] <= time)
	//	{
	//		RECT bounds = SceneManager::MainCamera()->GetBoundary();
	//		auto b = mBeatBars.GetNext();
	//		b->mTransform->SetPosition({ (float)bounds.right, application.GetHeight() * 0.5f,0}); //({(float)bounds.right, 0, 0 });
	//		b->Activate();
	//		if (idx % 2)
	//		{
	//			RECT bounds = SceneManager::MainCamera()->GetBoundary();
	//			float x = bounds.right + 42 * 0.5;
	//			float endX = bounds.left - 42 * 0.5;
	//			Vector3 pos = { x, 0, 1 };
	//			Vector3 endPos = { endX, 0, 1 };
	//			auto c = mFullBar.GetNext();
	//			c->Setup(7, pos, endPos);
	//			c->Activate();
	//		}
	//		idx++;
	//	}
	//}
	//void TutorialManager::Stage8(double time)
	//{
	//	const double beat[] = {
	//		   70.043 , 70.480, 73.507 , 73.944
	//	};
	//	const double semibeat[2][7] =
	//	{
	//		{71.798, 71.959, 72.12,	72.28,	72.441,	72.601,	72.762},
	//		{75.262, 75.423, 75.583, 75.744, 75.905, 76.065, 76.226 }
	//	};
	//	static int idx = 0;
	//	if (idx >= 4 && beat[0] >= time)
	//		idx = 0;
	//	if (idx < 4 && beat[idx] <= time)
	//	{
	//		RECT bounds = SceneManager::MainCamera()->GetBoundary();
	//		auto b = mBeatBars.GetNext();
	//		b->mTransform->SetPosition({ (float)bounds.right, application.GetHeight() * 0.5f,0 });
	//		b->Activate();
	//		if (idx % 2)
	//		{
	//			float x = bounds.right + 42 * 0.5;
	//			float endX = bounds.left - 42 * 0.5;
	//			Vector3 pos = { x, 0, 1 };
	//			Vector3 endPos = { endX, 0, 1 };
	//			auto c = mFullBar.GetNext();
	//			c->Setup(7, pos, endPos);
	//			c->Activate();
	//		}
	//		if (idx % 2 == 0)
	//		{
	//			float dist = 100;
	//			Vector3 pos[] = { {0, bounds.top + dist, 0 }, { 0, bounds.bottom - dist, 0 } };
	//			for (int i = 0; i < 2; i++)
	//			{
	//				auto c = mCircleLines.GetNext();
	//				c->FitToWidth();
	//				c->mTransform->SetPosition(pos[i]);
	//				c->Show(beat[idx] + 0.848);
	//			}
	//		}
	//		else
	//		{
	//			float dist = 100;
	//			Vector3 pos[] = { {0, bounds.top + dist, 0 }, { 0, bounds.bottom - dist, 0 } };
	//			for (int i = 0; i < 2; i++)
	//			{
	//				auto c = mCircleLines.GetNext();
	//				c->FitToWidth();
	//				c->mTransform->SetPosition(pos[i]);
	//				int j = idx == 1 ? 0 : 1;
	//				c->MultipleShow(semibeat[j]);
	//			}
	//		}
	//		idx++;
	//	}


	//	

	//}
	//void TutorialManager::Stage9(double time)
	//{
	//	const double beat[3] = { 111.611, 123.718, 125.035 };
	//	const Vector3 pos[6] = { {-640, 360, 0}, {640, 360, 0}, {-640, -360, 0}, {640, -360, 0}, {0, -500, 0},{0, 500, 0} };

	//	static int idx = 0;
	//	if (idx < 3 && time >= beat[idx])
	//	{
	//		if (idx == 0)
	//		{
	//			for (int i = 0; i < 6; i++)
	//			{
	//				auto c = mCircles.GetNext();
	//				c->mTransform->SetPosition(pos[i]);
	//				c->Show(0);
	//			}
	//		}
	//		else if (idx == 1)
	//		{
	//			for (int i = 0; i < 6; i++)
	//			{
	//				auto c = mCircles.GetNext();
	//				c->ActivateWithTime(lu::math::RealRandom<double>(0, 0.432));
	//			}
	//		}
	//		else if (idx == 2)
	//		{
	//			for (int i = 0; i < 6; i++)
	//			{
	//				auto c = mCircles.GetNext();
	//				c->DeActivate();
	//			}
	//		}
	//		idx++;
	//	}
	//	else if (idx > 2 && time < beat[2])
	//		idx = 0;
	//}
	//void TutorialManager::Stage10(double time)
	//{
	//	static double readTime = 125.467;
	//	static int beat = 0;
	//	if (readTime < 152.683 && time >= readTime)
	//	{
	//		{
	//			static int showNum = 0;
	//			for (showNum; showNum < 4; showNum++)
	//			{
	//				auto b = mBeatBars.GetNext();
	//				double showTime = readTime + showNum * 0.432;
	//				if (showTime <= 152.683)
	//				{
	//					b->SetRandomPosition();
	//					b->Show(showTime);
	//				}
	//			}
	//			showNum--;
	//		}
	//		if(beat % 2 ==0)
	//		{
	//			static int idx = 0;
	//			auto bullet = mBurstBullets.GetNext();
	//			bullet->IsEven(idx % 2 == 0);
	//			bullet->Activate();
	//			idx++;
	//		}
	//		{
	//			const int beats[] = { 5, 13, 21, 29, 36, 41, 49, 57 };
	//			static int idx = 0;
	//			//5 8 8 8 8 7 7 7 

	//			if ((beat + 3 ) == beats[idx])
	//			{
	//				auto c = mCircleLines.GetNext();
	//				c->FitToHeight();
	//				double time[7];
	//				double step = 0.432 * 1 / 7;
	//				for (int i = 0; i < 7; i++)
	//				{
	//					time[i] = readTime + 0.432 * 2 + step * i;
	//				}
	//				c->MultipleShow(time);
	//				idx++;
	//			}
	//		}  
	//		{
	//			const int beats[] = { 10, 17, 26, 33, 40, 48, 56 };
	//			static int idx = 0;
	//			if (beat == beats[idx])
	//			{
	//				auto r = SceneManager::MainCamera()->GetBoundary();
	//				Vector3 pos[2] = { {r.right - 20.f, -462, 1}, {r.right - 20.f, 501,1} };
	//				auto c = mFullBar.GetNext();
	//				c->Setup(7, pos[idx%2], { r.left + 40.f, pos[idx % 2].y, 1 });
	//				c->Activate();
	//				idx++;
	//			}
	//		}
	//		readTime += 0.432;
	//		beat++;
	//	}
	//	if (beat == 64)
	//	{
	//		auto r = SceneManager::MainCamera()->GetBoundary();
	//		auto c = mFullBar.GetNext();
	//		c->Setup(9 , { r.right - 20.f, 0, 0 }, { r.left - 40.f, 0, 0 });
	//		c->Activate();
	//		readTime += 0.432;
	//		beat++;
	//	}
	//}
}
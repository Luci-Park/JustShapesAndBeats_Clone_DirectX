#include "DubwooferManager.h"
#include "DubwooferDropSpawner.h"
#include "DubwooferSpikeDropper.h"
#include "DubwooferBeamBullet.h"
#include "TutorialBeam.h"
#include "CheckPoint.h"
#include "MusicController.h"
#include "LObject.h"
#include "LApplication.h"
#include "LCamera.h"

extern lu::Application application;
namespace lu::JSAB
{
	DubwooferManager::DubwooferManager()
		: mThickBeams(4)
		, mThinBeams(200)
	{
	}
	void DubwooferManager::Initialize()
	{
		mDrops = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<DubwooferDropSpawner>();
		mSpikes = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<DubwooferSpikeDropper>();
		mMusic = Owner()->GetComponent<MusicController>();
		mCheckPoint = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<CheckPoint>();
		mCheckPoint->SetBackground(SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground());
	}
	void DubwooferManager::Update()
	{
		double time = mMusic->GetTime();
		Drops(time);
		Spikes(time);
		BigBar(time);
		SmallBar(time);
		CheckPoints(time);
	}
	void DubwooferManager::Drops(double time)
	{
		static double beat[] = { 1, 1.25, 1.65, 2.75, 3, 3.4, 4.4, 4.65, 5.05, 6, 6.25, 6.55, 6.675, 6.8, 6.9, 7.05, 7.2, 7.7
			, 7.95, 8.35, 9.45, 9.7, 10.1, 11.1, 11.35, 11.75, 12.7, 12.95, 13.5, 13.65, 13.75, 13.8, 13.85, 13.95, 14
			, 14.15, 14.3,14.65, 14.8, 15.05, 15.35, 15.6, 15.9, 16.15, 16.45, 16.8, 17, 17.15, 17.25, 17.55, 17.85, 18.1
			, 18.5, 18.8, 18.9, 19.25, 19.5, 19.75, 20.05, 20.45, 20.55, 21, 21.3, 21.4, 21.7, 22, 22.25, 22.55, 22.8
			, 23.1, 23.35, 23.6, 23.75, 23.9, 24.15, 24.45, 24.7, 25.15, 25.4, 25.55, 25.85, 26.1, 26.4, 26.7, 27.05, 27.2
			, 89.2, 89.45, 89.75, 90, 90.3, 90.65, 90.85, 91, 91.1, 91.4, 91.7, 91.95, 92.35, 92.65, 92.75, 93.1, 93.35, 93.6, 93.9, 94.3
			, 94.4, 94.85, 95.15, 95.25, 95.55, 95.85, 96.1, 96.4, 96.65, 96.95, 97.2, 97.45, 97.6, 97.75, 98, 98.3, 98.55, 99
			, 99.25, 99.4, 99.7, 99.95, 100.25
		};
		static int idx = 0;
		while (idx < 129 && time >= beat[idx])
		{
			mDrops->Activate();
			idx++;
		}
	}
	void DubwooferManager::Spikes(double time)
	{
		static float appear[2][3] = { {9.533, 27.250, 27.114}, {.679, 126.550, 33.616} };
		static int appearIdx = 0;
		if (appearIdx < 2 && time > appear[appearIdx][1] - appear[appearIdx][0] - 1)
		{
			mSpikes->SetTimeline(mMusic, appear[appearIdx][0], appear[appearIdx][1], appear[appearIdx][2]);
			appearIdx++;
		}

		static float beat[] = { 27.15, 28.797, 30.443, 32.09, 33.737, 35.383, 37.03, 38.677, 40.323, 41.97
			, 43.617, 45.263, 46.91, 48.557, 50.203, 51.85, 128.35, 130, 131.6, 133.25, 134.9, 136.5
			, 138.15, 139.8, 141.4, 143.05, 144.7, 146.35, 147.95, 149.6, 151.25, 152.85
		};
		static int beatIdx = 0;
		if (beatIdx < 32 && time > beat[beatIdx])
		{
			mSpikes->DropSpike();
			beatIdx++;
		}
	}
	void DubwooferManager::BigBar(double time)
	{
		static int flag = 0;

		//109 ~ 111
		if (flag == 0)
		{
			if (time >= 60.2 - 2.013 - 0.5)
			{
				float beat[][3] = { {2.013, 60.2, 0.5},{2.119, 61.85, 0.5}, {2.119, 63.5, 0.5} };
				float x[] = { 0, 330, -330 };
				for (int i = 0; i < 3; i++)
				{
					auto bar = mThickBeams.GetNext();
					Vector3 pos = bar->mTransform->GetPosition();
					pos.x = x[i];
					bar->mTransform->SetPosition(pos);
					bar->SetTimeline(mMusic, beat[i][0], beat[i][1], beat[i][2]);
				}
				flag++;
			}
		}
		//125, 130, 131, 148
		else if (flag == 1)
		{
			float beat[][3] = { {2.119, 66.95, 0.5},{2.119, 68.55, 0.5}, {2.119, 70.25, 0.5}, {2.119, 74.4, 0.5} };
			float x[] = { -450, 330, 0, 0 };
			if (time >= beat[0][1] - beat[0][0] - 0.5)
			{				
				for (int i = 0; i < 4; i++)
				{
					auto bar = mThickBeams.GetNext();
					Vector3 pos = bar->mTransform->GetPosition();
					pos.x = x[i];
					bar->mTransform->SetPosition(pos);
					bar->SetTimeline(mMusic, beat[i][0], beat[i][1], beat[i][2]);
				}
				flag++;
			}
		}
		//184
		else if (flag == 2)
		{
			if (time >= 80)
			{
				float y = application.GetHeight() * 0.5;
				float x = 0;
				auto bar = mThickBeams.GetNext();
				Vector3 pos = { x, y, 0 };
				bar->mTransform->SetPosition(pos);
				bar->SetTimeline(mMusic, 2.119, 86.9, 0.5);
				flag++;
			}
		}
		//220
		else if (flag == 3)
		{
			if (time >= 95)
			{
				float y = application.GetHeight() * 0.5;
				float x = 0;
				auto bar = mThickBeams.GetNext();
				Vector3 pos = { x, y, 0 };
				bar->mTransform->SetPosition(pos);
				bar->SetTimeline(mMusic, 2.119, 100.1, 1);
				flag++;
			}
		}
		//363, 393, 394
		else if (flag == 4)
		{
			if (time >= 102)
			{
				float beat[][3] = { {2.000, 105.1, 1},{2, 107.5, 1}, {2, 107.5, 1}, {2, 114.2, 1} };
				float y = application.GetHeight() * 0.5;
				float x[] = { 0, 500, -500, 0 };
				for (int i = 0; i < 4; i++)
				{
					auto bar = mThickBeams.GetNext();
					Vector3 pos = bar->mTransform->GetPosition();
					pos.x = x[i];
					bar->mTransform->SetPosition(pos);
					bar->SetTimeline(mMusic, beat[i][0], beat[i][1], beat[i][2]);
				}
				flag++;
			}
		}
		else if (flag == 5)
		{
			if (time >= 115)
			{
				float beat[][3] = { {2.000, 117.4, 1},{2, 117.4, 1} };
				float y = application.GetHeight() * 0.5;
				float x[] = { 500, -500};
				for (int i = 0; i < 2; i++)
				{
					auto bar = mThickBeams.GetNext();
					Vector3 pos = bar->mTransform->GetPosition();
					pos.x = x[i];
					bar->mTransform->SetPosition(pos);
					bar->SetTimeline(mMusic, beat[i][0], beat[i][1], beat[i][2]);
				}
				flag++;
			}
		}
		else if (flag == 6)
		{
			if (time >= 118)
			{
				float beat[] = { 120.7, 122.55, 124.1 };
				float x = application.GetWidth() * -0.5 + 100;
				for (int i = 0; i < 3; i++, x+= 300)
				{
					auto bar = mThickBeams.GetNext();
					Vector3 pos = bar->mTransform->GetPosition();
					pos.x = x;
					bar->mTransform->SetPosition(pos);
					bar->SetTimeline(mMusic, 2, beat[i], 1);
				}
				x = application.GetWidth() * 0.5;
				float y = 60 - 5 - 80 * 0.5;
				auto bar = mThickBeams.GetNext();
				Vector3 pos = { x, y, 0 };
				bar->mTransform->SetPosition(pos);
				bar->mTransform->SetRotation(Quaternion::Create2DRotationRadian(PI * -0.5));
				bar->SetTimeline(mMusic, 1.5, 126.55, 0.5);
				bar->SetSize(80);
				flag++;
			}
		}
	}
	void DubwooferManager::SmallBar(double time)
	{
		static int flag = 0;
		//112 ~ 128
		if (flag == 0) 
		{
			if (time >= 65.031 - 2)
			{
				float beat = 65.031;
				float y = application.GetHeight() * 0.5;
				float x = 300;
				for (int i = 0; i < 16; i++, beat += 0.1, x -= 40)
				{
					auto bar = mThinBeams.GetNext();
					Vector3 pos = { x, y, 0 };
					bar->mTransform->SetPosition(pos);
					bar->mTransform->SetRotation(Quaternion::Identity);
					bar->SetTimeline(mMusic, 1.5, beat, 0.5);
				}
				flag++;
			}
		}
		//131 ~ 147
		else if (flag == 1)
		{
			float beat = 71.78;
			float y = application.GetHeight() * 0.5;
			float x = 0;
			float diff = -70;
			if (time >= beat - 2)
			{
				for (int i = 0; i < 17; i++, beat += 0.1)
				{
					auto bar = mThinBeams.GetNext();
					Vector3 pos = { x, y, 0 };
					bar->mTransform->SetPosition(pos);
					bar->mTransform->SetRotation(Quaternion::Identity);
					bar->SetTimeline(mMusic, 1.5, beat, 0.5);
					if (i % 2)
						x *= -1;
					else
						x = x * -1 + diff;

				}
				flag++;
			}
		}
		//149 ~ 158
		else if (flag == 2)
		{
			float beat[2] = { 75.946, 76.446 };
			float y = application.GetHeight() * 0.5;
			float step = application.GetWidth() / 10;
			float x = application.GetWidth() * -0.5 + step;
			if (time >= beat[0] - 2)
			{
				for (int i = 0; i < 10; i++, x += step)
				{
					auto bar = mThinBeams.GetNext();
					Vector3 pos = { x, y, 0 };
					bar->mTransform->SetPosition(pos);
					bar->mTransform->SetRotation(Quaternion::Identity);
					bar->SetTimeline(mMusic, 1.5, beat[i%2], 0.5);
					beat[i % 2] += 0.01;					
				}
				flag++;
			}
		}
		//159 ~ 164
		else if (flag == 3)
		{
			float beat[5] = { 77.8, 77.95, 78.2, 78.5, 78.5 };
			if (time >= beat[0] - 3)
			{
				float outro[5] = { 1.191, 1.032, 0.755, 0.477, 0.516 };
				float rot[5] = { 0.5, -0.5, 0.5, -0.5, -0.5 };
				float ystep = 90;
				float y = application.GetHeight() * 0.5 - ystep;
				for (int i = 0; i < 5; i++, y -= ystep)
				{
					auto bar = mThinBeams.GetNext();
					Vector3 pos = { application.GetWidth() * rot[i] * -1, y, 0};
					bar->mTransform->SetPosition(pos);
					bar->mTransform->SetRotation(Quaternion::Create2DRotationRadian(PI * rot[i]));
					bar->SetTimeline(mMusic, 2, beat[i], outro[i]);
				}
				flag++;
			}
		}
		//166 ~ 183
		else if (flag == 4)
		{
			float beat[2] = { 80.996,83.396 };
			if (time >= beat[0] - 2)
			{
				float x[2] = { application.GetWidth() * 0.5 - 30, application.GetWidth() * -0.5 + 30 };
				float sign[2] = { -1, 1 };
				float y = application.GetHeight() * 0.5;
				for (int i = 0; i < 18; i++)
				{
					auto bar = mThinBeams.GetNext();
					Vector3 pos = { x[i%2], y, 0};
					bar->mTransform->SetPosition(pos);
					bar->mTransform->SetRotation(Quaternion::Identity);
					bar->SetTimeline(mMusic, 2, beat[i%2], 0.5);
					beat[i % 2] += 0.29;
					x[i % 2] += 40 * sign[i % 2];
					bar->SetShake(false);
				}
				flag++;
			}
		}
		//230 ~ 313
		else if (flag == 5 && time >= 100)
		{
			{
				float y = application.GetHeight() * 0.5;
				float beat = 102.35;
				float x = 105;
				for (int i = 0; i < 21; i++, beat += 0.04, x += 40)
				{
					for (int j = 0; j < 2; j++)
					{
						auto bar = mThinBeams.GetNext();
						Vector3 pos = { x * (j % 2 ? 1 : -1), y, 0 };
						bar->mTransform->SetPosition(pos);
						bar->mTransform->SetRotation(Quaternion::Identity);
						bar->SetTimeline(mMusic, 1.5, beat, 0.5);
						bar->SetSize(10);
						bar->SetShake(false);
					}
				}
			}
			{
				float y = application.GetHeight() * 0.5;
				float beat = 102.75;
				float x = 125;
				for (int i = 0; i < 21; i++, beat += 0.04, x += 40)
				{
					for (int j = 0; j < 2; j++)
					{
						auto bar = mThinBeams.GetNext();
						Vector3 pos = { x * (j % 2 ? 1 : -1), y, 0 };
						bar->mTransform->SetPosition(pos);
						bar->mTransform->SetRotation(Quaternion::Identity);
						bar->SetTimeline(mMusic, 1.5, beat, 0.5);
						bar->SetSize(10);
						bar->SetShake(false);
					}
				}
			}
			flag++;
		}
		else if (flag == 6 && time >= 102)
		{
			{
				float y = application.GetHeight() * 0.5;
				float beat = 104.12;
				float x = -200;
				for (int i = 0; i < 21; i++, beat += 0.02, x -= 25)
				{
					for (int j = 0; j < 2; j++)
					{
						auto bar = mThinBeams.GetNext();
						Vector3 pos = { x , y, 0 };
						bar->mTransform->SetPosition(pos);
						bar->mTransform->SetRotation(Quaternion::Identity);
						bar->SetTimeline(mMusic, 1.5, beat, 0.5);
						bar->SetSize(10);
						bar->SetShake(false);
					}
				}
			}
			{
				float y = application.GetHeight() * 0.5;
				float beat = 104.48;
				float x = 200;
				for (int i = 0; i < 21; i++, beat += 0.02, x += 25)
				{
					for (int j = 0; j < 2; j++)
					{
						auto bar = mThinBeams.GetNext();
						Vector3 pos = { x , y, 0 };
						bar->mTransform->SetPosition(pos);
						bar->mTransform->SetRotation(Quaternion::Identity);
						bar->SetTimeline(mMusic, 1.5, beat, 0.5);
						bar->SetSize(10);
						bar->SetShake(false);
					}
				}
			}
			flag++;
		}
		else if (flag == 7 && time >= 110)
		{
			{
				float y = application.GetHeight() * 0.5;
				float beat = 111.35;
				float x = application.GetWidth() * -0.5;
				for (int i = 0; i < 22; i++, beat += 0.02, x += 25)
				{
					for (int j = 0; j < 2; j++)
					{
						auto bar = mThinBeams.GetNext();
						Vector3 pos = { x , y, 0 };
						bar->mTransform->SetPosition(pos);
						bar->mTransform->SetRotation(Quaternion::Identity);
						bar->SetTimeline(mMusic, 1.5, beat, 0.5);
						bar->SetSize(10);
						bar->SetShake(false);
					}
				}
			}
			{
				float y = application.GetHeight() * 0.5;
				float beat = 111.85;
				float x = application.GetWidth() * 0.5;
				for (int i = 0; i < 22; i++, beat += 0.02, x -= 25)
				{
					for (int j = 0; j < 2; j++)
					{
						auto bar = mThinBeams.GetNext();
						Vector3 pos = { x , y, 0 };
						bar->mTransform->SetPosition(pos);
						bar->mTransform->SetRotation(Quaternion::Identity);
						bar->SetTimeline(mMusic, 1.5, beat, 0.5);
						bar->SetSize(10);
						bar->SetShake(false);
					}
				}
			}
			flag++;
		}
		else if (flag == 8 && time >= 112)
		{
			float y = application.GetHeight() * 0.5;
			float outro[] = { 1.793, 1.5, 1.345, 1.093 };
			float beat[] = { 114, 113.75, 113.6, 113.35 };
			float x[] = { -450, 450, -300, 300 };
			for (int i = 0; i < 4; i++)
			{
				auto bar = mThinBeams.GetNext();
				Vector3 pos = { x[i] , y, 0 };
				bar->mTransform->SetPosition(pos);
				bar->mTransform->SetRotation(Quaternion::Identity);
				bar->SetTimeline(mMusic, outro[i], beat[i], 0.5);
				bar->SetSize(20);
				bar->SetShake(true);
			}
			flag++;
		}
		//450 ~ 461
		else if (flag == 9 && time >= 120)
		{
			float rot[2] = { 0.5, -0.5};
			float x = application.GetWidth();
			float y = application.GetHeight() * 0.5;
			float beat = 124.75;
			for (int i = 0; i < 12; i++, y -= 25, beat += 0.15)
			{
				auto bar = mThinBeams.GetNext();
				Vector3 pos = { x * rot[i % 2] * -1 , y, 0};
				bar->mTransform->SetPosition(pos);
				bar->mTransform->SetRotation(Quaternion::Create2DRotationRadian(PI* rot[i % 2]));
				bar->SetTimeline(mMusic, 2, beat, 0.35);
				bar->SetSize(20);
				bar->SetShake(true);
			}
			flag++;
		}
		//462 ~
		else if (flag == 10)
		{
			static float beat[] = { 126.55, 126.75, 127.2, 127.3, 127.75, 128.05, 128.15, 128.45, 128.65, 129, 129.25
				, 129.55, 129.8, 130.1, 130.35, 130.5, 130.65, 130.95, 131.2, 131.45, 132.15, 132.3, 132.6, 132.85, 133.05
				, 133.4, 133.75, 133.9, 134.35, 134.6, 134.75, 135, 135.35, 135.55, 135.85, 136.15, 136.4, 136.75, 136.95
				, 137.15, 137.25, 137.55, 137.8, 138.1, 138.5, 138.8, 138.9, 139.2, 139.5, 139.75, 140.05, 140.3, 140.55, 140.85
				, 141.1, 142.75, 142.9, 143.05, 143.2, 143.35, 143.5, 143.65, 143.8, 143.95, 144.1, 144.25, 144.4, 144.55, 144.7
				, 144.85, 145, 145.15, 145.3, 145.45, 145.6, 146.35, 146.6, 146.95, 147.2, 147.5, 147.75, 148, 148.3, 148.4
				, 148.75, 148.85, 149.15, 149.25, 149.4, 149.55, 149.7, 149.85, 150, 150.15, 150.3, 150.45, 150.6, 150.75, 150.75
				, 150.9, 150.9, 151.05, 151.2, 151.35, 151.5, 151.65, 151.8, 151.95, 152.1, 152.25, 152.4
			};
			static int idx = 0;
			static float prevx = 0;
			static float y = application.GetHeight() * 0.5;

			while (idx < 111 && time >= beat[idx] - 2)
			{
				auto bar = mThinBeams.GetNext();
				bar->SetSize(10);
				bar->SetShake(false);
				bar->mTransform->SetRotation(Quaternion::Identity);
				float x;
				if (54 <= idx && idx < 64)
					x = application.GetWidth() * 0.5 - 50 * (idx - 54);
				else if(64 <= idx && idx < 74)
					x = application.GetWidth() * -0.5 + 50 * (idx - 64);
				else if (91 <= idx && idx < 101)
					x = application.GetWidth() * 0.5 - 50 * (idx - 91);
				else if (101 <= idx && idx < 111)
					x = application.GetWidth() * -0.5 + 50 * (idx - 101);
				else
				{
					do
					{
						x = IntRandom(application.GetWidth() * -0.5 + 20, application.GetWidth() * 0.5 - 20);
					} while (abs(x - prevx) < 20);
				}
				Vector3 pos(x, y, 0);
				bar->mTransform->SetPosition(pos);
				bar->SetTimeline(mMusic, 1.5, beat[idx], 0.5);
				prevx = x;
				idx++;
			}

		}
	}
	void DubwooferManager::CheckPoints(double time)
	{
		static double beat[] = { 27.75, 54.25, 92.4, 131.15, 159.95 };
		static BackgroundScript::eBackgrounds types[] = {
			BackgroundScript::eBackgrounds::PINK,
			BackgroundScript::eBackgrounds::PURPLE,
			BackgroundScript::eBackgrounds::BLACK,
			BackgroundScript::eBackgrounds::DARKBLUE,
			BackgroundScript::eBackgrounds::BLACK
		};
		static int idx = 0;
		if (time >= beat[idx] - 5.5)
		{
			mCheckPoint->Owner()->SetActive(true);
			mCheckPoint->SetTimeline(mMusic, 5, beat[idx], 0);
			mCheckPoint->SetBackgroundType(types[idx]);
			if (idx == 4)
				mCheckPoint->SetIsFinal(true);
			idx++;
		}
	}
}
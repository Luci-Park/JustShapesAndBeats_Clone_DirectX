#pragma once
#include "..\Engine_SOURCE\LScene.h"
#include "CameraScript.h"
namespace lu::JSAB
{
	class ParticleTestScene : public Scene
	{
	public:
		ParticleTestScene();
		virtual ~ParticleTestScene();

		virtual void Initialize() override;

	};

	class CameraTestScene : public Scene
	{
	public:
		CameraTestScene(){}
		~CameraTestScene(){}
		virtual void Initialize() override;
		virtual void Update() override;

		GameCamera* script;
	};

	class TriangleTestScene : public Scene
	{
	public:
		TriangleTestScene(){}
		~TriangleTestScene() {};
		virtual void Initialize()override;
		virtual void Update() override;
	};
	class BulletTestScene : public Scene
	{
	public:
		BulletTestScene(){}
		~BulletTestScene() {};
		virtual void Initialize() override;
		virtual void Update() override;
	};
}

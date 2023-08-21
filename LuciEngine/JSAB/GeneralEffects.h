#pragma once
#include "LMaterial.h"
#include "LResources.h"
#include "LAnimation.h"
namespace lu::JSAB
{
	std::shared_ptr<Material> GetGeneralMaterial(const std::wstring key)
	{
		auto mat = Resources::Find<Material>(key);
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			auto t = Resources::Find<Texture>(key);
			assert(t != nullptr);
			mat->SetTexture(t);
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(key, mat);
			mat->SetKey(key);
		}
		return mat;
	}

	void CreateClockwiseAnimation(float duration, Animation* ani)
	{
		ani->AddRotationKey(0, Quaternion::Identity);
		ani->AddRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5));
		ani->AddRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
		ani->AddRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 1.5));
		ani->AddRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * -2));
	}

	void CreateCounterClockwiseAnimation(float duration, Animation* ani)
	{
		ani->AddRotationKey(0, Quaternion::Identity);
		ani->AddRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5));
		ani->AddRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI));
		ani->AddRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 1.5));
		ani->AddRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 2));
	}

	void CreateWhiteBlink(float duration, Animation* ani)
	{
		ani->AddInterpolationKey(0, 0);
		ani->AddInterpolationKey(duration, 1);
	}
}


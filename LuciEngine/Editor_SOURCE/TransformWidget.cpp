#include "TransformWidget.h"
#include "..\\Engine_SOURCE\\LGameObject.h"
#include "..\\Engine_SOURCE\\LInput.h"
#include "..\\Engine_SOURCE\\LTime.h"

namespace gui
{
	TransformWidget::TransformWidget()
		: fMoveSpeed(30.0f)
		, fRotateSpeed(PI/180 * 4)
		, fScaleSpeed(30.0f)
	{
	}
	TransformWidget::~TransformWidget()
	{
	}
	void TransformWidget::Initialize()
	{
		mTransform = GetOwner()->mTransform;
	}
	void TransformWidget::Update()
	{
		lu::math::Vector3 position = mTransform->GetPosition();
		lu::math::Vector3 rotation = mTransform->GetRotation();
		lu::math::Vector3 scale = mTransform->GetScale();
		//wasd = move
		//qe = rotate
		//rf = scale
		if (lu::Input::GetKey(lu::eKeyCode::W))
		{
			position.y += fMoveSpeed * lu::Time::DeltaTime();
		}
		if (lu::Input::GetKey(lu::eKeyCode::A))
		{
			position.x -= fMoveSpeed * lu::Time::DeltaTime();
		}

		if (lu::Input::GetKey(lu::eKeyCode::S))
		{
			position.y -= fMoveSpeed * lu::Time::DeltaTime();
		}

		if (lu::Input::GetKey(lu::eKeyCode::D))
		{
			position.x += fMoveSpeed * lu::Time::DeltaTime();
		}

		if (lu::Input::GetKey(lu::eKeyCode::Q))
		{
			rotation.z += fRotateSpeed * lu::Time::DeltaTime();
		}

		if (lu::Input::GetKey(lu::eKeyCode::E))
		{
			rotation.z -= fRotateSpeed * lu::Time::DeltaTime();
		}

		if (lu::Input::GetKey(lu::eKeyCode::R))
		{
			scale.x -= fScaleSpeed * lu::Time::DeltaTime();
			scale.y -= fScaleSpeed * lu::Time::DeltaTime();
		}

		if (lu::Input::GetKey(lu::eKeyCode::F))
		{
			scale.x += fScaleSpeed * lu::Time::DeltaTime();
			scale.y += fScaleSpeed * lu::Time::DeltaTime();
		}
		mTransform->SetPosition(position);
		mTransform->SetRotation(rotation);
		mTransform->SetScale(scale);
		if (lu::Input::GetKeyDown(lu::eKeyCode::ENTER))
		{
			OutputDebugStringA(std::format("position : {}, {}, {}\n", position.x, position.y, position.z).c_str());
			OutputDebugStringA(std::format("rotation : {}, {}, {}\n", rotation.x, rotation.y, rotation.z).c_str());
			OutputDebugStringA(std::format("scale : {}, {}, {}\n", scale.x, scale.y, scale.z).c_str());
		}
	}
}
#include "TransformWidget.h"
#include "..\\Engine_SOURCE\\LGameObject.h"
#include "..\\Engine_SOURCE\\LInput.h"
#include "..\\Engine_SOURCE\\LTime.h"
#include "..\\Engine_SOURCE\\LTransform.h"

namespace gui
{
	TransformWidget::TransformWidget()
		: fMoveSpeed(100.0f)
		, fRotateSpeed(PI/180 * 10)
		, fScaleSpeed(100.0f)
	{
	}
	TransformWidget::~TransformWidget()
	{
	}
	void TransformWidget::Update()
	{	
		lu::Transform* tr = Owner()->mTransform;
		lu::math::Vector3 position = tr->GetPosition();
		lu::math::Quaternion quaternion = tr->GetRotation();
		lu::math::Vector3 scale = tr->GetScale();
		lu::math::Vector3 rotation = quaternion.ToEuler();

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
		tr->SetPosition(position);
		tr->SetRotation(lu::math::Quaternion::CreateFromYawPitchRoll(rotation));
		tr->SetScale(scale);
		if (lu::Input::GetKeyDown(lu::eKeyCode::ENTER))
		{
			OutputDebugStringA(std::format("position : {}, {}, {}\n", position.x, position.y, position.z).c_str());
			OutputDebugStringA(std::format("rotation : {}, {}, {}\n", rotation.x, rotation.y, rotation.z).c_str());
			OutputDebugStringA(std::format("scale : {}, {}, {}\n", scale.x, scale.y, scale.z).c_str());
		}
	}
}
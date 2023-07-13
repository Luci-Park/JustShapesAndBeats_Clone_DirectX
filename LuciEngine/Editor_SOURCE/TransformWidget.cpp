#include "TransformWidget.h"
#include "..\\Engine_SOURCE\\LGameObject.h"
#include "..\\Engine_SOURCE\\LInput.h"

namespace gui
{
	TransformWidget::TransformWidget()
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
		if (lu::Input::GetKeyDown(lu::eKeyCode::W))
		{
			position.y--;
		}
		if (lu::Input::GetKeyDown(lu::eKeyCode::A))
		{
			position.x--;
		}

		if (lu::Input::GetKeyDown(lu::eKeyCode::S))
		{
			position.y++;
		}

		if (lu::Input::GetKeyDown(lu::eKeyCode::D))
		{
			position.y--;
		}

		if (lu::Input::GetKeyDown(lu::eKeyCode::Q))
		{
			rotation.z -= PI / 180;
		}

		if (lu::Input::GetKeyDown(lu::eKeyCode::E))
		{
			rotation.z += PI / 180;
		}

		if (lu::Input::GetKeyDown(lu::eKeyCode::R))
		{
			scale.x--;
			scale.y--;
		}

		if (lu::Input::GetKeyDown(lu::eKeyCode::F))
		{
			scale.x++;
			scale.y++;
		}
		mTransform->SetPosition(position);
		mTransform->SetRotation(rotation);
		mTransform->SetScale(scale);
		if (lu::Input::GetKeyDown(lu::eKeyCode::ENTER))
		{
		}
	}
}
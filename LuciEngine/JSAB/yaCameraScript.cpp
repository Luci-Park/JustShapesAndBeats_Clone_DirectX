#include "yaCameraScript.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LTime.h"
#include "LInput.h"

namespace lu
{
	void yaCamera::Update()
	{
		Transform* tr = Owner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		float speed = 100.0f;

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += speed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= speed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= speed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += speed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}
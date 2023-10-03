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


		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 50.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 50.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 50.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 50.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}
#include "yaPlayerScript.h"
#include "yaCameraScript.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LTime.h"
#include "LInput.h"

namespace lu
{
	void PlayerScript::Update()
	{
		Transform* tr = Owner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}
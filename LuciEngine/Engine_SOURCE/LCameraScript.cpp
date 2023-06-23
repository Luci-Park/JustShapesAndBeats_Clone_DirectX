#include "LCameraScript.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LTime.h"
#include "LInput.h"

namespace lu
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::W))
		{
			pos.z += 5.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			pos.z -= 5.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}
}

#include "LCameraScript.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LTime.h"

namespace lu
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPos();
		pos.x += 1.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}
}

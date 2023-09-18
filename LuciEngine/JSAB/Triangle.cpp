#include "Triangle.h"
#include "LCollider2D.h"
#include "LGameObject.h"
#include "MusicController.h"
#include "TutorialMusicController.h"
namespace lu::JSAB
{
	void Triangle::OnCollisionEnter(Collider2D* other)
	{
		if (other->Owner()->GetLayer() == eLayerType::Player)
		{
			other->Owner()->mTransform->SetPosition(mTransform->GetPosition());
			{
				auto tuto = dynamic_cast<TutorialMusicController*>(MusicController::Instance);
				if (tuto)
					tuto->PlayNextPart();
			}
		}
	}
}

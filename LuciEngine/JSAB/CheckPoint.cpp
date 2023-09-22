#include "CheckPoint.h"

namespace lu::JSAB
{
	void CheckPoint::BulletSetUp()
	{
		Owner()->SetTag(eTagType::Item);
	}
	void CheckPoint::OnWarning()
	{
	}
	void CheckPoint::WhileWarning(double time)
	{
	}
	void CheckPoint::OnDeActivate()
	{
	}
}
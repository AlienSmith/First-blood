#include "SimpleRotationCopy.h"
#include"UpdateObject.h"
#include"GSTime.h"
void SimpleRotationCopy::Update()
{
	{
		UpdateObject::OUT_Instance->GetTransformComponent()->Rotate(GStar::Vector3(GStar::GSTime::Instance().GetTotalTime() * 100, 0.0f, 0.0f));
	}
}

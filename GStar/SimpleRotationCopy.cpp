#include "SimpleRotationCopy.h"
#include"UpdateRObject.h"
#include"GSTime.h"
void SimpleRotationCopy::Update()
{
	{
		UpdateRObject::OUT_Instance->GetTransformComponent()->Rotate(GStar::Vector3((float)GStar::GSTime::Instance().GetTotalTime() * 100, 0.0f, 0.0f));
	}
}

#include "SimpleRotation.h"
#include "TransformComponent.h"
#include "GSTime.h"
void SimpleRotation::Update()
{
	my_transform->Rotate(GStar::Vector3((float)(GStar::GSTime::Instance().GetdeltaTime())*10.0F, 0.0f, 0.0f));
}

#include "Component.h"
#include "UpdateObject.h"
bool Component::Update()
{
	if (!UpdateObject::OUT_Instance && !UpdateObject::IN_Instance) {
		UpdateObject::Initialize();
	}
	return false;
}

#include "LightManager.h"
namespace GStar {
	LightManager* LightManager::instance = nullptr;
	const float LightManager::AmbientStrength = 0.1f;
	Vector3 GStar::LightManager::GetLight()
	{
		return Vector3(AmbientStrength,AmbientStrength,AmbientStrength);
	}
	void LightManager::Register(Object * lightsource)
	{
		LightList.Push(lightsource);
	}
}

#include "PhysicManager.h"
GStar::PhysicManager* GStar::PhysicManager::instance = nullptr;
const GStar::Vector3* const GStar::PhysicManager::Gravity = new GStar::Vector3(0.0f,9.8f,0.0f);
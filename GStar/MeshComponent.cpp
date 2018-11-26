#include "MeshComponent.h"
#include "MeshManager.h"
bool GStar::MeshComponent::Initialize(const MeshParameters& parameters)
{
	my_mesh = GStar::MeshManager::Instance()->GetMesh(parameters);
	//TODO add some kind of check for result;
	return true;
}

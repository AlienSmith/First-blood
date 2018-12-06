#include "MeshManager.h"
#include "MyString.h"
#include "Scene.h"
#include "Data.h"
//Mesh is like a two unsinged int number would be a waste to use dynamic allocation
GStar::MeshManager* GStar::MeshManager::instance = nullptr;
GStar::Mesh GStar::MeshManager::GetMesh(const MeshParameters& parameters)
{
	unsigned int CurrentID = GStar::MeshManager::MeshGetId(parameters);
	//Start of the checking loop
	MeshSource.Resetcurrent();
	GStar::Mesh current;
	while (MeshSource.HasNext()) {
		current = MeshSource.GetNextNode()->GetData();
		if (CurrentID == current.myId()) {
			return current;
		}
		MeshSource.Move();
	}
	current.SetVAO( LoadMesh(parameters));
	current.SetID ( CurrentID);
	current.SetIndex(parameters.TriangleIndex);
	MeshSource.Push(current);
	return current;
}

unsigned int GStar::MeshManager::LoadMesh(const MeshParameters& parameters)
{
	return Scene::Create()->LoadMesh(parameters);
}


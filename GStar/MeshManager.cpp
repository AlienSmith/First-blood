#include "MeshManager.h"
#include "MyString.h"
#include "Scene.h"
#include "Data.h"
//Mesh is like a two unsinged int number would be a waste to use dynamic allocation
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
	MeshSource.Push(current);
	return current;
}

unsigned int GStar::MeshManager::LoadMesh(const MeshParameters& parameters)
{
	Scene::Create()->LoadMesh(parameters);
	return 0;
}


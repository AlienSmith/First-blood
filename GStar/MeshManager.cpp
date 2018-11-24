#include "MeshManager.h"
#include "MyString.h"
GStar::Mesh GStar::MeshManager::GetMesh(const GStar::MyString resource)
{
	unsigned int CurrentID = GStar::MyString::hash_str(resource.GetString());
	//Start of the checking loop
	MeshSource.Resetcurrent();
	GStar::Mesh current;
	while (MeshSource.GetNextNode())
	{
		current = (MeshSource.GetNextNode())->GetData();
		if (current.myId == CurrentID) {
			return current;
		}
		MeshSource.Move();
	}
	
}

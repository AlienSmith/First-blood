#pragma once
//#include"Manager.h"
#include"SceneInterface.h"
namespace GStar {
	class World;
	class MyString;
	class Vector3;
	class RManager;
	class MeshComponent;
	class ShaderComponent;
	class PhysicComponent;
}
class PongGame : public GStar::SceneInterface {
public:
	PongGame() {
		GStar::SceneInterface::Instance = this;
	}
	virtual ~PongGame() {}
	virtual void Start();
	GStar::PhysicComponent* AddCommonObjects(const GStar::MyString& name, const GStar::Vector3& position, const GStar::Vector3& scale,float weight,float collision_constant,float roughness);
	virtual void Update() {}
	virtual void Terminate() {}
private:
	GStar::World* world;
	GStar::RManager* renderer;
	GStar::MeshComponent* CommonMesh;
	GStar::ShaderComponent* CommonShader;
};
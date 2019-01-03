#pragma once
#include"SceneInterface.h"
#include"World.h"
#include"UpdateObject.h"
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
#include"TransformComponent.h"
#include"InterfaceComponent.h"
#include"Data.h"
#include"SimpleRotation.h"
#include"KeyControlComponent.h"
#include"CameraManager.h"
class SimpleScene : public GStar::SceneInterface {
public:
	SimpleScene():GStar::SceneInterface(),TransformComponent(nullptr),TransformComponent1(nullptr) {
		GStar::SceneInterface::Instance = this;
	}
	virtual ~SimpleScene() {
	}
	virtual void Start() {
		GStar::World& world = GStar::World::Instance();
		Object* tempObject = world.AddObject();
		tempObject->AddComponent(new GStar::MeshComponent(cubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(Shader2TL));
		GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
		tempComponent->Initialize(Default_Texture_BOX);
		tempComponent->Initialize(Default_TextureFace);
		tempObject->AddComponent(tempComponent);
		TransformComponent = new GStar::TransformComponent(tempObject,"RotationCube1");
		world.AddToRoot(TransformComponent);
		TransformComponent->SetTransform(GStar::Vector3(1,2,3),GStar::Base::WORLD);
		TransformComponent->SetScale(GStar::Vector3(1.0f,1.0f,1.0f));
		tempObject->AddComponent(TransformComponent);
		//GStar::InterfaceComponent* component = new SimpleRotation(TransformComponent);
		//tempObject->AddComponent(component);
		
		Object* tempObject1 = world.AddObject();
		tempObject1->AddComponent(new GStar::MeshComponent(cubeparameters));
		tempObject1->AddComponent(new GStar::ShaderComponent(Shader2TL));
		tempComponent = new GStar::TextureComponent();
		tempComponent->Initialize(Default_TextureWall);
		tempComponent->Initialize(Default_TextureFace);
		tempObject1->AddComponent(tempComponent);
		TransformComponent1 = new GStar::TransformComponent(tempObject1,"RotationCube2");
		TransformComponent->AddChildren(TransformComponent1);
		TransformComponent1->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f),GStar::Base::PARENT);
		//TransformComponent1->SetTransform(GStar::Vector3(0.0f, 0.0f, 5.0f), GStar::Base::SELF);
		//TransformComponent1->SetTransform(GStar::Vector3(0.0f, 0.0f, 5.0f), GStar::Base::WORLD);
		tempObject1->AddComponent(TransformComponent1);
		/*tempObject1->AddComponent(new SimpleRotation(TransformComponent1));*/

		/*//Add Light Source
		tempObject = world.AddObject();
		tempObject->AddComponent(new GStar::MeshComponent(NT_cubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(NT_Shaders));
		tempObject->AddComponent(tempComponent);
		TransformComponent2 = new GStar::TransformComponent(tempObject,"Light1");
		world.AddToRoot(TransformComponent2);
		TransformComponent2->SetTransform(cubPosition[4], GStar::Base::WORLD);
		tempObject->AddComponent(TransformComponent2);
		//Add Camera

		tempObject = world.AddObject();
		TransfomrComponent3 = new GStar::TransformComponent(tempObject, "Camera1");
		world.AddToRoot(TransfomrComponent3);
		TransfomrComponent3->SetTransform(GStar::Vector3(0.0f, 0.0f, 0.0f), GStar::Base::WORLD);
		KeyControlCompoenent* controllerComponent = new KeyControlCompoenent(TransfomrComponent3, 2.0f);
		tempObject->AddComponent(controllerComponent);
		GStar::CameraManager::Instance()->SetCurrentCamera(TransfomrComponent3);*/
		
	}
	virtual void Update() {
		/*TransformComponent->SetRotation(GStar::Vector3(Scene::Create()->TotalTime() * 100, 0.0f, 0.0f));
		TransformComponent1->SetRotation(GStar::Vector3(0.0f, Scene::Create()->TotalTime() * 100, 0.0f));*/
	}
	virtual void Terminate() {}
private:
	GStar::TransformComponent* TransformComponent;
	GStar::TransformComponent* TransformComponent1;
	GStar::TransformComponent* TransformComponent2;
	GStar::TransformComponent* TransfomrComponent3;
	KeyControlCompoenent* controllerComponent;
};
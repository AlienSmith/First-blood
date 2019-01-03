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
		TransformComponent->SetTransform(GStar::Vector3(0,0,-5),GStar::Base::WORLD);
		TransformComponent->SetScale(GStar::Vector3(1.0f,1.0f,1.0f));
		TransformComponent->Rotate(60, 0, 0);
		TransformComponent->UpdateTransform();
		tempObject->AddComponent(TransformComponent);
		//KeyControlCompoenent* controller = new KeyControlCompoenent(TransformComponent,2.0f);
		//tempObject->AddComponent(controller);

		GStar::InterfaceComponent* component = new SimpleRotation(TransformComponent);
		tempObject->AddComponent(component);
		tempObject = world.AddObject();

		tempObject->AddComponent(new GStar::MeshComponent(cubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(Shader2TL));
		GStar::TextureComponent* tempC = new GStar::TextureComponent();
		tempC->Initialize(Default_TextureWall);
		tempC->Initialize(Default_TextureFace);
		tempObject->AddComponent(tempC);
		TransformComponent1 = new GStar::TransformComponent(tempObject, "RotationCube2");
		TransformComponent->AddChildren(TransformComponent1);
		TransformComponent1->SetTransform(GStar::Vector3(0, 0, 1), GStar::Base::WORLD);
		tempObject->AddComponent(TransformComponent1);
		TransformComponent1->UpdateTransform();
		//GStar::InterfaceComponent* component1 = new SimpleRotation(TransformComponent1);
		//tempObject->AddComponent(component1);

		Object* tempObject1 = world.AddObject();
		TransformComponent2 = new GStar::TransformComponent(tempObject1,"Camera1");
		world.AddToRoot(TransformComponent2);
		TransformComponent2->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f),GStar::Base::WORLD);
		tempObject1->AddComponent(TransformComponent2);
		TransformComponent2->UpdateTransform();
		controllerComponent = new KeyControlCompoenent(TransformComponent2, 2.0f);
		tempObject1->AddComponent(controllerComponent);
		GStar::CameraManager::Instance()->SetCurrentCamera(TransformComponent2);

		tempObject = world.AddObject();
		tempObject->AddComponent(new GStar::MeshComponent(NT_cubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(NT_Shaders));
		tempObject->AddComponent(tempComponent);
		TransfomrComponent3 = new GStar::TransformComponent(tempObject, "Light1");
		world.AddToRoot(TransfomrComponent3);
		TransfomrComponent3->SetTransform(cubPosition[4], GStar::Base::WORLD);
		tempObject->AddComponent(TransfomrComponent3);
		TransfomrComponent3->UpdateTransform();

		/*GStar::InterfaceComponent* component1 = new SimpleRotation(TransformComponent1);
		tempObject1->AddComponent(component1);*/
		/*
		//Add Light Source
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
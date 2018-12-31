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
		TransformComponent = new GStar::TransformComponent(tempObject);
		world.AddToRoot(TransformComponent);
		TransformComponent->SetTransform(cubPosition[1],GStar::Base::WORLD);
		tempObject->AddComponent(TransformComponent);
		GStar::InterfaceComponent* component = new SimpleRotation();
		tempObject->AddComponent(component);

		Object* tempObject1 = world.AddObject();
		tempObject1->AddComponent(new GStar::MeshComponent(cubeparameters));
		tempObject1->AddComponent(new GStar::ShaderComponent(Shader2TL));
		tempComponent = new GStar::TextureComponent();
		tempComponent->Initialize(Default_TextureWall);
		tempComponent->Initialize(Default_TextureFace);
		tempObject1->AddComponent(tempComponent);
		TransformComponent1 = new GStar::TransformComponent(tempObject1);
		TransformComponent->AddChildren(TransformComponent1);
		TransformComponent1->SetTransform(GStar::Vector3(0.0f, 0.0f, 5.0f),GStar::Base::PARENT);
		TransformComponent1->SetTransform(GStar::Vector3(0.0f, 0.0f, 5.0f), GStar::Base::SELF);
		TransformComponent1->SetTransform(GStar::Vector3(0.0f, 0.0f, 5.0f), GStar::Base::WORLD);
		tempObject1->AddComponent(TransformComponent1);
		tempObject1->AddComponent(new SimpleRotation());

		//Add Light Source
		tempObject = world.AddObject();
		tempObject->AddComponent(new GStar::MeshComponent(NT_cubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(NT_Shaders));
		tempObject->AddComponent(tempComponent);
		TransformComponent2 = new GStar::TransformComponent(tempObject);
		world.AddToRoot(TransformComponent2);
		TransformComponent2->SetTransform(cubPosition[0], GStar::Base::WORLD);
		tempObject->AddComponent(TransformComponent2);
		KeyControlCompoenent* controllerComponent = new KeyControlCompoenent(TransformComponent2, 1.0f);
		tempObject->AddComponent(controllerComponent);
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
	KeyControlCompoenent* controllerComponent;
};
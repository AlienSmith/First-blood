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
//#include"KeyControlComponent.h"
#include"SimpleForce.h"
#include"PhysicBasedController.h"
#include"CameraManager.h"
#include"LightManager.h"
#include"PhysicManager.h"
class SimpleScene : public GStar::SceneInterface {
public:
	SimpleScene() :GStar::SceneInterface(), TransformComponent(nullptr), TransformComponent1(nullptr) {
		GStar::SceneInterface::Instance = this;
	}
	virtual ~SimpleScene() {
	}
	virtual void Start() {
		GStar::World& world = GStar::World::Instance();
		Object* tempObject = world.AddObject();

		tempObject->AddComponent(new GStar::MeshComponent(normalcubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(Shader2L));
		GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
		tempComponent->Initialize(Default_Texture_BOX);
		tempComponent->Initialize(Default_TextureFace);
		tempObject->AddComponent(tempComponent);
		TransformComponent = new GStar::TransformComponent(tempObject, "RotationCube1");
		world.AddToRoot(TransformComponent);
		TransformComponent->SetTransform(GStar::Vector3(0, 0, -5), GStar::Base::WORLD);
		TransformComponent->SetScale(GStar::Vector3(.5f, .5f, .5f));
		TransformComponent->Rotate(60, 0, 0);
		TransformComponent->UpdateTransform();
		tempObject->AddComponent(TransformComponent);
		//KeyControlCompoenent* controller = new KeyControlCompoenent(TransformComponent,2.0f);
		//tempObject->AddComponent(controller);

		GStar::InterfaceComponent* component = new SimpleRotation(TransformComponent);
		tempObject->AddComponent(component);
		tempObject = world.AddObject();

		tempObject->AddComponent(new GStar::MeshComponent(texturenormalcubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(LM_Shaders));
		GStar::TextureComponent* tempC = new GStar::TextureComponent();
		tempC->Initialize(Default_Diffuse_IronBox);
		tempC->Initialize(Default_Specular_IronBox);
		tempObject->AddComponent(tempC);
		TransformComponent1 = new GStar::TransformComponent(tempObject, "RotationCube2");
		TransformComponent->AddChildren(TransformComponent1);
		TransformComponent1->SetTransform(GStar::Vector3(0, 0, 1), GStar::Base::WORLD);
		tempObject->AddComponent(TransformComponent1);
		TransformComponent1->UpdateTransform();
		//GStar::InterfaceComponent* component1 = new SimpleRotation(TransformComponent1);
		//tempObject->AddComponent(component1);

		Object* tempObject1 = world.AddObject();
		TransformComponent2 = new GStar::TransformComponent(tempObject1, "Camera1");
		world.AddToRoot(TransformComponent2);
		TransformComponent2->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f), GStar::Base::WORLD);
		tempObject1->AddComponent(TransformComponent2);
		TransformComponent2->UpdateTransform();
		//controllerComponent = new KeyControlCompoenent(TransformComponent2, 2.0f);
		//tempObject1->AddComponent(controllerComponent);
		GStar::CameraManager::Instance()->SetCurrentCamera(TransformComponent2);

		tempObject = world.AddObject();
		tempObject->AddComponent(new GStar::MeshComponent(NT_cubeparameters));
		tempObject->AddComponent(new GStar::ShaderComponent(NT_Shaders));
		tempObject->AddComponent(tempComponent);
		TransfomrComponent3 = new GStar::TransformComponent(tempObject, "Light1");
		world.AddToRoot(TransfomrComponent3);
		TransfomrComponent3->SetTransform(GStar::Vector3(0.0f, 0.0f, 0.0f), GStar::Base::WORLD);
		TransfomrComponent3->SetScale(.03f, .03f, .03f);
		tempObject->AddComponent(TransfomrComponent3);
		TransfomrComponent3->UpdateTransform();
		//Directional Light;
		/*GStar::LightComponent* temp = GStar::LightManager::Instance()->GenerateLight(TransfomrComponent3, GStar::Lighttype::DIRECTIONAL);
		temp->SetIntensity(GStar::Vector3(0.2f, 0.2F, 0.2F), GStar::Vector3(0.5f, 0.5F, 0.5F), GStar::Vector3(0.7f, 0.7F, 0.7F));*/
		//Point Light;
		/*GStar::LightComponent* temp = GStar::LightManager::Instance()->GenerateLight(TransfomrComponent3, GStar::Lighttype::POINT);
		temp->SetIntensity(GStar::Vector3(0.0f, 0.0F, 0.0F), GStar::Vector3(0.0f, 0.0F, 1.0F), GStar::Vector3(0.0f, 0.0F, 0.0F));
		temp->SetActivateConsts(.2f, 30.0f, 30.0f);
		temp->SetcutOff(1.05f, 0.0f, 0.0f);*/
		//Spot Light;
		GStar::LightComponent* temp = GStar::LightManager::Instance()->GenerateLight(TransfomrComponent3, GStar::Lighttype::SPOT);
		temp->SetIntensity(GStar::Vector3(0.2f, 0.2F, 0.2F), GStar::Vector3(0.5f, 0.5F, 0.5F), GStar::Vector3(0.7f, 0.7F, 0.7F));
		temp->SetActivateConsts(1.0f, 0.09f, 0.032f);
		temp->SetcutOff(20.0f, 0.5f, 0.707f);

		GStar::PhysicComponent* physic = GStar::PhysicManager::Instance()->AddPhysic(TransfomrComponent3, false, 1.0f, .1f);
		GStar::SimpleForce* forcecomponent = new GStar::SimpleForce(physic,1.0f);
		tempObject->AddComponent(forcecomponent);
		//controllerComponent = new GStar::PhysicBasedController(physic, 5.0f);
		//tempObject->AddComponent(controllerComponent);
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
	GStar::TransformComponent* TransfomrComponent4;
	GStar::TransformComponent* TransfomrComponent5;
	GStar::PhysicBasedController* controllerComponent;
};
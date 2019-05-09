#pragma once
//#include"Manager.h"
#include<stdlib.h>
#include"SceneInterface.h"
#include"World.h"
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
#include"TransformComponent.h"
#include"InterfaceComponent.h"
#include"Data.h"
#include"SimpleRotation.h"
#include"KeyControlComponent.h"
#include"CameraManager.h"
#include"LightManager.h"
#include"ConsolePrint.h"
#include"RManager.h"
#include"World.h"
#include"InterfaceComponentManager.h"
#include"TextureData.h"
#include"SimpleExample.h"
#include"Data.h"
#include"PhysicBasedController.h"
#include"PongController.h"
#include"PhysicComponent.h"
#include"PhysicManager.h"
#include"CollisionComponent.h"
#include"CollisionManager.h"
class PongGame : public GStar::SceneInterface {
public:
	PongGame() {
		GStar::SceneInterface::Instance = this;
	}
	virtual ~PongGame() {}
	virtual void Start() {
		uint8_t texels[3] =
		{
			255,   255,   0,
		};
		int width = 1;
		int height = 1;
		GStar::TextureData texture;
		///Generate and Write files
		//GStar::TextureData* i_texture = SimpleExample::getdata();
		//i_texture->writetofile(RT_Test);
		texture.readformfile(RT_GlassBubble);

		//Camaera
		GStar::World& world = GStar::World::Instance();
		GStar::RManager& renderer = *GStar::RManager::Instance();
		GStar::InterfaceComponentManager& imanager = *GStar::InterfaceComponentManager::Instance();
		trans1 = new GStar::TransformComponent("Camera");
		world.AddToRoot(trans1);
		trans1->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f), GStar::Base::WORLD);
		trans1->UpdateTransform();
		//disable the camera 
		//control1 = new KeyControlCompoenent(trans1, 2.0f);
		//imanager.AddInterface(control1);
		GStar::CameraManager::Instance()->SetCurrentCamera(trans1);
		//BackGround
		trans2 = new GStar::TransformComponent("BackGround");
		world.AddToRoot(trans2);
		trans2->SetTransform(GStar::Vector3(0.0f, 0.0f, -.5f), GStar::Base::WORLD);
		trans2->UpdateTransform();
		RObject& R2 = renderer.CreateRenderObject(trans2);
		GStar::MeshComponent* m2 = new GStar::MeshComponent(spriteTparameters);
		R2.AddComponent(m2);
		GStar::TextureComponent* t2 = new GStar::TextureComponent();
		t2->Initialize(texture.getData());
		R2.AddComponent(t2);
		R2.AddComponent(new GStar::ShaderComponent(DefaultShader2T));

		//Ball
		trans3 = new GStar::TransformComponent("Ball");
		//add transform to the tree or it will not be updated
		world.AddToRoot(trans3);
		trans3->SetTransform(GStar::Vector3(0.0f, 0.0f, -.3f), GStar::WORLD);
		trans3->SetScale(GStar::Vector3(.05f, .05f, .05f));
		trans3->UpdateTransform();
		RObject& R3 = renderer.CreateRenderObject(trans3);
		GStar::MeshComponent* M3 = new GStar::MeshComponent(NT_cubeparameters);
		R3.AddComponent(M3);
		GStar::ShaderComponent* S3 = new GStar::ShaderComponent(NT_Shaders);
		R3.AddComponent(S3);
		GStar::PhysicComponent* P3 = GStar::PhysicManager::Instance()->AddPhysic(trans3, false, 1.0f, .1f);
		P3->SetSpeed(GStar::Vector3(-.5f, 0.0f, 0.0f));
		GStar::CollisionManager::AddCollision(P3, GStar::Vector3(1.0f, 1.0f, 1.0f));

		//Controller 1
		trans4 = new GStar::TransformComponent("Controller1");
		world.AddToRoot(trans4);
		trans4->SetTransform(GStar::Vector3(-0.4f, 0.0f, -.3f), GStar::WORLD);
		trans4->SetScale(GStar::Vector3(.05f, .25f, .05f));
		trans4->UpdateTransform();
		RObject& R4 = renderer.CreateRenderObject(trans4);
		R4.AddComponent(M3);
		R4.AddComponent(S3);
		GStar::PhysicComponent* P4 = GStar::PhysicManager::Instance()->AddPhysic(trans4, false, 1.0f, .1f);
		GStar::CollisionManager::AddCollision(P4, GStar::Vector3(1.0f, 1.0f, 1.0f));
		GStar::InterfaceComponent* I4 = new GStar::PongController(P4, 1.0f, 87, 83);
		imanager.AddInterface(I4);

		//Controller 2
		trans5 = new GStar::TransformComponent("Controller2");
		world.AddToRoot(trans5);
		trans5->SetTransform(GStar::Vector3(0.4f, 0.0f, -.3f), GStar::WORLD);
		trans5->SetScale(GStar::Vector3(.05f, .25f, .05f));
		trans5->UpdateTransform();
		RObject& R5 = renderer.CreateRenderObject(trans5);
		R5.AddComponent(M3);
		R5.AddComponent(S3);
		GStar::PhysicComponent* P5 = GStar::PhysicManager::Instance()->AddPhysic(trans5, false, 1.0f, .1f);
		GStar::CollisionManager::AddCollision(P5, GStar::Vector3(1.0f, 1.0f, 1.0f));
		GStar::InterfaceComponent* I5 = new GStar::PongController(P5, 1.0f, 265, 264);
		imanager.AddInterface(I5);
	}
	virtual void Update() {}
	virtual void Terminate() {}
private:
	GStar::TransformComponent* trans1;
	GStar::InterfaceComponent* control1;
	GStar::TransformComponent* trans2;
	GStar::TransformComponent* trans3;
	GStar::TransformComponent* trans4;
	GStar::TransformComponent* trans5;
	GStar::InterfaceComponent* ai2;
};
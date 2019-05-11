#include "PongGame.h"
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
#include"Vector3.h"
#include"PongBallController.h"
void PongGame::Start()
{
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
	world = &(GStar::World::Instance());
	renderer = GStar::RManager::Instance();
	GStar::InterfaceComponentManager& imanager = *GStar::InterfaceComponentManager::Instance();
	GStar::TransformComponent* trans1 = new GStar::TransformComponent("Camera");
	world->AddToRoot(trans1);
	trans1->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f), GStar::Base::WORLD);
	trans1->UpdateTransform();
	//disable the camera 
	//control1 = new KeyControlCompoenent(trans1, 2.0f);
	//imanager.AddInterface(control1);
	GStar::CameraManager::Instance()->SetCurrentCamera(trans1);
	//BackGround
	GStar::TransformComponent* trans2 = new GStar::TransformComponent("BackGround");
	world->AddToRoot(trans2);
	trans2->SetTransform(GStar::Vector3(0.0f, 0.0f, -.5f), GStar::Base::WORLD);
	trans2->UpdateTransform();
	RObject& R2 = renderer->CreateRenderObject(trans2);
	GStar::MeshComponent* m2 = new GStar::MeshComponent(spriteTparameters);
	R2.AddComponent(m2);
	GStar::TextureComponent* t2 = new GStar::TextureComponent();
	t2->Initialize(texture.getData());
	R2.AddComponent(t2);
	R2.AddComponent(new GStar::ShaderComponent(DefaultShader2T));

	CommonMesh = new GStar::MeshComponent(NT_cubeparameters);
	CommonShader = new GStar::ShaderComponent(NT_Shaders);

	//Ball and two players
	GStar::PhysicComponent* Ball = AddCommonObjects("Ball", GStar::Vector3(0.0f, 0.0f, -.3f), GStar::Vector3(.05f, .05f, .05f),.0001f,1.1f,0.0f);
	GStar::InterfaceComponent* I_Ball = new GStar::PongBallController(Ball, 3.0f, 0.2f);
	GStar::PhysicComponent* Player1 = AddCommonObjects("Controller1", GStar::Vector3(-0.4f, 0.0f, -.3f), GStar::Vector3(.05f, .25f, .05f), 10.0f,.9f,0.5f);
	GStar::InterfaceComponent* I4 = new GStar::PongController(Player1, .1f, 87, 83);
	imanager.AddInterface(I4);
	GStar::PhysicComponent* Player2 = AddCommonObjects("Controller2", GStar::Vector3(0.4f, 0.0f, -.3f), GStar::Vector3(.05f, .25f, .05f), 10.0f,0.9f,0.5f);
	GStar::InterfaceComponent* I5 = new GStar::PongController(Player2, .1f, 265, 264);
	imanager.AddInterface(I5);
	//Wall 1 2 3 4
	AddCommonObjects("Wall1", GStar::Vector3(0.0f, .33f, -.3f), GStar::Vector3(1.0f, .05f, .05f), 100000000.0f,1.0f,0.0f);
	AddCommonObjects("Wall1", GStar::Vector3(0.0f, -.33f, -.3f), GStar::Vector3(1.0f, .05f, .05f),100000000.0f,1.0f,0.0f);

}

GStar::PhysicComponent * PongGame::AddCommonObjects(const GStar::MyString & name, const GStar::Vector3 & position, const GStar::Vector3 & scale, float weight, float collision_constant, float roughness)
{
	GStar::TransformComponent* temp = new GStar::TransformComponent(name);
	world->AddToRoot(temp);
	temp->SetTransform(position, GStar::WORLD);
	temp->SetScale(scale);
	temp->UpdateTransform();
	RObject& R5 = renderer->CreateRenderObject(temp);
	R5.AddComponent(CommonMesh);
	R5.AddComponent(CommonShader);
	GStar::PhysicComponent* P5 = GStar::PhysicManager::Instance()->AddPhysic(temp, false, weight, roughness,collision_constant);
	GStar::CollisionManager::AddCollision(P5, GStar::Vector3(1.0f, 1.0f, 1.0f));
	return P5;
}


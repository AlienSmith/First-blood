#pragma once
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
class TestScene : public GStar::SceneInterface {
public:
	TestScene() {
		GStar::SceneInterface::Instance = this;
	}
	virtual ~TestScene(){}
	virtual void Start() {
		uint8_t texels[4] =
		{
			255,   0,   0,   127,
		};
		int width = 1; 
		int height = 1;
		GStar::TextureData texture(texels, height, width);

		GStar::TextureData* i_texture = SimpleExample::getdata();
		//Camaera
		GStar::World& world = GStar::World::Instance();
		GStar::RManager& renderer = *GStar::RManager::Instance();
		GStar::InterfaceComponentManager& imanager = *GStar::InterfaceComponentManager::Instance();
		trans1 = new GStar::TransformComponent("Camera");
		world.AddToRoot(trans1);
		trans1->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f), GStar::Base::WORLD);
		trans1->UpdateTransform();
		control1 = new KeyControlCompoenent(trans1, 2.0f);
		imanager.AddInterface(control1);
		GStar::CameraManager::Instance()->SetCurrentCamera(trans1);
		//Cube
		trans2 = new GStar::TransformComponent("Cube");
		world.AddToRoot(trans2);
		trans2->SetTransform(GStar::Vector3(0.0f, 0.0f, -1.0f), GStar::Base::WORLD);
		trans2->UpdateTransform();
		RObject& R2 = renderer.CreateRenderObject(trans2);
		GStar::MeshComponent* m2 = new GStar::MeshComponent(cubeparameters);
		R2.AddComponent(m2);
		GStar::TextureComponent* t2 = new GStar::TextureComponent();


		t2->Initialize(Default_Texture_BOX);
		t2->Initialize(i_texture->getData());


		R2.AddComponent(t2);
		R2.AddComponent(new GStar::ShaderComponent(DefaultShader2T));
		ai2 = new SimpleRotation(trans2);
		imanager.AddInterface(ai2);
		delete i_texture;
	}
	virtual void Update() {}
	virtual void Terminate() {}
private:
	GStar::TransformComponent* trans1;
	GStar::InterfaceComponent* control1;
	GStar::TransformComponent* trans2;
	GStar::InterfaceComponent* ai2;
};
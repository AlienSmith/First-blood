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
#include"LightManager.h"
#include"ConsolePrint.h"
class LightScene : public GStar::SceneInterface {
public:
	LightScene() :GStar::SceneInterface(), TransformComponent(nullptr) {
		GStar::SceneInterface::Instance = this;
	}
	virtual ~LightScene() {
	}
	virtual void Start() {
		Modulecount = 0;
		LightShader = new GStar::ShaderComponent(NT_Shaders);
		LightMesh = new GStar::MeshComponent(NT_cubeparameters);
		SpriteMesh = new GStar::MeshComponent(spriteNparameters);
		GStar::World& world = GStar::World::Instance();
		Object* tempObject = world.AddObject();

		Object* tempObject1 = world.AddObject();
		TransformComponent2 = new GStar::TransformComponent(tempObject1, "Camera1");
		world.AddToRoot(TransformComponent2);
		TransformComponent2->SetTransform(GStar::Vector3(0.0f, 0.0f, 1.0f), GStar::Base::WORLD);
		tempObject1->AddComponent(TransformComponent2);
		TransformComponent2->UpdateTransform();
		controllerComponent = new KeyControlCompoenent(TransformComponent2, 2.0f);
		tempObject1->AddComponent(controllerComponent);
		GStar::CameraManager::Instance()->SetCurrentCamera(TransformComponent2);

		GStar::LightComponent* temp = GStar::LightManager::Instance()->GenerateLight(new GStar::TransformComponent(tempObject, "Lights"), GStar::Lighttype::DIRECTIONAL);
		temp->SetIntensity(GStar::Vector3(0.2f, 0.2F, 0.2F), GStar::Vector3(0.0f, 0.0F, 0.0F), GStar::Vector3(0.0f, 0.0F, 0.0F));
		
		AddModule(0.0f, 0.0f, GStar::MyString("Module1"));
		AddModule(2.1f, 0.0f, GStar::MyString("Module2"));
		AddModule(0.0f, 2.1f, GStar::MyString("Module3"));
		AddModule(2.1f, 2.1f, GStar::MyString("Module4"));
	}
	virtual void Update() {
		for (int i = 0; i < Modulecount; i++) {
			CommonShader[i]->GetShader()->use();
			if(!GStar::LightManager::Instance()->WriteToShaderFrom(CommonShader[i]->GetShader(), StartLight[i], 4,true))
				DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Fail TO InitializeShader %d",i);
		}
		check_gl_error();
		//TODO Figure OUT WHY Can not I do this
		/*TransformComponent->SetRotation(GStar::Vector3(Scene::Create()->TotalTime() * 100, 0.0f, 0.0f));
		TransformComponent1->SetRotation(GStar::Vector3(0.0f, Scene::Create()->TotalTime() * 100, 0.0f));*/
	}
	virtual void Terminate() {}
	inline void AddModule(float x, float y, const GStar::MyString& Name) {
		GStar::World& world = GStar::World::Instance();
		Object* tempObject = world.AddObject();
		GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
		tempObject->AddComponent(SpriteMesh);
		CommonShader[Modulecount] = new GStar::ShaderComponent(Shader2L);
		tempObject->AddComponent(CommonShader[Modulecount]);
		TransformComponent = new GStar::TransformComponent(tempObject, Name);
		world.AddToRoot(TransformComponent);
		TransformComponent->SetTransform(GStar::Vector3(x, y, -10.0f), GStar::Base::WORLD);
		TransformComponent->SetScale(GStar::Vector3(2.0f, 2.0f, 2.0f));
		TransformComponent->UpdateTransform();
		tempObject->AddComponent(TransformComponent);

		StartLight[Modulecount] = AddLight(0.5+x, 0.5+y, GStar::Vector3(1.0f, 1.0f, 0.0f));
		 AddLight(-0.5+x, -0.5+y, GStar::Vector3(0.0f, 1.0f, 1.0f));
		 AddLight(0.5+x, -0.5+y, GStar::Vector3(0.0f, 1.0f, 0.0f));
		 AddLight(-0.5+x, 0.5+y, GStar::Vector3(1.0f, 0.0f, 0.0f));
		 Modulecount++;
	}
	inline GStar::LightComponent* AddLight(float x, float y, const GStar::Vector3& color) {
		GStar::World& world = GStar::World::Instance();
		Object* tempObject = world.AddObject();
		tempObject->AddComponent(LightMesh);
		tempObject->AddComponent(LightShader);
		TransfomrComponent5 = new GStar::TransformComponent(tempObject, "Lights");
		world.AddToRoot(TransfomrComponent5);
		TransfomrComponent5->SetTransform(GStar::Vector3(x, y, -9.7f), GStar::Base::WORLD);
		TransfomrComponent5->SetScale(.1, .1, .1);
		tempObject->AddComponent(TransfomrComponent5);
		TransfomrComponent5->UpdateTransform();
		GStar::LightComponent* temp = GStar::LightManager::Instance()->GenerateLight(TransfomrComponent5, GStar::Lighttype::POINT);
		temp->SetIntensity(GStar::Vector3(0.0f, 0.0F, 0.0F), color, GStar::Vector3(0.0f, 0.0F, 0.0F));
		temp->SetActivateConsts(.2f, 0.0f, 6.0f);
		temp->SetcutOff(1.05f, 0.0f, 0.0f);
		return temp;
	}
private:
	GStar::TransformComponent* TransformComponent;
	GStar::TransformComponent* TransformComponent2;
	GStar::TransformComponent* TransfomrComponent5;
	KeyControlCompoenent* controllerComponent;
	GStar::ShaderComponent* LightShader;
	GStar::MeshComponent* LightMesh;
	GStar::MeshComponent* SpriteMesh;
	GStar::ShaderComponent* CommonShader[4];
	GStar::LightComponent* StartLight[4];
	int Modulecount;
};
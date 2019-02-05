#include"Scene.h"
#include"View.h"
#include"Controller.h"
#include"World.h"
#include"UpdateRObject.h"
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
#include"TransformComponent.h"
#include"InterfaceComponentManager.h"
#include"SimpleRotationCopy.h"
#include"Data.h"
#include"Assert.h"
#include"GLError.h"
#include"SceneInterface.h"
#include"EventManager.h"
#include"KeyInputEvent.h"
#include"PhysicManager.h"
Scene* myScene = nullptr;
Controller* myController = nullptr;
View* myView = nullptr;
void mouse_call(GLFWwindow * window, double xpos, double ypos);
void framebuffer_size_call(GLFWwindow * windwo, int width, int height);
void CleanScreen();
void MainEntrance() {
	myScene = Scene::Create();
	myController = new Controller(myScene);
	myView = new View(myScene);
	GStar::World& world = GStar::World::Instance();
	//Game Code
	if (GStar::SceneInterface::Instance) {
		GStar::SceneInterface::Instance->Start();
	}
	///Intialization Area
	
	//this code is used for test indivisual component. Noteice the Component directly communicate with UpdateObject::OUT_Instance
	//instead of holding a reference to the object it is attached to (which is always the UpdateObject::OUT_Instance)
	//Add /*tempObject->Update();*/ to Update cercle to test it.

	/*UpdateObject::IN_Instance;d
	UpdateObject::OUT_Instance;
	Object* tempObject = new Object();
	tempObject->AddComponent(new GStar::MeshComponent(cubeparameters));
	tempObject->AddComponent(new GStar::ShaderComponent(DefaultShader2T));
	GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
	tempComponent->Initialize(Default_Texture_BOX);
	tempComponent->Initialize(Default_TextureFace);
	tempObject->AddComponent(tempComponent);
	GStar::TransformComponent* TransformComponent = new GStar::TransformComponent(world.AddObject());
	TransformComponent->SetTransform(cubPosition[1]);
	tempObject->AddComponent(TransformComponent);
	GStar::InterfaceComponent* rotation = new SimpleRotationCopy();
	tempObject->AddComponent(rotation);
	tempObject->Update();*/

	//Set up 
	//Bind CallBack Function
	glfwSetFramebufferSizeCallback(myScene->Window(), framebuffer_size_call);
	glfwSetCursorPosCallback(myScene->Window(), mouse_call);
	//RenderLoop
	while (!glfwWindowShouldClose(myScene->Window())) {
		if (GStar::SceneInterface::Instance) {
			GStar::SceneInterface::Instance->Update();
		}
		myScene->UpdateTime();
		///Interface Class
		myController->Update();
		GStar::InterfaceComponentManager::Instance()->Update();

		GStar::PhysicManager::Instance()->Update();
		CleanScreen();
		world.Update();
		myScene->UpdateEnd();
	}
	myScene->TerminateWindow();
	if (GStar::SceneInterface::Instance) {
		GStar::SceneInterface::Instance->Terminate();
	}
	delete myScene;
	delete myController;
	delete myView;
}
void mouse_call(GLFWwindow * window, double xpos, double ypos)
{
	myController->mouse_callBack(window, xpos, ypos);
}
void framebuffer_size_call(GLFWwindow * windwo, int width, int height)
{
	myController->framebuffer_size_callback(windwo, width, height);
}
void CleanScreen() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// set color
	   //glClear(GL_COLOR_BUFFER_BIT); // only clean the color not depth and stencil
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//  clean the color and depth
}

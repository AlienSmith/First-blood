#include "MainEntrance.h"
#include"World.h"
#include"UpdateObject.h"
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
#include"TransformComponent.h"
#include"InterfaceComponent.h"
#include"SimpleRotationCopy.h"
#include"Data.h"
#include"Assert.h"
#include"GLError.h"
#include"SceneInterface.h"
#include"KeyInputEvent.h"
MainEntrance* MainEntrance::instance = nullptr;
void MainEntrance::SetUpAndRun()
{
	MainEntrance::instance = new MainEntrance();
	MainEntrance::instance->Run();
}


void MainEntrance::Run()
{
	GStar::World& world = GStar::World::Instance();
	//Game Code
	if (GStar::SceneInterface::Instance) {
		GStar::SceneInterface::Instance->Start();
	}
	//this code is used for test indivisual component. Noteice the Component directly communicate with UpdateObject::OUT_Instance
	//instead of holding a reference to the object it is attached to (which is always the UpdateObject::OUT_Instance)
	//Add /*tempObject->Update();*/ to Update cercle to test it.

	/*UpdateObject::IN_Instance;
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
	glfwSetCursorPosCallback(myScene->Window(), MainEntrance::mouse_call);
	glfwSetKeyCallback(myScene->Window(), MainEntrance::keyboard_call);
	//RenderLoop
	while (!glfwWindowShouldClose(myScene->Window())) {
		if (GStar::SceneInterface::Instance) {
			GStar::SceneInterface::Instance->Update();
		}
		myScene->UpdateTime();
		myController->Update();
		CleanScreen();
		world.Update(myScene->Deltatime());
		myScene->UpdateEnd();
	}
	myScene->TerminateWindow();
	if (GStar::SceneInterface::Instance) {
		GStar::SceneInterface::Instance->Terminate();
	}
	delete myScene;
	delete myController;
}

void MainEntrance::mouse_call(GLFWwindow * window, double xpos, double ypos)
{
	MainEntrance::instance->myController->mouse_callBack(window, xpos, ypos);
}

void MainEntrance::framebuffer_size_call(GLFWwindow * window, int width, int height)
{
	MainEntrance::instance->myController->framebuffer_size_callback(window, width, height);
}
//The keyinputevent object will die with the function
void MainEntrance::keyboard_call(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	MainEntrance::instance->KeyBoardInput.Invoke(new GStar::KeyInputEvent(key,action));
}

void MainEntrance::CleanScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// set color
	   //glClear(GL_COLOR_BUFFER_BIT); // only clean the color not depth and stencil
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//  clean the color and depth
}

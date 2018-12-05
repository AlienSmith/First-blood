#include"Scene.h"
#include"View.h"
#include"Controller.h"
#include"World.h"
#include"UpdateObject.h"
#include"ComponentInclude.h"
#include"Data.h"
Scene* myScene = Scene::Create();
Controller myController(myScene);
View myView(myScene);
void mouse_call(GLFWwindow * window, double xpos, double ypos);
void framebuffer_size_call(GLFWwindow * windwo, int width, int height);
void MainEntrance() {
	GStar::World& world = GStar::World::Instance();
	//SetUp An Object
	Object& tempObject = world.AddObject();
	tempObject.AddComponent(new GStar::MeshComponent(cubeparameters));
	tempObject.AddComponent(new GStar::ShaderComponent(DefaultShader2T));
	GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
	tempComponent->Initialize(Default_Texture_BOX);
	tempComponent->Initialize(Default_TextureFace);
	tempObject.AddComponent(tempComponent);
	GStar::TransformComponent* TransformComponent = new GStar::TransformComponent();
	TransformComponent->SetTransform(cubPosition[0]);
	tempObject.AddComponent(TransformComponent);
	
	//Set up 
	//Bind CallBack Function
	glfwSetFramebufferSizeCallback(myScene->Window(), framebuffer_size_call);
	glfwSetCursorPosCallback(myScene->Window(), mouse_call);
	//RenderLoop
	while (!glfwWindowShouldClose(myScene->Window())) {
		
		myScene->UpdateTime();
		myController.Update();
		myScene->Update();
		myView.Update();
		myScene->UpdateEnd();
		//world.Update();
	}
	myScene->TerminateWindow();
	delete myScene;
}
void mouse_call(GLFWwindow * window, double xpos, double ypos)
{
	myController.mouse_callBack(window, xpos, ypos);
}
void framebuffer_size_call(GLFWwindow * windwo, int width, int height)
{
	myController.framebuffer_size_callback(windwo, width, height);
}
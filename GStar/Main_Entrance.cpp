#include"Scene.h"
#include"View.h"
#include"Controller.h"
#include"World.h"
#include"UpdateObject.h"
#include"ComponentInclude.h"
#include"Data.h"
#include"Assert.h"
#include"GLError.h"
Scene* myScene = Scene::Create();
Controller myController(myScene);
View myView(myScene);
void mouse_call(GLFWwindow * window, double xpos, double ypos);
void framebuffer_size_call(GLFWwindow * windwo, int width, int height);
void CleanScreen();
void MainEntrance() {
	GStar::World& world = GStar::World::Instance();
	//Game Code
	Object& tempObject = world.AddObject();
	tempObject.AddComponent(new GStar::MeshComponent(cubeparameters));
	tempObject.AddComponent(new GStar::ShaderComponent(DefaultShader2T));
	GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
	tempComponent->Initialize(Default_Texture_BOX);
	tempComponent->Initialize(Default_TextureFace);
	tempObject.AddComponent(tempComponent);
	GStar::TransformComponent* TransformComponent = new GStar::TransformComponent();
	TransformComponent->SetTransform(cubPosition[1]);
	tempObject.AddComponent(TransformComponent);
	
	/*Object& tempObject1 = world.AddObject();

	tempObject1.AddComponent(new GStar::MeshComponent(cubeparameters));
	tempObject1.AddComponent(new GStar::ShaderComponent(DefaultShader2T));
	tempComponent = new GStar::TextureComponent();
	tempComponent->Initialize(Default_Texture_BOX);
	tempComponent->Initialize(Default_TextureFace);
	tempObject.AddComponent(tempComponent);
	TransformComponent = new GStar::TransformComponent();
	TransformComponent->SetTransform(cubPosition[1]);
	tempObject.AddComponent(TransformComponent);*/

	//Set up 
	//Bind CallBack Function
	glfwSetFramebufferSizeCallback(myScene->Window(), framebuffer_size_call);
	glfwSetCursorPosCallback(myScene->Window(), mouse_call);
	//RenderLoop
	while (!glfwWindowShouldClose(myScene->Window())) {
		myScene->UpdateTime();
		myController.Update();
		CleanScreen();
		//myScene->Update();
		//myView.Update();
		world.Update();
		myScene->UpdateEnd();
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
void CleanScreen() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// set color
	   //glClear(GL_COLOR_BUFFER_BIT); // only clean the color not depth and stencil
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//  clean the color and depth
}
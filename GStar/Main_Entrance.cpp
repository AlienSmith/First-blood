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
	UpdateObject tempObject;
	tempObject.SetMesh(new GStar::MeshComponent(cubeparameters));
	tempObject.SetShader(new GStar::ShaderComponent(DefaultShader2T));
	GStar::TextureComponent* tempComponent = new GStar::TextureComponent();
	tempComponent->Initialize(Default_Texture_BOX);
	tempComponent->Initialize(Default_TextureFace);
	tempObject.SetTexture(tempComponent);
	GStar::TransformComponent* TransformComponent = new GStar::TransformComponent();
	TransformComponent->SetTransform(cubPosition[0]);
	tempObject.SetTransform(TransformComponent);
	
	UpdateObject tempObject1;
	tempObject1.SetMesh(new GStar::MeshComponent(cubeparameters));
	tempObject1.SetShader(new GStar::ShaderComponent(DefaultShader2T));
	tempComponent = new GStar::TextureComponent();
	tempComponent->Initialize(Default_TextureWall);
	tempComponent->Initialize(Default_TextureFace);
	tempObject1.SetTexture(tempComponent);
	TransformComponent = new GStar::TransformComponent();
	TransformComponent->SetTransform(cubPosition[1]);
	tempObject1.SetTransform(TransformComponent);

	UpdateObject::OUT_Instance = &tempObject;
	UpdateObject::IN_Instance = &tempObject1;
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
		//world.Update();
		UpdateObject::OUT_Instance->Update();
		UpdateObject::Swamp();

		UpdateObject::OUT_Instance->Update();
		UpdateObject::Swamp();
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
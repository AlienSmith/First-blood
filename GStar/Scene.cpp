#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include "Scene.h"
#include "Data.h"
#include"ConsolePrint.h"
// return nullptr as fail, Remeber to delete this pointer
Scene* Scene::Create()
{
	Scene* currentScene = new Scene(); 
	if (!currentScene->SetupWindow()) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Fail set up window");
		return nullptr;
	}
	
	
	return currentScene;
}

//This function specifies opengl version set glfw window and initialize glad 
bool Scene::SetupWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// Using Core Content
	window = glfwCreateWindow(Data::SCR_WIDTH, Data::SCR_HEIGHT, Data::title, NULL, NULL);
	if (!window) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Fail to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Failed to initialize GLAD");
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	return true;
}

bool Scene::LoadObject()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//claim a name different function from VBO
	glBindVertexArray(VAO);

	//Put the data inside
	// require buffers for the vertices on GPU VBO for Vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO); // how many object names (unsigned integer) and where to store it.

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO is GL_ARRAY_BUFFER. see docs.GL for other type

	glBufferData(GL_ARRAY_BUFFER, sizeof(Data::cubevertexs), Data::cubevertexs, GL_STATIC_DRAW); // COPY DATA IN TO BUFFER
	// static_Draw will rarely change, dynamic_draw will change, stream_draw change every time it draw
	// deteminds where the data will be putted

	//Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FASTEST, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return true;
}


Scene::Scene():
	my_camera(GStar::Camera()),
	projection(GStar::Matrix4(IDENTICAL_MATRIX)),
	model(GStar::Matrix4(IDENTICAL_MATRIX)),
	my_shaders(Shader(Data::vs, Data::fs)), //TODO add Creator To Shader
	deltaTime(0.0f),
	LastFrame(0.0f),
	currentFrame(0.0f),
	window(nullptr){}


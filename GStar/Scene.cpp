#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include "Scene.h"
#include "Data.h"
#include"ConsolePrint.h"
#include"stb_image.h"
#include "Coordinate.h"
// return nullptr as fail, Remeber to delete this pointer
Scene* Scene::Create()
{
	//Load Shader
	Scene* currentScene = new Scene(); 
	if (!currentScene->SetupWindow()) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Fail set up window");
		return nullptr;
	}if (!currentScene->LoadObject()) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Fail load Object");
		return nullptr;
	}
	currentScene->SetPespective();

	return currentScene;
}

bool Scene::Update()
{
	glBindVertexArray(VAO);
	//render loop
	float radius = 10.0f;
	float camX = sin(glfwGetTime())*radius;
	float camZ = cos(glfwGetTime())*radius;
	//my_camera.Set_Pos(GStar::Vector3(camX, 0.0f, camZ));
	my_camera.Update();
	GStar::Matrix4 view = my_camera.view;
	my_shaders.setMat4("view", view, GL_FALSE);
	//Rotate the matrix

	return false;
}

//This function specifies opengl version set glfw window and initialize glad 
bool Scene::SetupWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// Using Core Content
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,title, NULL, NULL);
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
	glGenVertexArrays(1, &VAO);//claim a name different function from VBO
	glBindVertexArray(VAO);

	//Put the data inside
	// require buffers for the vertices on GPU VBO for Vertex buffer object
	glGenBuffers(1, &VBO); // how many object names (unsigned integer) and where to store it.

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO is GL_ARRAY_BUFFER. see docs.GL for other type

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubevertexs), cubevertexs, GL_STATIC_DRAW); // COPY DATA IN TO BUFFER
	// static_Draw will rarely change, dynamic_draw will change, stream_draw change every time it draw
	// deteminds where the data will be putted

	//Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FASTEST, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return true;
}

unsigned int Scene::LoadTexture(const char file[])
{
	//load texture
	stbi_set_flip_vertically_on_load(true);// Flip the picture by x axies
	int width, height, nrChannels; //out parameter
	unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);

	unsigned int texture;// the texture object
	glGenTextures(1, &texture); // claim a name 1 texture out parameter name.
	glBindTexture(GL_TEXTURE_2D, texture); // bind name

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	///load texture data into graphic card
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "Fail to LoadTexture");
	}//Create minimap since the texture is binded.
	stbi_image_free(data);
	return texture;
}

bool Scene::SetPespective()
{
	//TODO rewrite and seperate this parts when put textuers in singlelinkedlist
	texture1 = LoadTexture(WoodBox);
	glActiveTexture(GL_TEXTURE0); // activate the texture unit 0
	glBindTexture(GL_TEXTURE_2D, texture1); // bind name
	texture2 = LoadTexture(SmileFace);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//set both front and back buffer to line mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// set back
	projection = GStar::perspective(projection, 45, SCR_WIDTH / SCR_HEIGHT, .1f, 100.0f);

	//TODO seperate this part to load shader
	my_shaders.use();
	my_shaders.setFloat("offset", 0.1);
	my_shaders.setInt("texture1", 0);
	my_shaders.setInt("texture2", 1);
	my_shaders.setMat4("projection", projection, GL_FALSE);

	return true;
}


Scene::Scene():
	my_camera(GStar::Camera()),
	projection(GStar::Matrix4(IDENTICAL_MATRIX)),
	model(GStar::Matrix4(IDENTICAL_MATRIX)),
	my_shaders(Shader(vs, fs)), //TODO add Creator To Shader
	deltaTime(0.0f),
	LastFrame(0.0f),
	currentFrame(0.0f),
	window(nullptr),
	VAO(0),
	VBO(0),
	texture1(0),
	texture2(0){}


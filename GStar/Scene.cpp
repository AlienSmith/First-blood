#include "Scene.h"
#include "Data.h"
#include"ConsolePrint.h"
#include"stb_image.h"
#include "Coordinate.h"
#include "GSTime.h"
#include "TextureData.h"
Scene* Scene::Instance = nullptr;
// return nullptr as fail, Remeber to delete this pointer
Scene* Scene::Create()
{
	if (Scene::Instance == nullptr) {
		Scene* currentScene = new Scene();
		//Load Default;
		if (!currentScene->SetupWindow()) {
			DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Fail set up window");
			return nullptr;
		}
		currentScene->SetPespective();
		Scene::Instance = currentScene;
	}
	return Scene::Instance;
}

bool Scene::Update()
{
	glBindVertexArray(VAO);
	my_shaders->use();
	my_shaders->setFloat("offset", 0.1f);
	my_shaders->setInt("texture1", 0);
	my_shaders->setInt("texture2", 1);
	my_shaders->setMat4("view", view, GL_FALSE);
	my_shaders->setMat4("projection", projection, GL_FALSE);
	//Rotate the matrix

	return false;
}


void Scene::UpdateTime()
{
	GStar::GSTime::Instance().Tick();
}

unsigned int Scene::LoadMesh(const MeshParameters & parameters) const
{
	GLsizei entrysize = parameters.positionsize + parameters.texturesize + parameters.normalsize;
	unsigned int TempVAO;
	glGenVertexArrays(1, &TempVAO);//claim a name different function from VBO
	glBindVertexArray(TempVAO);

	unsigned int TempVBO;
	//Put the data inside
	// require buffers for the vertices on GPU VBO for Vertex buffer RObject
	glGenBuffers(1, &TempVBO); // how many RObject names (unsigned integer) and where to store it.

	glBindBuffer(GL_ARRAY_BUFFER, TempVBO); //VBO is GL_ARRAY_BUFFER. see docs.GL for other type

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* parameters.numelements, parameters.data, GL_STATIC_DRAW); // COPY DATA IN TO BUFFER
	// static_Draw will rarely change, dynamic_draw will change, stream_draw change every time it draw
	// deteminds where the data will be putted

	//Link Vertex Attributes
	glVertexAttribPointer(0, parameters.positionsize, GL_FLOAT, GL_FALSE,  entrysize* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	if (parameters.texturesize != 0) {
		glVertexAttribPointer(1, parameters.texturesize, GL_FLOAT, GL_FALSE, entrysize * sizeof(float), (void*)(parameters.positionsize * sizeof(float)));
		glEnableVertexAttribArray(1);
	}if (parameters.normalsize != 0) {
		glVertexAttribPointer(2, parameters.normalsize, GL_FLOAT, GL_FALSE, entrysize * sizeof(float), (void*)((parameters.positionsize+parameters.texturesize) * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	return TempVAO;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	GStar::GSTime::Instance().Initialize();
	return true;
}

bool Scene::LoadObject()
{
	glGenVertexArrays(1, &VAO);//claim a name different function from VBO
	glBindVertexArray(VAO);

	//Put the data inside
	// require buffers for the vertices on GPU VBO for Vertex buffer RObject
	glGenBuffers(1, &VBO); // how many RObject names (unsigned integer) and where to store it.

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO is GL_ARRAY_BUFFER. see docs.GL for other type

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubevertexs), cubevertexs, GL_STATIC_DRAW); // COPY DATA IN TO BUFFER
	// static_Draw will rarely change, dynamic_draw will change, stream_draw change every time it draw
	// deteminds where the data will be putted

	//Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return true;
}

unsigned int Scene::LoadTexture(const TextureParameters& parameters) const
{
	//load texture
	//stbi_set_flip_vertically_on_load(true);// Flip the picture by x axies
	int width, height, nrComponents; //out parameter
	unsigned char *data = stbi_load(parameters.textureroute, &width, &height, &nrComponents, 0);

	unsigned int texture;// the texture RObject
	glGenTextures(1, &texture); // claim a name 1 texture out parameter name.
	glBindTexture(GL_TEXTURE_2D, texture); // bind name

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	///load texture data into graphic card
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		else
			format = GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "Fail to LoadTexture");
	}//Create minimap since the texture is binded.
	stbi_image_free(data);
	return texture;
}

unsigned int Scene::LoadTexture(const GStar::texturedata & parameters) const
{
	unsigned int texture;// the texture RObject
	glGenTextures(1, &texture); // claim a name 1 texture out parameter name.
	glBindTexture(GL_TEXTURE_2D, texture); // bind name
	// Allocate the storage.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, parameters.y, parameters.x, 0, GL_RGBA8, GL_UNSIGNED_BYTE, parameters.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return texture;
}

bool Scene::SetPespective()
{

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//set both front and back buffer to line mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Change the ratio between width and height to float will redering everything in right proportiong. 
	//would need to change the value if the screen got resized.
	//PerSPectiveSetting
	projection = GStar::perspective(projection, 45, (float)SCR_WIDTH / SCR_HEIGHT, .1f, 100.0f);
	//projection = GStar::orthogrphic(projection, 45, (float)SCR_WIDTH / SCR_HEIGHT, .1f, 100.0f);
	return true;
}

bool Scene::CompileShader()
{
	texture1 = LoadTexture(Default_Texture_BOX);
	texture2 = LoadTexture(Default_TextureFace);
	my_shaders = Shader::Create(vs,fs);
	//TODO rewrite and seperate this parts when put textuers in singlelinkedlist
	glActiveTexture(GL_TEXTURE0); // activate the texture unit 0
	glBindTexture(GL_TEXTURE_2D, texture1); // bind name
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// set back
	//projection = GStar::perspective(projection, 45, SCR_WIDTH / SCR_HEIGHT, .1f, 100.0f);

	return true;
}


Scene::Scene():
	projection(GStar::Matrix4(IDENTICAL_MATRIX)),
	view(GStar::Matrix4(IDENTICAL_MATRIX)),
	my_shaders(nullptr), //TODO add Creator To Shader
	window(nullptr),
	VAO(0),
	VBO(0),
	texture1(0),
	texture2(0){
}


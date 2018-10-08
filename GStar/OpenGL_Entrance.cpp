#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include"ConsolePrint.h"
//Initial window size
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Shaders
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* windwo, int width, int height);
void processInput(GLFWwindow* window);
void CleanSCreen();

void Entrance() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == nullptr) {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Fail to create GLFW window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Failed to initialize GLAD");
	}

	// we do not need to sed viewport because the callback function will be called at beginning.
	//glViewport(0, 0, 800, 600);
	//Register the resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//vertex data only position now
	float vertices[] = {
	 // first triangle
	  0.5f,  0.5f, 0.0f,  // top right
	  0.5f, -0.5f, 0.0f,  // bottom right
	 -0.5f,  0.5f, 0.0f,  // top left 
	};
	//Rectangle
	float verticesRec[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//VAO for draw Rectangle
	//Element Buffer Object 
	///Bind VAO
	unsigned int VAOREC;
	glGenVertexArrays(1, &VAOREC);
	glBindVertexArray(VAOREC);
	///COPY vertex array
	unsigned int VBORec;
	glGenBuffers(1, &VBORec);
	glBindBuffer(GL_ARRAY_BUFFER, VBORec);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRec), verticesRec, GL_STATIC_DRAW);
	///Copy index Array
	unsigned int EBO;
	glGenBuffers(1, &EBO);// claim a name samve with VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// bind the name here is element array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	///we need six point to draw to tirangle. int have same size as float buffer data

	///Set Attribute Pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	

	//Vertex Array Object VAO to avoid previous problem
	//VAO is a array that sotre the pointer to VBO's each attribute
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//claim a name different function from VBO
	glBindVertexArray(VAO);

	//Put the data inside
	// require buffers for the vertices on GPU VBO for Vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO); // how many object names (unsigned integer) and where to store it.

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO is GL_ARRAY_BUFFER. see docs.GL for other type

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // COPY DATA IN TO BUFFER
	// static_Draw will rarely change, dynamic_draw will change, stream_draw change every time it draw
	// deteminds where the data will be putted


	//Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	///Every time we want to draw a object we need to bind the name, buffer the 
	///data and Link Vertex Attributes and Enable it.
	

	//Compile shaders
	///VERTEX_SHADER how to interprate vertex
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // obtain a name

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach the code
	
	glCompileShader(vertexShader); //Compile shaders

	///Store the compile error
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);// pass lots of things by address
	///if not success print the info.
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Vertex Shader Compile error %s", infoLog);
	}
	///Fragment Shader calculate color for each pixel

	unsigned int fragmentshader;
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);

	///Store the compile error
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);// pass lots of things by address
	///if not success print the info.
	if (!success) {
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Fragment Shader Compile error %s",infoLog);
	}

	// Bind shader to program
	unsigned int shaderprogram;
	shaderprogram = glCreateProgram();

	glAttachShader(shaderprogram, vertexShader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Link Error");
	}
	
	glUseProgram(shaderprogram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentshader);







	//The render loop
	while (!glfwWindowShouldClose(window))// return ture if GLFW is instructed to close
	{	//input 
		processInput(window);

		//Clean Window or the old pixel will stay
		CleanSCreen();

		//Draw
		glUseProgram(shaderprogram);
		glBindVertexArray(VAOREC);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //which primitive, vertex array start, how may points
		// check and call events and swap the buffers
		glfwSwapBuffers(window);// swamp color buffer. and show what drawed in this iteration
		glfwPollEvents();// checks events update functions
	}
	glfwTerminate();





}
// Whenever the window changes in size, GLFW calls 
//this function and fills in the proper arguments for you to process.
void framebuffer_size_callback(GLFWwindow * windwo, int width, int height)
{
	glViewport(0, 0, width, height);// Viewport and window are different.
}

void processInput(GLFWwindow * window)
{
	//if focused on the window and esc pressed set shouldclose to true
	//if not pressed the return value is GLFW_RELEASE
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void CleanSCreen()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// set color
	glClear(GL_COLOR_BUFFER_BIT); // only clean the color not depth and stencil
}

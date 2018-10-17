#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include"ConsolePrint.h"
#include"Shader.h"
#include"stb_image.h"
#include "Coordinate.h"
#include "Camera.cpp"
void framebuffer_size_callback(GLFWwindow* windwo, int width, int height);
void processInput(GLFWwindow* window);
void CleanSCreen();

//Initial window size
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mixValue = 0.2f;


void Entrance() {
	//Going to 3D
	GStar::Vector3 cubPosition[] = {
	GStar::Vector3(0.0f,0.0f,0.0f),
	GStar::Vector3(2.0f,5.0f,-15.0f),
	GStar::Vector3(-1.5f, -2.2f, -2.5f),
	GStar::Vector3(-3.8f, -2.0f, -12.3f),
	GStar::Vector3(2.4f, -0.4f, -3.5f),
	GStar::Vector3(-1.7f,  3.0f, -7.5f),
	GStar::Vector3(1.3f, -2.0f, -2.5f),
	GStar::Vector3(1.5f,  2.0f, -2.5f),
	GStar::Vector3(1.5f,  0.2f, -1.5f),
	GStar::Vector3(-1.3f,  1.0f, -1.5f)
	};
	//topleft = model * topleft;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Fail to create GLFW window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Failed to initialize GLAD");
	}
	glEnable(GL_DEPTH_TEST);
	// we do not need to sed viewport because the callback function will be called at beginning.
	//glViewport(0, 0, 800, 600);
	//Register the resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//vertex data only position now
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// use to specify where three vertex be on the texture
	float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FASTEST, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//load texture
	stbi_set_flip_vertically_on_load(true);// Flip the picture by x axies
	int width, height, nrChannels; //out parameter
	unsigned char *data = stbi_load("../GStar/woodcontainer.jpg", &width, &height, &nrChannels, 0);

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

	//load another texture and store it in texture unit 1
	unsigned int textureface;
	glGenTextures(1, &textureface); // claim name;
	glBindTexture(GL_TEXTURE_2D,textureface);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("../GStar/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "Fail to LoadTexture");
	}
	stbi_image_free(data);

	//Vertex Array Object VAO to avoid previous problem
	//VAO is a array that sotre the pointer to VBO's each attribute

	/*unsigned int VEO;
	glGenBuffers(1, &VEO); // Claim a name
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*/
	//Compile Shaders
	Shader my_shader = Shader("../GStar/VertexColor.ves", "../GStar/VertexColor.frs");
	glActiveTexture(GL_TEXTURE0); // activate the texture unit 0
	glBindTexture(GL_TEXTURE_2D, texture); // bind name
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureface);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//set both front and back buffer to line mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// set back
	//The render loop
	GStar::Matrix4 projection = GStar::Matrix4(IDENTICAL_MATRIX);
	projection = GStar::perspective(projection, 45, SCR_WIDTH / SCR_HEIGHT, .1f, 100.0f);
	
	GStar::Camera my_camera = GStar::Camera();
	while (!glfwWindowShouldClose(window))// return ture if GLFW is instructed to close
	{	//input 
		processInput(window);

		//Clean Window or the old pixel will stay
		CleanSCreen();

		//Change The mixed value
		//my_shader.setFloat("alphavalue", mixValue);
		my_shader.use();

		glBindVertexArray(VAO);
		//render loop
		float radius = 10.0f;
		float camX = sin(glfwGetTime())*radius;
		float camZ = cos(glfwGetTime())*radius;
		my_camera.Set_Pos(GStar::Vector3(camX, 0.0f, camZ));
		my_camera.Update();
		GStar::Matrix4 view = my_camera.view;
		//Rotate the matrix
		my_shader.setFloat("offset", 0.1);
		my_shader.setInt("texture1", 0);
		my_shader.setInt("texture2", 1);
		//GStar::Matrix4 model = GStar::Matrix4(IDENTICAL_MATRIX); //Transform in to world space
		//model = GStar::Rotate(model, (float)glfwGetTime() * 100, (float)glfwGetTime() * 100, (float)glfwGetTime() * 100);
		//my_shader.setMat4("model", model);
		my_shader.setMat4("view", view, GLFW_TRUE);
		my_shader.setMat4("projection", projection,GL_FALSE);
		for (unsigned int i = 0; i < 10; i++) {
			GStar::Matrix4 model = GStar::Matrix4(IDENTICAL_MATRIX);
			model = GStar::Transform(model, cubPosition[i].x(), cubPosition[i].y(),cubPosition[i].z());
			float angle = 20.0f*i;
			//model = GStar::Rotate(model, (float)glfwGetTime() * 100,cubPosition[i]);
			my_shader.setMat4("model", model, GL_FALSE);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		mixValue += 0.001f;
		if (mixValue >= 1.0f) {
			mixValue = 1.0f;
		}
	}else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		mixValue -= 0.001f;
		if (mixValue <= 0.0f) {
			mixValue = 0.0f;
		}
	}
}

void CleanSCreen()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// set color
	//glClear(GL_COLOR_BUFFER_BIT); // only clean the color not depth and stencil
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//  clean the color and depth
}

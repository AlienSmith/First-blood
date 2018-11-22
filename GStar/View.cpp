#include "View.h"
#include "Scene.h"
#include "Data.h"
#include "Coordinate.h"

void View::Update()
{
	CleanScreen();
	for (unsigned int i = 0; i < 10; i++) {
		GStar::Matrix4 model = GStar::Matrix4(IDENTICAL_MATRIX);
		model = GStar::Transform(model, cubPosition[i].x(), cubPosition[i].y(), cubPosition[i].z());
		float angle = 20.0f*i;
		model = GStar::Rotate(model, (float)glfwGetTime() * 100, cubPosition[i]);
		my_scene->Shaders().setMat4("model", model, GL_FALSE);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void View::CleanScreen()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// set color
	   //glClear(GL_COLOR_BUFFER_BIT); // only clean the color not depth and stencil
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//  clean the color and depth
}

#pragma once
#include"Vector3.h"
#include"GLINCLUDE.h"
const static unsigned int SCR_WIDTH = 800;
const static unsigned int SCR_HEIGHT = 600;
//TODO Could add more details
const struct TextureParameters {
	const char* textureroute;
	unsigned int inchannel;
	unsigned int outchannel;
};
const struct ShaderParameters {
	const char* vs;
	const char* fs;
};
//Postion and Texture position
const struct MeshParameters
{
	const int numelements;
	const int positionsize;
	const int texturesize;
	const int TriangleIndex;
	const float* data;
};
const static float sprite[] = {
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
};
const static float cubevertexs[] = {
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
const static GStar::Vector3 cubPosition[] = {
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

const static float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
}; 

const static char title[] = "GStar Test Scene";
const static char WoodBox[] = "../GStar/woodcontainer.jpg";
const static char Wall[] = "../GStar/wall.jpg";
const static char SmileFace[] = "../GStar/awesomeface.png";
const static char vs[] = "../GStar/VertexColor.ves";
const static char fs[] = "../GStar/VertexColor.frs";
// Shader
const static size_t ShadersHeapSize = 1024;
const static size_t SceneHeapSize = 32768;
const static MeshParameters cubeparameters = { 180,3,2,36,cubevertexs };
const static MeshParameters spriteparameters = { 30,3,2,6, sprite};
const static ShaderParameters DefaultShader2T = { vs,fs };
const static TextureParameters Default_Texture_BOX = { WoodBox,GL_RGB,GL_RGB };
const static TextureParameters  Default_TextureFace = { SmileFace, GL_RGB,GL_RGBA };
const static TextureParameters  Default_TextureWall = { Wall,GL_RGB,GL_RGB };

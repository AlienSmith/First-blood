#pragma once
#include"Vector3.h"
#include"GLINCLUDE.h"
const static unsigned int SCR_WIDTH = 800;
const static unsigned int SCR_HEIGHT = 600;
//TODO Could add more details
const struct TextureParameters {
	const char* textureroute;
};
const struct ShaderParameters {
	const char* vs;
	const char* fs;
	//uniform
	const bool texture1 : 1;
	const bool texture2 : 1;
	const bool lighting : 1;
	const bool lightmapping : 1;//contain normal vector
};
//Postion and Texture position
const struct MeshParameters
{
	const int numelements;
	const int positionsize;
	const int texturesize;
	const int normalsize;
	const int TriangleIndex;
	const float* data;
};
const static float sprite[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
};
const static float spriteT[] = {
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
};
const static float spriteN[] = {
	-0.5f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,
	 0.5f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,
	 0.5f,  0.5f, 0.0f,   0.0f,0.0f,1.0f,
	 0.5f,  0.5f, 0.0f,   0.0f,0.0f,1.0f,
	-0.5f,  0.5f, 0.0f,   0.0f,0.0f,1.0f,
	-0.5f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,
};
const static float spriteTN[] = {
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,0.0f,1.0f,
	 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
	 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,
};
const static float NT_cubevertexs[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
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
//position texture|coordinate|normal vector
const static float cubevertexsn[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,-1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
};
const static float cubenormal[] = {
	-0.5f, -0.5f, -0.5f,   0.0f,0.0f,-1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,0.0f,-1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,0.0f,-1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,0.0f,-1.0f,

	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
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
const static char IronBox[] = "../GStar/IronBox.png";
const static char IronBox_Specular[] = "../GStar/IronBox_specular.png";
const static char SmileFace[] = "../GStar/awesomeface.png";
//these are shaders for 2d texture coordinate
const static char vs[] = "../GStar/VertexColor.ves";
const static char fs[] = "../GStar/VertexColor.frs";
//these shader do not support texture
const static char NT_vs[] = "../GStar/NTexture.ves";
const static char NT_fs[] = "../GStar/NTexture.frs";
//this is the fragment shader supports light;
const static char TL_fs[] = "../GStar/TLVertexColor.frs";
const static char TL_vs[] = "../GStar/TLVertexColor.ves";
//this for light mapping
const static char LM_fs[] = "../GStar/TextureMap.frs";
const static char LM_vs[] = "../GStar/TextureMap.ves";

// Shader
const static size_t ShadersHeapSize = 1024;
const static size_t SceneHeapSize = 32768;
const static MeshParameters spriteparameters = { 18,3,0,0,6,sprite };
const static MeshParameters spriteTparameters = { 30,3,2,0,6,spriteT };
const static MeshParameters spriteNparameters = { 36,3,0,3,6,spriteN };
const static MeshParameters spriteTNparameters = { 48,3,2,3,6,spriteTN };
const static MeshParameters cubeparameters = { 180,3,2,0,36,cubevertexs };
const static MeshParameters NT_cubeparameters = { 108,3,0,0,36,NT_cubevertexs };
const static MeshParameters texturenormalcubeparameters = {288,3,2,3,36,cubevertexsn};//??
const static MeshParameters normalcubeparameters = {216,3,3,0,36,cubenormal};
const static ShaderParameters DefaultShader2T = { vs,fs,true,true,false,false};
const static ShaderParameters Shader2L = { TL_vs,TL_fs,false,false,true,false};
const static ShaderParameters NT_Shaders = { NT_vs,NT_fs,false,false,false,false };
const static ShaderParameters LM_Shaders = { LM_vs,LM_fs,false,false,false,true};
const static TextureParameters Default_Texture_BOX = { WoodBox };
const static TextureParameters  Default_TextureFace = { SmileFace};
const static TextureParameters  Default_TextureWall = { Wall };
const static TextureParameters Default_Texture_Iron_Box = {IronBox};
const static TextureParameters Default_Diffuse_IronBox = { IronBox };
const static TextureParameters Default_Specular_IronBox = { IronBox_Specular };

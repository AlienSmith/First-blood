#include"Manager.h"
#include"SceneInterface.h"
#include"World.h"
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
#include"TransformComponent.h"
#include"InterfaceComponent.h"
#include"Data.h"
#include"CameraManager.h"
#include"LightManager.h"
#include"ConsolePrint.h"
#include"RManager.h"
#include"World.h"
#include"InterfaceComponentManager.h"
#include"TextureData.h"
#include"SimpleExample.h"
#include"Data.h"
#include"lua.hpp"
#include"Assert.h"
uint8_t * GStar::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{

	ASSERT(i_pFilename != NULL, "Load File fail, file name is null");

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	ASSERT(pFile != NULL,"Load File Fail");

	int FileIOError = fseek(pFile, 0, SEEK_END);
	ASSERT(FileIOError == 0, "Load File Fail");

	long FileSize = ftell(pFile);
	ASSERT(FileSize >= 0, "Load File Fail");

	FileIOError = fseek(pFile, 0, SEEK_SET);
	ASSERT(FileIOError == 0, "Load File Fail");

	uint8_t * pBuffer = new uint8_t[FileSize];
	ASSERT(pBuffer, "Load File Fail");

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	ASSERT(FileRead == FileSize, "Load File Fail");

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}
bool GStar::LoadObject(char * filename, size_t filesize, const InterfaceComponent* controller)
{
	lua_State* pLuaState = luaL_newstate();
	luaL_openlibs(pLuaState);

	uint8_t* pFileContents = LoadFile(filename, filesize);
	if (pFileContents && filesize) {
		int  result = 0;
		result = luaL_loadbuffer(pLuaState, reinterpret_cast<char*>(pFileContents), filesize, nullptr);
		ASSERT(result == 0, "Load buffer fail");
		result = lua_pcall(pLuaState, 0, 0, 0);
		ASSERT(result == 0, "Load buffer fail");
		lua_pushstring(pLuaState, "Version");
		lua_pushnil(pLuaState);
	}
	return true;
}
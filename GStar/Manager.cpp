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
bool GStar::LoadObject(const char * filename, const InterfaceComponent* controller)
{
	lua_State* pLuaState = luaL_newstate();
	luaL_openlibs(pLuaState);
	size_t filesize;
	uint8_t* pFileContents = LoadFile(filename, filesize);
	int  result = 0;
	result = luaL_loadbuffer(pLuaState, reinterpret_cast<char*>(pFileContents), filesize, nullptr);
	ASSERT(result == 0, "Load buffer fail");
	result = lua_pcall(pLuaState, 0, 0, 0);
	ASSERT(result == 0, "Load buffer fail");
	result = lua_getglobal(pLuaState, "Version");
	ASSERT(result == LUA_TSTRING,"Wrong DataType");
	const char* pVersion = lua_tostring(pLuaState, -1);
	if (pVersion) {
		pVersion = _strdup(pVersion);
	}
	lua_pop(pLuaState, 1);
	result = lua_getglobal(pLuaState, "Camera");
	ASSERT(result == LUA_TTABLE, "Wrong DataType");
	lua_len(pLuaState, -1);
	ASSERT(lua_type(pLuaState,-1)==LUA_TNUMBER, "Wrong DataType");
	lua_Integer table_entries = lua_tointeger(pLuaState, -1);
	lua_pop(pLuaState, 1);
	lua_pushstring(pLuaState, "name");
	int type = lua_gettable(pLuaState, -2);
	ASSERT(result == LUA_TSTRING, "Wrong DataType");
	const char* name = lua_tostring(pLuaState, -1);
	if (name) {
		name = _strdup(name);
	}
	lua_pop(pLuaState, 1);
	return true;
}
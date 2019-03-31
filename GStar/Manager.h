#pragma once
#include<stdint.h>
#include"lua.hpp"
namespace GStar {
	class InterfaceComponent;
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	bool LoadObject(const char* filename,const InterfaceComponent* controller);
	bool LoadFloatArray(const char* tablename,float* array, lua_State* i_pState, int size);
	bool GenerateObject(const char* name, float* position);
}
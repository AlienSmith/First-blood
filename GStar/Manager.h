#pragma once
#include<stdint.h>
namespace GStar {
	class InterfaceComponent;
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	bool LoadObject(const char* filename,const InterfaceComponent* controller);
}
#pragma once
#include<stdint.h>
namespace GStar {
	class InterfaceComponent;
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	bool LoadObject(char* filename, size_t filesize,const InterfaceComponent* controller);
}
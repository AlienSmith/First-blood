#include "TextureData.h"
#include "ConsolePrint.h"
#include <iostream>
#include <fstream>
//Files have the signature 
//nx ny r g b r g b ...
bool GStar::TextureData::readformfile(const GStar::MyString & string)
{
	return readformfile(string.GetString());
}

bool GStar::TextureData::writetofile(const GStar::MyString & string)
{
	return writetofile(string.GetString());
}

bool GStar::TextureData::readformfile(const char * string)
{
	std::ifstream myFile(string, std::ios::in | std::ios::binary);
	uint32_t nx, ny;
	if (!myFile.read(reinterpret_cast<char*>(&nx), sizeof(nx)))
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "Fail Read File %s", string);
	if (!myFile.read(reinterpret_cast<char*>(&ny), sizeof(ny)))
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "Fail Read File %s", string);
	this->my_data.x = nx;
	this->my_data.y = ny;
	uint8_t* data = new uint8_t((uint8_t)(nx*ny * 3));
	if (!myFile.read(reinterpret_cast<char*>(data), nx*ny * 3))
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "Fail Read File %s", string);
	this->my_data.data = data;
	myFile.close();
	return true;
}

bool GStar::TextureData::writetofile(const char * string)
{
	std::ofstream myFile;
	myFile.open(string, std::ios::out | std::ios::binary);
	uint32_t nx, ny;
	nx = this->my_data.x;
	ny = this->my_data.y;
	if (!myFile.write(reinterpret_cast<char*>(&nx), sizeof(nx)))
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "Fail Write File %s", string);
	if (!myFile.write(reinterpret_cast<char*>(&ny), sizeof(ny)))
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "Fail Write File %s", string);
	if (!myFile.write(reinterpret_cast<char*>(this->my_data.data), nx*ny * 3))
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "Fail Write File %s", string);
	myFile.close();
	return true;
}

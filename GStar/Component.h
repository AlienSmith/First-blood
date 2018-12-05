#pragma once
#define MESH_WORD 'm'
#define TEXTURE_WORD 't'
#define SHADER_WORD 's'
#define TRANSFORM_WORD 'a'
class Component {
public:
	//TODO if more efficient I could have a convert component for next object and update this object
	bool Initialize() { return true; }
	bool Update();
	bool Terminate() { return true; }
	Component(char tpe) :type(tpe) {}
	Component() {}
protected:
	char type;
};
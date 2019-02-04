#pragma once
#define MESH_WORD 'm'
#define TEXTURE_WORD 't'
#define SHADER_WORD 's'
#define UNDEFINED_WORD 'u'
#define TRANSFORM_WORD 'o'
#define INTERFACE_WORD 'i'
class Component {
public:
	//TODO add deltaTime to the update
	//TODO if more efficient I could have a convert component for next object and update this object
	bool Initialize() { return true; }
	bool Update();
	bool Terminate() { return true; }
	Component(char tpe) :type(tpe) {}
	Component():type(UNDEFINED_WORD) {}
	inline char GetType() const { return type; }
protected:
	char type;
};
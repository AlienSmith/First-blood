#pragma once
class Component {
public:
	bool Initialize() { return true; }
	bool Update() { return true; }
	bool Terminate() { return true; }
protected:
	char type;
};
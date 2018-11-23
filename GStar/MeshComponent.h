#pragma once
#include"Component.h"
class MeshComponent: public Component {
public:
	const static char TypeWord(){
		return 'm';
	}
	bool Initialize();
	bool Update();
	bool Terminate();
	MeshComponent() {
	
	}
};
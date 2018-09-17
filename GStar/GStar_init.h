#pragma once
namespace GStar {
	bool Initialize();
	bool Terminate();
	class Coordinate;
	Coordinate* world;
	Coordinate* object;
	Coordinate* camera;
}

#pragma once
#include "Vector3.h"
namespace GStar {
		struct TextureData;
		class Ray;
		class Sphere;
		class Hitable;
}
class SimpleExample {
public:
	static GStar::TextureData* getdata();
	static GStar::Vector3 color(const GStar::Ray& ray,const GStar::Hitable& sphere, int depth);
	static GStar::Vector3 random_in_unit_sphere();
	static float UnitRandom();
	static float Random();
};
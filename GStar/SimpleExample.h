#pragma once
#include "Vector3.h"
namespace GStar {
		struct TextureData;
		class Ray;
		class Sphere;
}
class SimpleExample {
public:
	static GStar::TextureData* getdata();
	static GStar::Vector3 color(const GStar::Ray& ray,const GStar::Sphere& sphere);
};
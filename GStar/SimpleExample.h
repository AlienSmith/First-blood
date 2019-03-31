#pragma once
#include "Vector3.h"
#include <mutex>
namespace GStar {
		struct TextureData;
		class Ray;
		class Sphere;
		class Hitable;
		class TRCamera;
}
class SimpleExample {
public:
	static std::mutex mtx;
	static GStar::TextureData* getdata();
	static GStar::Vector3 color(const GStar::Ray& ray,const GStar::Hitable& sphere, int depth);
	static GStar::Vector3 random_in_unit_sphere();
	static float UnitRandom();
	static float Random();
	static GStar::Hitable* random_scene();
	static GStar::Hitable* Glass_scene();
	static void CalculationBlock(int start, int end,int nx,int ns,const GStar::TRCamera& cam, GStar::Hitable* world, uint8_t* data);
};
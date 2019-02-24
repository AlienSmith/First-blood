#include "SimpleExample.h"
#include "TextureData.h"
#include "Ray.h"
#include "Sphere.h"
#include "hitable_list.h"
#include "TRCamera.h"
#include <iostream>
#include <random>
#include <chrono>
#include "ConsolePrint.h"
#include "material.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 200;
	int ns = 100;
	GStar::Hitable * list[5];
	list[0] = new GStar::Sphere(GStar::Vector3(0, 0, -1), .5f,new GStar::lambertian(GStar::Vector3(.1f,.2f,.5f)));
	list[1] = new GStar::Sphere(GStar::Vector3(0.0f, -100.5f, -1.0f),100.0f, new GStar::lambertian(GStar::Vector3(.8f, .8f, .0f)));
	list[2] = new GStar::Sphere(GStar::Vector3(1, 0, -1), .5f, new GStar::dielectric(1.5f));
	list[3] = new GStar::Sphere(GStar::Vector3(-1, 0, -1), .5f, new GStar::dielectric(1.5f));
	list[4] = new GStar::Sphere(GStar::Vector3(-1, 0, -1), -.45f, new GStar::dielectric(1.5f));
	GStar::Hitable * world = new GStar::hitable_list(list,5);
	GStar::TRCamera cam;
	uint8_t data[200*200* 3];
	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			GStar::Vector3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + Random()) / float(nx);
				float v = float(j + Random()) / float(ny);
				GStar::Ray r = cam.get_ray(u, v);
				col += color(r, *world,0);
			}
			col /= float(ns);
			col = GStar::Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			data[(j * 200 + i) * 3] = int(255.99*col[0]);
			data[(j * 200 + i) * 3 + 1] = int(255.99*col[1]);
			data[(j * 200 + i) * 3 + 2] = int(255.99*col[2]);
		}
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Generating RayTracing Map %f ", float(j * 100 / ny));
	}
	GStar::TextureData* texture = new GStar::TextureData(data, 200, 200);
	for (int i = 0; i < 5; i++) {
		delete list[i];
	}
	delete world;
	return texture;
}

GStar::Vector3 SimpleExample::color(const GStar::Ray & ray, const GStar::Hitable & hitable, int depth)
{
	GStar::hit_record rec;
	if (hitable.hit(ray, 0.001f, 1000, rec)) {
		GStar::Ray scattered;
		GStar::Vector3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(ray, rec, attenuation, scattered)) {
			return attenuation * color(scattered, hitable, depth + 1);
		}
		else {
			//The back ground is black
			return GStar::Vector3(0, 0, 0);
		}
	}
	else {
		GStar::Vector3 unit_direction = ray.getValue().direction;
		float t = .5f*(unit_direction[1] + 1.0);
		return (1.0f - t)*GStar::Vector3(1, 1, 1) + t*GStar::Vector3(.5f, .7f, 1.0f);
	}
}
GStar::Vector3 SimpleExample::random_in_unit_sphere()
{
	GStar::Vector3 p;
	do {
		p = (2.0f*GStar::Vector3(Random(), Random(), Random())) - GStar::Vector3(1,1,1);
	} while (p.Dot(p) >= 1.0f);
	return p;
}
// 0(inclusive) to 1 (exclusive)
float SimpleExample::UnitRandom() {
	std::mt19937_64 rng;
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	// initialize a uniform distribution between 0 and 1
	std::uniform_real_distribution<double> unif(0, 1);
	return unif(rng);
}
float SimpleExample::Random() {
	return ((float)rand() / (RAND_MAX));
}

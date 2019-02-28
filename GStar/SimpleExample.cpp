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
#include "Schlick.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 200;
	int ns = 100;
	constexpr int hitables = 5;
	/*GStar::Hitable * list[hitables];
	list[0] = new GStar::Sphere(GStar::Vector3(0, 0, -1), .5f,new GStar::lambertian(GStar::Vector3(.1f,.2f,.5f)));
	list[1] = new GStar::Sphere(GStar::Vector3(0.0f, -100.5f, -1.0f),100.0f, new GStar::lambertian(GStar::Vector3(.8f, .8f, .0f)));
	list[2] = new GStar::Sphere(GStar::Vector3(1, 0, -1), .5f, new GStar::metal(GStar::Vector3(.8f,.6f,.2f),.3f));
	list[3] = new GStar::Sphere(GStar::Vector3(-1, 0, -1), .5f, new GStar::dielectric(1.5f));
	list[4] = new GStar::Sphere(GStar::Vector3(-1, 0, -1), -.45f, new GStar::dielectric(1.5f));*/
	GStar::Hitable * world = Glass_scene();
	GStar::Vector3 lookfrom(3, 3, 2);
	GStar::Vector3 lookat(0, 0, -1);
	float dist_focus = (lookfrom - lookat).Length();
	float apeture = 2.0f;
	GStar::TRCamera cam(lookfrom, lookat,GStar::Vector3(0,1,0),40,nx/ny,apeture,dist_focus);
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
	delete world;
	return texture;
}

GStar::Vector3 SimpleExample::color(const GStar::Ray & ray, const GStar::Hitable & hitable, int depth)
{
	GStar::hit_record rec;
	if (hitable.hit(ray, 0.001f, GStar::MAXFLOAT, rec)) {
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
		float t = .5f*(unit_direction[1] + 1.0f);
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

GStar::Hitable * SimpleExample::random_scene()
{
	using namespace GStar;
	constexpr int n = 500;
	Hitable** list = new Hitable*[n];
	list[0] = new Sphere(Vector3(0, -1000, 0), 1000, new lambertian(Vector3(.5f, .5f, .5f)));
	int i = 0;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = Random();
			Vector3 center(a + .9f*Random(), .2f, .9f*Random());
			if ((center - Vector3(4, .2, 0)).Length() > .9) {
				if (choose_mat < .8) {
					list[i++] = new Sphere(center, .2f, new lambertian(Vector3(Random()*Random(), Random()*Random(), Random()*Random())));
				}
				else if (choose_mat < .95) {
					list[i++] = new Sphere(center, .2f, new metal(
						Vector3(.5f*(1.0f + Random()), .5f*(1.0f + Random()), .5f*(1.0f + Random())), .5f*(1.0f + Random())));
				}
				else {
					list[i++] = new Sphere(center, .2f, new dielectric(1.5f));
				}
			}
		}
	}
	list[i++] = new Sphere(Vector3(0, 1, 0), 1.0f, new dielectric(1.5f));
	list[i++] = new Sphere(Vector3(-4,1,0),1.0f,new lambertian(Vector3(.4f,.2f,.1f)));
	list[i++] = new Sphere(Vector3(4, 1, 0), 1.0f, new metal(Vector3(.7f, .6f, .5f), 0.0f));
	return new hitable_list(list,i);
}

GStar::Hitable * SimpleExample::Glass_scene()
{
	int hitables = 5;
	GStar::Hitable ** list = new GStar::Hitable*[hitables];
	list[0] = new GStar::Sphere(GStar::Vector3(0, 0, -1), .5f, new GStar::lambertian(GStar::Vector3(.1f, .2f, .5f)));
	list[1] = new GStar::Sphere(GStar::Vector3(0.0f, -100.5f, -1.0f), 100.0f, new GStar::lambertian(GStar::Vector3(.8f, .8f, .0f)));
	list[2] = new GStar::Sphere(GStar::Vector3(1, 0, -1), .5f, new GStar::metal(GStar::Vector3(.8f, .6f, .2f), .3f));
	list[3] = new GStar::Sphere(GStar::Vector3(-1, 0, -1), .5f, new GStar::dielectric(1.5f));
	list[4] = new GStar::Sphere(GStar::Vector3(-1, 0, -1), -.45f, new GStar::dielectric(1.5f));
	return new GStar::hitable_list(list, hitables);
}

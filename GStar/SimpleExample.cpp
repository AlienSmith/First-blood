#include "SimpleExample.h"
#include "TextureData.h"
#include "Ray.h"
#include "Sphere.h"
#include "hitable_list.h"
#include "TRCamera.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 200;
	GStar::Vector3 lower_left_corner(-1.0f, -1.0f, -1.0f);
	GStar::Vector3 horizontal(2.0f, 0.0f, 0.0f);
	GStar::Vector3 vertical(0.0f, 2.0f, 0.0f);
	GStar::Vector3 origin(0.0f, 0.0f, 0.0f);
	GStar::Hitable * list[2];
	list[0] = new GStar::Sphere(GStar::Vector3(0, 0, -1), .5);
	list[1] = new GStar::Sphere(GStar::Vector3(0, -100, -10), 100);
	GStar::Hitable * world = new GStar::hitable_list(list,2);
	GStar::TRCamera cam;
	uint8_t data[200*200* 3];
	GStar::Sphere sphere(GStar::Vector3(0, 0, -1), .5);
	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			GStar::Ray r = cam.get_ray(u, v);
			//GStar::Ray r(origin, GStar::Vector3( 0.0f,0.0f,-1.0f));
			GStar::Vector3 col = color(r,(*world));
			data[(i * 200 + j)*3] = 255 * col[0];
			data[(i * 200 + j) * 3 + 1] = 255 * col[1];
			data[(i * 200 + j) * 3 + 2] = 255 * col[2];
		}
	}
	GStar::TextureData* texture = new GStar::TextureData(data, 200, 200);
	delete list[0];
	delete list[1];
	delete world;
	return texture;
}

GStar::Vector3 SimpleExample::color(const GStar::Ray & ray, const GStar::Hitable & hitable)
{
	GStar::hit_record rec;
	if (hitable.hit(ray, 0.0f, 1000.0f, rec)) {
		return .5f* (GStar::Vector3(1, 1, 1) + rec.n);
	}
	GStar::RayData data = ray.getValue();
	float t = .5*(data.direction.y() + 1.0);
	return ((float)(1.0 - t))*GStar::Vector3(1, 1, 1) + ((float)t)*GStar::Vector3(.5f, .7f, 1.0f);
}


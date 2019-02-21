#include "SimpleExample.h"
#include "TextureData.h"
#include "Ray.h"
#include "Sphere.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 200;
	GStar::Vector3 lower_left_corner(-1.0f, -1.0f, -1.0f);
	GStar::Vector3 horizontal(2.0f, 0.0f, 0.0f);
	GStar::Vector3 vertical(0.0f, 2.0f, 0.0f);
	GStar::Vector3 origin(0.0f, 0.0f, 0.0f);
	uint8_t data[200*200* 3];
	GStar::Sphere sphere(GStar::Vector3(0, 0, -1), .5);
	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			GStar::Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			//GStar::Ray r(origin, GStar::Vector3( 0.0f,0.0f,-1.0f));
			GStar::Vector3 col = color(r,sphere);
			data[(i * 200 + j)*3] = 255 * col[0];
			data[(i * 200 + j) * 3 + 1] = 255 * col[1];
			data[(i * 200 + j) * 3 + 2] = 255 * col[2];
		}
	}
	GStar::TextureData* texture = new GStar::TextureData(data, 200, 200);
	return texture;

}

GStar::Vector3 SimpleExample::color(const GStar::Ray & ray, const GStar::Sphere& sphere)
{
	GStar::hit_record rec;
	if (sphere.hit(ray,0.0f,1000.0f,rec)) {
		GStar::Vector3 N = ray.point_at_parameter(rec.t) - GStar::Vector3(0, 0, -1);
		N.Normalize();
		return .5f* GStar::Vector3(N[0] +1, N[1]+1, N[2]+1);
	}
	GStar::RayData data = ray.getValue();
	float t = .5*(data.direction.y() + 1.0);
	return ((float)(1.0 - t))*GStar::Vector3(1,1,1) + ((float)t)*GStar::Vector3(.5f,.7f,1.0f);
}

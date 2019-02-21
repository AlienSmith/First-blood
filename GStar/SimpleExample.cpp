#include "SimpleExample.h"
#include "TextureData.h"
#include "Ray.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 200;
	GStar::Vector3 lower_left_corner(-1.0f, -1.0f, -1.0f);
	GStar::Vector3 horizontal(2.0f, 0.0f, 0.0f);
	GStar::Vector3 vertical(0.0f, 2.0f, 0.0f);
	GStar::Vector3 origin(0.0f, 0.0f, 0.0f);
	uint8_t data[200*200* 3];
	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			GStar::Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			GStar::Vector3 col = color(r);
			data[(i * 200 + j)*3] = 255 * col[0];
			data[(i * 200 + j) * 3 + 1] = 255 * col[1];
			data[(i * 200 + j) * 3 + 2] = 255 * col[2];
		}
	}
	GStar::TextureData* texture = new GStar::TextureData(data, 200, 200);
	return texture;

}

GStar::Vector3 SimpleExample::color(const GStar::Ray & ray)
{
	GStar::RayData data = ray.getValue();
	float t = .5*(data.direction.y() + 1.0);
	return ((float)(1.0 - t))*GStar::Vector3(1,1,1) + ((float)t)*GStar::Vector3(.5f,.7f,1.0f);
}

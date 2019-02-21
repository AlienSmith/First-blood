#include "SimpleExample.h"
#include "TextureData.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 100;
	uint8_t data[200*100* 4];
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 100; j++) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			data[(i * 100 + j)*4] = 255 * r;
			data[(i * 100 + j) * 4 + 1] = 255 * g;
			data[(i * 100 + j) * 4 + 2] = 255 * b;
			data[(i * 100 + j) * 4 + 3] = 255;
		}
	}
	GStar::TextureData* texture = new GStar::TextureData(data, 200, 100);
	return texture;

}

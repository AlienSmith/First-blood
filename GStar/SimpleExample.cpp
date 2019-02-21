#include "SimpleExample.h"
#include "TextureData.h"
#include "Vector3.h"
GStar::TextureData * SimpleExample::getdata()
{
	int nx = 200;
	int ny = 200;
	uint8_t data[200*200* 3];
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			GStar::Vector3 col(float(i) / float(nx), float(j) / float(nx), .2);
			data[(i * 200 + j)*3] = 255 * col[0];
			data[(i * 200 + j) * 3 + 1] = 255 * col[1];
			data[(i * 200 + j) * 3 + 2] = 255 * col[2];
		}
	}
	GStar::TextureData* texture = new GStar::TextureData(data, 200, 200);
	return texture;

}

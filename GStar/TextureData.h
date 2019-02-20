#pragma once
#include <stdlib.h>
namespace GStar {
	struct texturedata {
		float* data;
		int x;
		int y;
	};
	class TextureData {
	public:
		TextureData(float* data, int x, int y) :my_data({ data,x,y }){}
		TextureData() :my_data({nullptr,0,0}) {}
		TextureData(const TextureData& other) :my_data({ nullptr,0,0 }) {
			my_data.data = Copy(other.my_data.data, other.my_data.x, other.my_data.y);
		}
		TextureData& operator=(const TextureData& other) {
			if (&other == this) {
				return *this;
			}
			if (my_data.data) {
				delete my_data.data;
			}
			my_data.x = other.my_data.x;
			my_data.y = other.my_data.y;
			my_data.data = Copy(other.my_data.data, other.my_data.x, other.my_data.y);
		}
		~TextureData() {
			if (my_data.data) {
				delete my_data.data;
			}
		}
		const texturedata& getData() const{ return my_data; }
	private:
		float* Copy(const float* const data, int x, int y) {
			float* new_data = (float*)malloc(sizeof(float)*x*y);
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					new_data[i*j + j] = data[i*j + j];
				}
			}
			return new_data;
		}
		texturedata my_data;
	};
}
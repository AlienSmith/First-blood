#pragma once
#include <stdlib.h>
#include <stdint.h>
#include "MyString.h"
namespace GStar {
	struct texturedata {
		uint8_t* data;
		int x;
		int y;
	};
	class TextureData {
	public:
		TextureData(uint8_t* data, int x, int y) :my_data({ nullptr,x,y }){
			my_data.data = Copy(data, x, y);
		}
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
		bool readformfile(const GStar::MyString& string);
		bool writetofile(const GStar::MyString& string);
		bool readformfile(const char* string);
		bool writetofile(const char* string);
	private:
		uint8_t* Copy(const uint8_t* const data, int x, int y) {
			uint8_t* new_data = new uint8_t(x*y*3);
			for (int i = 0; i < x*y * 3; i++) {
				new_data[i] = data[i];
			}
			return new_data;
		}
		texturedata my_data;
	};
}
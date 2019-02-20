#pragma once
#include<iostream>
#include<fstream>
#include"MyString.h"
namespace GStar {
	class TextureWriter {
	public:
		static TextureWriter* Create(const MyString& file){
			if (instance->my_stream.is_open()) {
				instance->my_stream.close();
			}
			instance->my_stream.open(file.GetString());
			return instance;
		}
		void WriteALine(const MyString& data) {
			instance->my_stream << (data.GetString());
			instance->my_stream << "\n";
		}
		void Terminate() {
			my_stream.close();
		}
	private:
		static TextureWriter* instance;
		std::ofstream my_stream;
	};
	class TextureReader {
	public:
		static TextureReader* Create(const MyString& file) {
			if (instance->my_stream.is_open()) {
				instance->my_stream.close();
			}
			instance->my_stream.open(file.GetString());
			return instance;
		}
		void ReadTexture(const MyString& data) {
			
		}
		void Terminate() {
			my_stream.close();
		}
	private:
		static TextureReader* instance;
		std::ifstream my_stream;
	};
}
#pragma once
#include "GLError.h"
#include"GLINCLUDE.h"
#include"MyString.h"
#include"ConsolePrint.h"
#if defined(_DEBUG)
void _check_gl_error(const char *file, int line) {
	GLenum err(glGetError());

	while (err != GL_NO_ERROR) {
		GStar::MyString error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "%s at %s line %d\n", error.GetString(),file,line);
	}
}
#endif
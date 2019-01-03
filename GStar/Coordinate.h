#pragma once
#ifndef COORDINATE_H
#define COORDINATE_H
#include "Matrix4.h"
#include "math.h"
#include "Vector3.h"
#define PI 3.14159265
#include "ConsolePrint.h"
namespace GStar {
	inline static float radians(float angle) { return angle * PI / 180.0; };
	static GStar::Matrix4 Transform(Matrix4& offset,float x, float y, float z);
	static GStar::Matrix4 Scale(Matrix4& offset, float x, float y, float z);
	static GStar::Matrix4 Rotate(Matrix4& offset,float roll, float pitch, float yaw);
	static GStar::Matrix4 Rotate(Matrix4 & offset, float degree, GStar::Vector3 direction);
	static GStar::Matrix4 perspective(Matrix4& offset, float horangle, float widthbyheight, float nsize, float fsize);
	inline GStar::Matrix4 orthogrphic(Matrix4& offset, float horangle, float widthbyheight, float nsize, float fsize);
	class Coordinate
	{
	public:
		enum TYPE
		{
			WORLD,
			CAMERA,
			OBJECT
		};
		Coordinate(TYPE objecttype);
		Coordinate(TYPE objecttype,Matrix4& offset);
		~Coordinate();
		void Rotate(float roll, float pitch, float yaw);
		void move(float x, float y, float z);
		Vector3 Apply(Vector3& object);
		Vector3 Reverse(Vector3& object);
	private:
		TYPE mytype;
		Matrix4 worldTothis;
	};

	inline Coordinate::Coordinate(TYPE objecttype)
	{
		this->mytype = objecttype;
		worldTothis = Matrix4(IDENTICAL_MATRIX);
	}

	inline Coordinate::Coordinate(TYPE objecttype, Matrix4& offset)
	{
		this->mytype = objecttype;
		this->worldTothis = Matrix4(IDENTICAL_MATRIX);
	}

	inline Coordinate::~Coordinate()
	{
	}
	// rotate counterclock wise with the axis point to you
	inline void Coordinate::Rotate(float roll, float pitch, float yaw)
	{
		array_ff temp = IDENTICAL_MATRIX;
		float sx = sin(roll*PI/180);
		float sy = sin(pitch*PI / 180);
		float sz = sin(yaw*PI / 180);
		float cx = cos(roll*PI / 180);
		float cy = cos(pitch*PI / 180);
		float cz = cos(yaw*PI / 180);

		temp[0][0] = cz * cy - sz * sx*sy;
		temp[0][1] = -sz*cx;
		temp[0][2] = sy * cz + sz * sx*cy;
		temp[1][0] = sz * cy + cz * sx*sy;
		temp[1][1] = cz*cx;
		temp[1][2] = sz * sy - cz * sx*cy;
		temp[2][0] = -cx * sy;
		temp[2][1] = sx;
		temp[2][2] = cx * cy;
		Matrix4 tempmatrix = this->worldTothis.Dot(Matrix4(temp));

		this->worldTothis = tempmatrix;
	}

	/*inline void Coordinate::move(float x, float y, float z)
	{
		array_ff temp = IDENTICAL_MATRIX;
		temp[0][3] = x;
		temp[1][3] = y;
		temp[2][3] = z;
		Matrix4 tempmatrix = this->worldTothis.Dot(Matrix4(temp));
		this->worldTothis = tempmatrix;

	}*/

	/*inline Vector3 Coordinate::Apply(Vector3 & object)
	{

		return this->worldTothis*object;
	}

	inline Vector3 Coordinate::Reverse(Vector3 & object)
	{
		return this->worldTothis.I()*object;
	}*/

	//TODO add a move constructor and operator for Matrix4
	//TODO add rotation arround a Axies
	inline GStar::Matrix4 GStar::Transform(Matrix4& offset,float x, float y, float z)
	{
		array_ff temp = IDENTICAL_MATRIX;
		temp[0][3] = x;
		temp[1][3] = y;
		temp[2][3] = z;
		Matrix4 tempmatrix = Matrix4(temp);
		tempmatrix = offset.Dot(tempmatrix);
		return tempmatrix;
	}
	inline GStar::Matrix4 Scale(Matrix4 & offset, float x, float y, float z)
	{
		array_ff temp = IDENTICAL_MATRIX;
		temp[0][0] = x;
		temp[1][1] = y;
		temp[2][2] = z;
		Matrix4 tempmatrix = GStar::Matrix4(temp);
		tempmatrix = offset.Dot(tempmatrix);
		return tempmatrix;
	}
	inline GStar::Matrix4 Rotate(Matrix4& offset,float roll, float pitch, float yaw)
	{
		//This implementation follows the order of zxy
		array_ff temp = IDENTICAL_MATRIX;
		float sx = sin(roll*PI / 180);
		float sy = sin(pitch*PI / 180);
		float sz = sin(yaw*PI / 180);
		float cx = cos(roll*PI / 180);
		float cy = cos(pitch*PI / 180);
		float cz = cos(yaw*PI / 180);
		//DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "sx %f, sy %f, sz %f", sx, sy, sz);
		temp[0][0] = cz * cy - sz * sx*sy;
		temp[0][1] = -sz * cx;
		temp[0][2] = sy * cz + sz * sx*cy;
		temp[1][0] = sz * cy + cz * sx*sy;
		temp[1][1] = cz * cx;
		temp[1][2] = sz * sy - cz * sx*cy;
		temp[2][0] = -cx * sy;
		temp[2][1] = sx;
		temp[2][2] = cx * cy;
		Matrix4 tempmatrix = GStar::Matrix4(temp);
		tempmatrix = offset.Dot(tempmatrix);
		return tempmatrix;
	}
	GStar::Matrix4 Rotate(Matrix4 & offset, float degree, GStar::Vector3 direction)
	{
		direction.Normalize();
		float s = sin(degree*PI / 180);
		float c = cos(degree*PI / 180);
		float x = direction.x();
		float y = direction.y();
		float z = direction.z();
		array_ff temp = IDENTICAL_MATRIX;
		temp[0][0] = c + (1 - c)*x*x;
		temp[0][1] = (1 - c)*x*y - s * z;
		temp[0][2] = (1 - c)*x*z + s * y;
		temp[1][0] = (1 - c)*x*y + s * z;
		temp[1][1] = c + (1 - c)*y*y;
		temp[1][2] = (1 - c)*y*z - s * x;
		temp[2][0] = (1 - c)*x*z - s * y;
		temp[2][1] = (1 - c)*y*z + s * x;
		temp[2][2] = c + (1 - c)*z*z;
		Matrix4 tempmatrix = GStar::Matrix4(temp);
		tempmatrix = offset.Dot(tempmatrix);
		return tempmatrix;
	}
	inline GStar::Matrix4 perspective(Matrix4& offset, float horangle, float widthbyheight, float nsize, float fsize)
	{
		float value = tan(horangle*PI / 360);
		float width = 2*nsize*value;
		float height = width / widthbyheight;

		array_ff temp = IDENTICAL_MATRIX;
		temp[0][0] = 2 * nsize / width;
		//temp[0][2] = 0;
		temp[1][1] = 2 * nsize / height;
		//temp[1][2] = 0;
		temp[2][2] = (fsize+nsize)/(nsize-fsize);
		temp[2][3] = (2 * nsize*fsize)/ (nsize - fsize);
		temp[3][2] = -1;
		temp[3][3] =  0;
		Matrix4 tempmatrix = GStar::Matrix4(temp);
		tempmatrix = offset.Dot(tempmatrix);
		return tempmatrix;
	}

	GStar::Matrix4 orthogrphic(Matrix4 & offset, float horangle, float widthbyheight, float nsize, float fsize)
	{
		float value = tan(horangle*PI / 360);
		float width = 2 * nsize*value;
		float height = width / widthbyheight;

		array_ff temp = IDENTICAL_MATRIX;
		temp[0][0] = 2 * nsize / width;
		//temp[0][2] = 0;
		temp[1][1] = 2 * nsize / height;
		//temp[1][2] = 0;
		temp[2][2] = 2 / (nsize - fsize);
		temp[2][3] = (nsize+fsize) / (nsize - fsize);
		temp[3][3] = 1;
		Matrix4 tempmatrix = GStar::Matrix4(temp);
		tempmatrix = offset.Dot(tempmatrix);
		return tempmatrix;
	}

}
#endif // ! COORDINATE_H

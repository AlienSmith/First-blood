#pragma once
#ifndef COORDINATE_H
#define COORDINATE_H
#include "Matrix4.h"
#include "math.h"
namespace GStar {
	//right hand coordinate
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
		float sx = sin(roll);
		float sy = sin(pitch);
		float sz = sin(yaw);
		float cx = cos(roll);
		float cy = cos(pitch);
		float cz = cos(yaw);
		temp[0][0] = cz * cy - sz * sx*sy;
		temp[0][1] = -sz*cx;
		temp[0][2] = sy * cz + sz * sx*cy;
		temp[1][0] = sz * cy + cz * sx*sy;
		temp[1][1] = cz*cx;
		temp[1][2] = sz * sy - cz * sx*cy;
		temp[2][0] = -cx * sy;
		temp[2][1] = sx;
		temp[2][3] = cx * cy;
		Matrix4 tempmatrix = Matrix4(temp);
		this->worldTothis *= tempmatrix;
	}

	inline void Coordinate::move(float x, float y, float z)
	{
		array_ff temp = IDENTICAL_MATRIX;
		temp[0][3] = x;
		temp[1][3] = y;
		temp[2][3] = z;
		Matrix4 tempmatrix = Matrix4(temp);
		this->worldTothis = tempmatrix;

	}

	inline Vector3 Coordinate::Apply(Vector3 & object)
	{
		return this->worldTothis*object;
	}

}
#endif // ! COORDINATE_H

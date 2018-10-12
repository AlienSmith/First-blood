#pragma once
#include <Vector>
#include "Assert.h"
#include "Vector3.h"
#ifndef MATRIX4
#define MATRIX4
#define out
#define SIZE 4
#define ZERO_MATRIX { {0,0,0,0},{0, 0, 0, 0},{ 0,0,0,0 },{ 0,0,0,0 }, }
#define IDENTICAL_MATRIX { {1,0,0,0},{0, 1, 0, 0},{ 0,0,1,0 },{ 0,0,0,1 }, }
typedef float array_ff[SIZE][SIZE]; 
typedef float array_f[SIZE*SIZE];
namespace GStar {
	class Matrix4;
	std::vector<Matrix4*>* tempresultpool;
	inline Matrix4& AddPool(array_ff& rdata);
	inline void CleanPool();
	//Plase do not contain constructor in equations.
	//Constructor with parameters and = += *= -= /=  will clean the temperary data
	//function return a reference of Matrix4 will add entries to the temperary data
	class Matrix4
	{
	public:
		static void value_ptr(const Matrix4 & matrix, array_f & temparray);
		Matrix4();
		~Matrix4();
		Matrix4(const array_ff & rdata);
		void Copy(const array_ff & rdata);
		//TODO do I need to make this nonconst
		const array_ff& Get() const;
		void operator = (const Matrix4& A);
		void operator += (const Matrix4& A);
		void operator -= (const Matrix4& A);
		void operator *= (const Matrix4& A);
		void operator /= (const Matrix4& A);
		void operator = (float A);
		void operator += (float A);
		void operator -= (float A);
		void operator *= (float A);
		void operator /= (float A);
		void Dot(const Matrix4& B, Matrix4& out result) const;
		Matrix4& Dot(const Matrix4& B)const;
		Matrix4& T() const;
		Matrix4& I()const;
		float determinant() const;
		float determinantc() const;
	private:
		array_ff data = ZERO_MATRIX;
		float C(float x, float y) const;
	};
	inline GStar::Matrix4& GStar::AddPool(array_ff& rdata) {
		if (GStar::tempresultpool == nullptr) {
			GStar::tempresultpool = new std::vector<Matrix4*>();
		}
		Matrix4* p_temp = new Matrix4(rdata);
		Matrix4& temp = *p_temp;
		GStar::tempresultpool->push_back(p_temp);
		return temp;
	}
	inline void GStar::CleanPool() {
		if (GStar::tempresultpool != nullptr) {
			for (Matrix4* pointer : *GStar::tempresultpool) {
				delete(pointer);
			}
			delete(GStar::tempresultpool);
			GStar::tempresultpool = nullptr;
		}
	}
	// Matrix to Matrix = += -= *= /= 
	inline void Matrix4::operator=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] = TA[i][j];
			}
		}
		GStar::CleanPool();
	}
	inline void Matrix4::operator+=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] += TA[i][j];
			}
		}
		GStar::CleanPool();
	}
	inline void Matrix4::operator-=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] -= TA[i][j];
			}
		}
		GStar::CleanPool();
	}
	inline void Matrix4::operator*=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] *= TA[i][j];
			}
		}
		GStar::CleanPool();
	}
	inline void Matrix4::operator/=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] /= TA[i][j];
			}
		}
		GStar::CleanPool();
	}

	//Matrix to float = += -= *= /=
	inline void Matrix4::operator=(float A)
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] = A;
			}
		}
	}
	inline void Matrix4::operator +=(float A)
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] += A;
			}
		}
	}
	inline void Matrix4::operator *=(float A)
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] *= A;
			}
		}
	}
	inline void Matrix4::operator -=(float A)
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] -= A;
			}
		}
	}
	inline void Matrix4::operator /=(float A)
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] /= A;
			}
		}
	}
	// multiply a matrix with a vector3
	inline Vector3 operator* (Matrix4& trans, Vector3& ve) {
		const array_ff& temp = trans.Get();
		float tempvector[4] = {0,0,0,0};
		tempvector[0] = ve.x();
		tempvector[1] = ve.y();
		tempvector[2] = ve.z();
		tempvector[3] = 1;
		float result[4] = { 0,0,0,0 };
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				result[i] += temp[i][j]*tempvector[j];
			}
		}
		return Vector3(result[0], result[1], result[2]);
	}
	//return the matrix product between two matrics
	inline void Matrix4::Dot(const Matrix4 & B, Matrix4& out matrix3) const
	{
		array_ff temp = ZERO_MATRIX;
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				for (int m = 0; m < SIZE; m++) {
					temp[i][j] += this->data[i][m] * TB[m][j];
				}
			}
		}
		matrix3.Copy(temp);
	}

	//Mathmatic implementation of Dot
	inline Matrix4& Matrix4::Dot(const Matrix4& B) const
	{
		array_ff temp = ZERO_MATRIX;
		array_ff& temp1 = temp;
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				for (int m = 0; m < SIZE; m++) {
					temp[i][j] += this->data[i][m] * TB[m][j];
				}
			}
		}
		return AddPool(temp);
	}

	// POOL Mathmatic transpose of matrix 
	inline Matrix4 & Matrix4::T() const
	{
		array_ff temp = ZERO_MATRIX;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[j][i] = this->data[i][j];
			}
		}
		return GStar::AddPool(temp);
	}

	//Mathmatic inverse of matrix
	inline Matrix4 & Matrix4::I() const
	{
		array_ff temp = ZERO_MATRIX;
		float deteminate = this->determinantc();
		ASSERT(deteminate != 0, "The Matrix do not have a reverse");
		Matrix4& transpose = this->T();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = transpose.C(i, j) / deteminate;
			}
		}

			return GStar::AddPool(temp);
	}
	//Mathmatic determinant of a 3*3 matrix cut from the original matirx
	inline float Matrix4::C(float x, float y) const
	{
		int tempflag = x + y;
		if (tempflag % 2 == 0) {
			tempflag = 1;
		}
		else
		{
			tempflag = -1;
		}
		float temp[9];
		int count = 0;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (i != x && j != y) {
					temp[count] = data[i][j];
					count++;
				}
			}
		}
		float temp1 = temp[0] * (temp[4] * temp[8] - temp[5] * temp[7]);
		float temp2 = temp[1] * (temp[3] * temp[8] - temp[5] * temp[6]);
		float temp3 = temp[2] * (temp[3] * temp[7] - temp[4] * temp[6]);
		return tempflag*(temp1 - temp2 + temp3);
	}

	inline float Matrix4::determinant() const
	{
		return data[0][ 3] * data[1][ 2] * data[2][ 1] * data[3][ 0] - data[0][ 2] * data[1][ 3] * data[2][ 1] * data[3][ 0] -
			data[0][ 3] * data[1][ 1] * data[2][ 2] * data[3][ 0] + data[0][ 1] * data[1][ 3] * data[2][ 2] * data[3][ 0] +
			data[0][ 2] * data[1][ 1] * data[2][ 3] * data[3][ 0] - data[0][ 1] * data[1][ 2] * data[2][ 3] * data[3][ 0] -
			data[0][ 3] * data[1][ 2] * data[2][ 0] * data[3][ 1] + data[0][ 2] * data[1][ 3] * data[2][ 0] * data[3][ 1] +
			data[0][ 3] * data[1][ 0] * data[2][ 2] * data[3][ 1] - data[0][ 0] * data[1][ 3] * data[2][ 2] * data[3][ 1] -
			data[0][ 2] * data[1][ 0] * data[2][ 3] * data[3][ 1] + data[0][ 0] * data[1][ 2] * data[2][ 3] * data[3][ 1] +
			data[0][ 3] * data[1][ 1] * data[2][ 0] * data[3][ 2] - data[0][ 1] * data[1][ 3] * data[2][ 0] * data[3][ 2] -
			data[0][ 3] * data[1][ 0] * data[2][ 1] * data[3][ 2] + data[0][ 0] * data[1][ 3] * data[2][ 1] * data[3][ 2] +
			data[0][ 1] * data[1][ 0] * data[2][ 3] * data[3][ 2] - data[0][ 0] * data[1][ 1] * data[2][ 3] * data[3][ 2] -
			data[0][ 2] * data[1][ 1] * data[2][ 0] * data[3][ 3] + data[0][ 1] * data[1][ 2] * data[2][ 0] * data[3][ 3] +
			data[0][ 2] * data[1][ 0] * data[2][ 1] * data[3][ 3] - data[0][ 0] * data[1][ 2] * data[2][ 1] * data[3][ 3] -
			data[0][ 1] * data[1][ 0] * data[2][ 2] * data[3][ 3] + data[0][ 0] * data[1][ 1] * data[2][ 2] * data[3][3];
	}

	inline float Matrix4::determinantc() const
	{
		float temp1 = data[0][0] * this->C(0, 0);
		float temp2 = data[0][1] * this->C(0, 1);
		float temp3 = data[0][2] * this->C(0, 2);
		float temp4 = data[0][3] * this->C(0, 3);

		return temp1+temp2+temp3+temp4;
	}

	

	// override operators MAtrix4 +-*/ Matrix4
	inline const Matrix4& operator+ (const Matrix4& A, const Matrix4& B) {
		array_ff temp;
		const array_ff& TA = A.Get();
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] + TB[i][j];
			}
		}
		return GStar::AddPool(temp);
	}
	inline const Matrix4& operator- (const Matrix4& A, const Matrix4& B) {
		array_ff temp;
		const array_ff& TA = A.Get();
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] - TB[i][j];
			}
		}
		return GStar::AddPool(temp);
	}
	inline const Matrix4& operator* (const Matrix4& A, const Matrix4& B) {
		array_ff temp;
		const array_ff& TA = A.Get();
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] * TB[i][j];
			}
		}
		return GStar::AddPool(temp);
	}
	inline const Matrix4& operator/ (const Matrix4& A, const Matrix4& B) {
		array_ff temp;
		const array_ff& TA = A.Get();
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] / TB[i][j];
			}
		}
		return GStar::AddPool(temp);
	}
	// number and matrix4 */

	inline const Matrix4& operator* (float A, const Matrix4& B){
		array_ff temp;
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = A * TB[i][j];
			}
		}
		return GStar::AddPool(temp);
	}

	inline const Matrix4& operator* (const Matrix4& A, float B) {
		array_ff temp;
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] * B;
			}
		}
		return GStar::AddPool(temp);
	}

	inline const Matrix4& operator/ (const Matrix4& A, float B) {
		array_ff temp;
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] / B;
			}
		}
		return GStar::AddPool(temp);
	}

	inline void Matrix4::value_ptr(const Matrix4 & matrix,array_f & temparray)
	{   // Since OpenGL use column major order so we need to transpose ower matrix
		Matrix4 tempmatrix;
		tempmatrix = matrix.T();
		const array_ff& TA = tempmatrix.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temparray[i*SIZE + j] = TA[i][j];
			}
		}
	}

	inline Matrix4::Matrix4()
	{
	}

	inline Matrix4::~Matrix4()
	{
	}
	inline Matrix4::Matrix4(const array_ff & rdata)
	{
		this->Copy(rdata);
	}
	inline void Matrix4::Copy(const array_ff & rdata)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->data[i][j] = rdata[i][j];
			}
		}
	}
	inline const array_ff& Matrix4::Get() const
	{
		return data;
	}
}
#endif // !MATRIX4

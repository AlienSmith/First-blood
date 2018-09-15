#pragma once
#ifndef MATRIX4
#define MATRIX4
#include <vector>
#define out
#define SIZE 4
#define ZERO_ARRAY { {0,0,0,0},{0, 0, 0, 0},{ 0,0,0,0 },{ 0,0,0,0 }, }
typedef float array_ff[SIZE][SIZE];
namespace GStar {
	class Matrix4
	{
	public:
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
		// A funtion that should not work
		const Matrix4& Dot(const Matrix4& B) const;
		//void Transform();
	private:
		array_ff data = ZERO_ARRAY;
	};
	// Matrix to Matrix = += -= *= /= 
	inline void Matrix4::operator=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] = TA[i][j];
			}
		}
	}
	inline void Matrix4::operator+=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] += TA[i][j];
			}
		}
	}
	inline void Matrix4::operator-=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] -= TA[i][j];
			}
		}
	}
	inline void Matrix4::operator*=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] *= TA[i][j];
			}
		}
	}
	inline void Matrix4::operator/=(const Matrix4 & A)
	{
		const array_ff& TA = A.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->data[i][j] /= TA[i][j];
			}
		}
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
	//return the matrix product between two matrics
	inline void Matrix4::Dot(const Matrix4 & B, Matrix4& out matrix3) const
	{
		array_ff temp = ZERO_ARRAY;
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

	inline const Matrix4& Matrix4::Dot(const Matrix4& B)  const
	{
		array_ff temp = ZERO_ARRAY;
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				for (int m = 0; m < SIZE; m++) {
					temp[i][j] += this->data[i][m] * TB[m][j];
				}
			}
		}
		return temp;
	}


	

	inline const Matrix4& operator+ (const Matrix4& A, const Matrix4& B) {
		array_ff temp;
		array_ff & rtemp = temp;
		const array_ff& TA = A.Get();
		const array_ff& TB = B.Get();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				temp[i][j] = TA[i][j] + TB[i][j];
			}
		}
		return rtemp;
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

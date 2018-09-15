#pragma once
#include <math.h>
namespace GStar {
	//TODO Fully test Vector2 
	class Vector2 {
	public:
		Vector2();
		Vector2(int x, int y);
		Vector2(float x, float y);
		float x() const;
		float y() const;
		void x(int x);
		void y(int y);
		void x(float x);
		void y(float y);
		// 2D vectors operations 
		void Normalize();
		float Dot(const Vector2& other) const;
		float Length() const;
		static Vector2 ProjAtoB(const Vector2& A, const Vector2& B);
		static Vector2 PerpAtoB(const Vector2& A, const Vector2& B);
		static float TriangleArea(const Vector2& A, const Vector2& B);
		void operator = (const Vector2& B) {
			this->m_x = B.x();
			this->m_y = B.y();
		}
		void operator += (const Vector2& B) {
			this->m_x += B.x();
			this->m_y += B.y();
		}
		void operator -= (const Vector2& B) {
			this->m_x -= B.x();
			this->m_y -= B.y();
		}
		void operator *= (const Vector2& B) {
			this->m_x *= B.x();
			this->m_y *= B.y();
		}
		void operator /= (const Vector2& B) {
			this->m_x /= B.x();
			this->m_y /= B.y();
		}
		void operator *= (int B) {
			this->m_x *= B;
			this->m_y *= B;
		}
		void operator /= (int B) {
			this->m_x /= B;
			this->m_y /= B;
		}
		void operator *= (float B) {
			this->m_x *= B;
			this->m_y *= B;
		}
		void operator /= (float B) {
			this->m_x /= B;
			this->m_y /= B;
		}
	private:
		float m_x;
		float m_y;

	};
	// Operator overriede
	inline Vector2 operator + (const Vector2& A, const Vector2& B) {
		return Vector2(A.x() + B.x(), A.y() + B.y());
	}
	inline Vector2 operator - (const Vector2& A, const Vector2& B) {
		return Vector2(A.x() - B.x(), A.y() - B.y());
	}
	inline Vector2 operator * (const Vector2& A, const Vector2& B) {
		return Vector2(A.x() * B.x(), A.y() * B.y());
	}
	inline Vector2 operator * (const float A, const Vector2& B) {
		return Vector2(A * B.x(), A * B.y());
	}
	inline Vector2 operator * (const Vector2& A, const float B) {
		return Vector2(A.x() * B, A.y() * B);
	}
	inline Vector2 operator * (const int A, const Vector2& B) {
		return Vector2(A * B.x(), A * B.y());
	}
	inline Vector2 operator / (const Vector2& A, const int B) {
		return Vector2(A.x() / B, A.y() / B);
	}
	inline Vector2 operator / (const float A, const Vector2& B) {
		return Vector2(A / B.x(), A / B.y());
	}
	inline Vector2 operator / (const Vector2& A, const float B) {
		return Vector2(A.x() / B, A.y() / B);
	}
	inline Vector2 operator / (const int A, const Vector2& B) {
		return Vector2(A / B.x(), A / B.y());
	}
	inline GStar::Vector2::Vector2()
	{
	}

	inline GStar::Vector2::Vector2(int x, int y)
	{
		this->m_x = x;
		this->m_y = y;
	}

	inline GStar::Vector2::Vector2(float x, float y)
	{
		this->m_x = x;
		this->m_y = y;
	}

	inline float GStar::Vector2::x() const
	{
		return this->m_x;
	}

	inline float GStar::Vector2::y() const
	{
		return this->m_y;
	}

	inline void GStar::Vector2::x(int x)
	{
		this->m_x = x;
	}

	inline void GStar::Vector2::y(int y)
	{
		this->m_y = y;
	}

	inline void GStar::Vector2::x(float x)
	{
		this->m_x = x;
	}

	inline void GStar::Vector2::y(float y)
	{
		this->m_y = y;
	}
	// this manage the dot product of two vector.
	inline float GStar::Vector2::Dot(const Vector2& other) const
	{
		return this->m_x*other.m_x + this->m_y*other.m_y;
	}
	// this length of the vector
	inline float GStar::Vector2::Length() const {
		return sqrt(this->m_x*this->m_x+this->m_y*this->m_y);
	}
	//this will normalize the vector
	inline void GStar::Vector2::Normalize() {
		float length = this->Length();
		this->m_x = this->m_x/length;
		this->m_y = this->m_y/length;
		return;
	}
	// return projective from vector A onto vector B
	inline GStar::Vector2 GStar::Vector2::ProjAtoB(const Vector2& A, const Vector2& B) {
		return A.Dot(B) / B.Length()* (B/B.Length());
	}
	// return perpendicular part of vector A of vector B 
	inline GStar::Vector2 GStar::Vector2::PerpAtoB(const Vector2& A, const Vector2& B) {
		return A - (A.Dot(B) / B.Length()* (B / B.Length()));
	}
	//this return the area of the triangle surrounded by A, B and A-B
	inline float GStar::Vector2::TriangleArea(const Vector2& A, const Vector2& B) {
		Vector2 temp = A - (A.Dot(B) / B.Length()* (B / B.Length()));
		return temp.Length()*B.Length()/2;
	}
}

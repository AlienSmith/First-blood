#pragma once
#include <math.h>
#ifndef Vector3_H
#define Vector3_H
namespace GStar {
	//TODO test the Vector3 Class
	class Vector3 {
	public:
		Vector3();
		Vector3(int x, int y, int z);
		Vector3(float x, float y, float z);
		float x() const;
		float y() const;
		float z() const;
		void x(int x);
		void y(int y);
		void z(int z);
		void x(float x);
		void y(float y);
		void z(float z);
		// 2D vectors operations 
		void Normalize();
		float Dot(const Vector3& other) const;
		float Length() const;
		static Vector3 ProjAtoB(const Vector3& A, const Vector3& B);
		static Vector3 PerpAtoB(const Vector3& A, const Vector3& B);
		static Vector3 Cross(const Vector3& A, const Vector3& B);
		static float Volume(const Vector3& A, const Vector3& B,const Vector3& C);
		void operator = (const Vector3& B) {
			this->m_x = B.x();
			this->m_y = B.y();
			this->m_z = B.z();
		}
		void operator += (const Vector3& B) {
			this->m_x += B.x();
			this->m_y += B.y();
			this->m_z += B.z();
		}
		void operator -= (const Vector3& B) {
			this->m_x -= B.x();
			this->m_y -= B.y();
			this->m_z -= B.z();
		}
		void operator *= (const Vector3& B) {
			this->m_x *= B.x();
			this->m_y *= B.y();
			this->m_z *= B.z();
		}
		void operator /= (const Vector3& B) {
			this->m_x /= B.x();
			this->m_y /= B.y();
			this->m_z /= B.z();
		}
		void operator *= (int B) {
			this->m_x *= B;
			this->m_y *= B;
			this->m_z *= B;
		}
		void operator /= (int B) {
			this->m_x /= B;
			this->m_y /= B;
			this->m_z /= B;
		}
		void operator *= (float B) {
			this->m_x *= B;
			this->m_y *= B;
			this->m_z *= B;
		}
		void operator /= (float B) {
			this->m_x /= B;
			this->m_y /= B;
			this->m_z /= B;
		}
	private:
		float m_x;
		float m_y;
		float m_z;
	};
	// Operator overriede
	inline Vector3 operator + (const Vector3& a, const Vector3& b) {
		return Vector3(a.x()+b.x(),a.y()+b.y(),a.z()+b.z());
	}
	inline Vector3 operator - (const Vector3& a, const Vector3& b) {
		return Vector3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
	}
	inline Vector3 operator * (const Vector3& a, const Vector3& b) {
		return Vector3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
	}
	inline Vector3 operator * (const float a, const Vector3& b) {
		return Vector3(a * b.x(), a * b.y(), a * b.z());
	}
	inline Vector3 operator * (const Vector3& a, const float b) {
		return Vector3(a.x() * b, a.y() * b, a.z() * b);
	}
	inline Vector3 operator * (const int a, const Vector3& b) {
		return Vector3(a * b.x(), a * b.y(), a * b.z());
	}
	inline Vector3 operator / (const Vector3& a, const int b) {
		return Vector3(a.x() / b, a.y() / b, a.z() / b);
	}
	inline Vector3 operator / (const float a, const Vector3& b) {
		return Vector3(a / b.x(), a / b.y(), a / b.z());
	}
	inline Vector3 operator / (const Vector3& a, const float b) {
		return Vector3(a.x() / b, a.y() / b, a.z() / b);
	}
	inline Vector3 operator / (const int a, const Vector3& b) {
		return Vector3(a / b.x(), a / b.y(), a / b.z());
	}
	inline GStar::Vector3::Vector3()
	{
	}

	inline GStar::Vector3::Vector3(int x, int y, int z)
	{
		this->m_x = x;
		this->m_y = y;
		this->m_z = z;
	}

	inline GStar::Vector3::Vector3(float x, float y,float z)
	{
		this->m_x = x;
		this->m_y = y;
		this->m_z = z;
	}

	inline float GStar::Vector3::x() const
	{
		return this->m_x;
	}

	inline float GStar::Vector3::y() const
	{
		return this->m_y;
	}

	inline float GStar::Vector3::z() const
	{
		return this->m_z;
	}

	inline void GStar::Vector3::x(int x)
	{
		this->m_x = x;
	}

	inline void GStar::Vector3::y(int y)
	{
		this->m_y = y;
	}
	inline void GStar::Vector3::z(int z)
	{
		this->m_z = z;
	}

	inline void GStar::Vector3::x(float x)
	{
		this->m_x = x;
	}

	inline void GStar::Vector3::y(float y)
	{
		this->m_y = y;
	}
	inline void GStar::Vector3::z(float z)
	{
		this->m_z = z;
	}
	// this manage the dot product of two vector.
	inline float GStar::Vector3::Dot(const Vector3& other) const
	{
		return this->m_x*other.m_x + this->m_y*other.m_y+this->m_z*other.m_z;
	}
	// this length of the vector
	inline float GStar::Vector3::Length() const {
		return sqrt(this->m_x*this->m_x + this->m_y*this->m_y+this->m_z*this->m_z);
	}
	//this will normalize the vector
	inline void GStar::Vector3::Normalize() {
		float length = this->Length();
		this->m_x = this->m_x / length;
		this->m_y = this->m_y / length;
		this->m_z = this->m_z / length;
		return;
	}
	// return projective from vector A onto vector B
	inline GStar::Vector3 GStar::Vector3::ProjAtoB(const Vector3& A, const Vector3& B) {
		return A.Dot(B) / B.Length()* (B / B.Length());
	}
	// return perpendicular part of vector A of vector B 
	inline GStar::Vector3 GStar::Vector3::PerpAtoB(const Vector3& A, const Vector3& B) {
		return A - (A.Dot(B) / B.Length()* (B / B.Length()));
	}
	//this return the cross product
	inline Vector3 GStar::Vector3::Cross(const Vector3& A, const Vector3& B) {
		float temp_x = A.y()*B.z() - A.z()*B.y();
		float temp_y = A.z()*B.x() - A.x()*B.z();
		float temp_Z = A.x()*B.y() - A.y()*B.x();
		return Vector3(temp_x,temp_y,temp_Z);
	}
	// this return the Volume of the tetrahedron generated by the three Vectors
	inline float GStar::Vector3::Volume(const Vector3& A, const Vector3& B,const Vector3& C) {
		return (Vector3::Cross(A, B).Dot(C));
	}

}
#endif // !Vector3_H

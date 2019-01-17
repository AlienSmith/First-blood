#pragma once
#include"Vector3.h"
#include <cmath>
namespace GStar {
	class Trace {
	public:
		Trace() :_isline(true) {}
		Trace(const Trace& other);
		Trace(const Vector3& base, const Vector3& direction, bool isline) :_base(base), _direction(direction), _isline(isline) {}
		Trace(Vector3&& base, Vector3&& direction, bool isline) :_base(base), _direction(direction), _isline(isline) {}
		inline Trace& operator = (const Trace& other);
		~Trace(){}
		inline void Set(const Vector3& base, const Vector3& direction,bool isline) {
			_base = base;
			_direction = direction;
			_isline = isline;
		}
		inline void Set( Vector3&& base,  Vector3&& direction, bool isline) {
			_base = base;
			_direction = direction;
			_isline = isline;
		}
		inline Vector3 GetBase() const { return _base; }
		inline Vector3 GetDirection() const{ return _direction; }
		inline bool IsLine() const { return _isline; }
	private:
		Vector3 _base;
		Vector3 _direction;
		bool _isline;
	};
	inline Trace::Trace(const Trace& other) {
		_base = other._base;
		_direction = other._direction;
		_isline = other._isline;
	}
	inline Trace & Trace::operator=(const Trace & other)
	{
		_base = other._base;
		_direction = other._direction;
		_isline = other._isline;
		return *this;
	}
	//return the distance between a point to a infinite line
	inline float DistanceBetween(const GStar::Vector3& point, const GStar::Trace& line) {
		GStar::Vector3 temp = point - line.GetBase();
		return GStar::Vector3::PerpAtoB(temp, line.GetBase()).Length();
	}
	//return the distance between two infinite line
	inline float DistanceBetween(const GStar::Trace& lineA, const GStar::Trace& LineB) {
		GStar::Vector3 s1 = lineA.GetBase();
		GStar::Vector3 v1 = lineA.GetDirection();
		GStar::Vector3 s2 = LineB.GetBase();
		GStar::Vector3 v2 = LineB.GetDirection();
		if (lineA.IsLine()) { v1.Normalize();}
		if (LineB.IsLine()) { v2.Normalize();}
		float base = pow(v1.Dot(v2), 2) - v1.Dot(v1)*v2.Dot(v2);
		if (base < 0.00001f && base >-0.00001f) {
			return DistanceBetween(s1, LineB);
		}
		else {
			float c1 = (s2 - s1).Dot(v1);
			float c2 = (s2 - s1).Dot(v2);
			float t1 = (-c1 +v1.Dot(v2)*c2)/base;
			float t2 = (-(v1.Dot(v2)*c1) + c2) / base;
			s1 += t1 * v1;
			s2 += t2 * v2;
			return (s2 - s1).Length();
		}
	}
}
#pragma once
#include "Vector3.h"
namespace GStar {
	class Rectangle {
	public:
		Rectangle() {}
		Rectangle(const Vector3& center,const Vector3& normal, float x, float y) :
			_centerPoint(center),
			_normalDirection(normal),
			_Xexpand(x),
			_Yexpand(y){}
		Rectangle( Vector3&& center,  Vector3&& normal, float x, float y) :
			_centerPoint(center),
			_normalDirection(normal),
			_Xexpand(x),
			_Yexpand(y) {}
		Rectangle(const Rectangle& other) {
			_centerPoint = other._centerPoint;
			_normalDirection = other._normalDirection;
			_Xexpand = other._Xexpand;
			_Yexpand = other._Yexpand;
		}
		Rectangle& operator = (const Rectangle& other) {
			_centerPoint = other._centerPoint;
			_normalDirection = other._normalDirection;
			_Xexpand = other._Xexpand;
			_Yexpand = other._Yexpand;
		}
		inline void Set(const Vector3& center, const Vector3& normal, float x, float y) {
			_centerPoint = center;
			_normalDirection = normal;
			_Xexpand = x;
			_Yexpand = y;
		}
		inline void Set(Vector3&& center, Vector3&& normal, float x, float y) {
			_centerPoint = center;
			_normalDirection = normal;
			_Xexpand = x;
			_Yexpand = y;
		}
		inline Vector3 GetCenter() const{
			return _centerPoint;
		}
		inline Vector3 GetDirection() const {
			return _normalDirection;
		}
		inline float GetXexpand() const{
			return _Xexpand;
		}
		inline float GetYexpand() const{
			return _Yexpand;
		}
	private:
		Vector3 _centerPoint;
		Vector3 _normalDirection;
		float _Xexpand;
		float _Yexpand;
	};
	//return the distance between a point to a infinite plane
	inline float DistanceBetween(const GStar::Vector3& point, const GStar::Rectangle& plane) {
		Vector3 temp = point - plane.GetCenter();
		return GStar::Vector3::ProjAtoB(temp, plane.GetDirection()).Length();
	}
	//return the distance between two infinite plane
	inline float DistanceBetween(const GStar::Rectangle& planeA, const GStar::Rectangle& planeB) {
		short int flag = GStar::Vector3::parallel(planeA.GetDirection(),planeB.GetDirection());
		if (flag != 0) {
			return (planeA.GetCenter() - planeB.GetCenter()).Length();
		}
		else {
			return 0;
		}
	}
}
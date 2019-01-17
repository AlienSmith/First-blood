#include "Trace.h"
#include "Rectangle.h"
namespace GStar {
	//Return the distance between an infinite line and an infinite plane return 0 if the line intersect with the plane
	inline float DistanceBetween(const GStar::Trace& lineA, const GStar::Rectangle& Plane) {
		if (EqualsZero(lineA.GetDirection().Dot(Plane.GetDirection()))) {
			return DistanceBetween(lineA.GetBase, Plane);
		}
		else {
			return 0;
		}
	}
	inline bool Intersect(const GStar::Trace& lineA, const GStar::Trace& LineB, GStar::Vector3 IntersectPoint) {

		GStar::Vector3 normal = GStar::Vector3::Cross(lineA.GetDirection(),LineB.GetDirection());
		GStar::Vector3 temp = lineA.GetBase() - LineB.GetBase();
		if (EqualsZero(normal.Dot(temp))) {
			return true;
		}
		else {
			return false;
		}
	}
}
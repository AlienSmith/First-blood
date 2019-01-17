#include "Trace.h"
#include "Rectangle.h"
#include <algorithm>
#include "ConsolePrint.h"
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
	//return ture if two line intersect intersect point stored at IntersectPoint
	inline bool Intersect(const GStar::Trace& lineA, const GStar::Trace& LineB, GStar::Vector3 IntersectPoint) {
		//paralel lines could intersect at multiple points return the middle point if intersect
		if (GStar::Vector3::parallel(lineA.GetDirection(), LineB.GetDirection()) != 0) {
			int i = 0;
			while (i < 3) {
				if (!EqualsZero(lineA.GetDirection().getValue(i))) {
					float x = lineA.GetBase().getValue(i);
					float deltax = lineA.GetDirection().getValue(i);
					float basex = LineB.GetBase().getValue(i);
					float endx = basex + LineB.GetDirection().getValue(i);
					float left = (basex - x) / deltax;
					float right = (endx - x) / deltax;
					if ((BigerThan(left, 1.0f) && BigerThan(right, 1.0f)) || (SmallerThan(left, 0.0f) && SmallerThan(left, 0.0f))) {
						return false;
					}
					else
					{
						float low = std::clamp(std::min(left, right),0.0f,1.0f);
						float high = std::clamp(std::max(left, right), 0.0f, 1.0f);
						IntersectPoint = lineA.GetBase() + ((low + high) / 2.0f)*lineA.GetDirection();
						return true;
					}
				}
				else {
					i++;
				}
			}
		}
		//Not Parallel either intersect at one point or not
		else {
			GStar::Vector3 normal = GStar::Vector3::Cross(lineA.GetDirection(), LineB.GetDirection());
			GStar::Vector3 temp = lineA.GetBase() - LineB.GetBase();
			//All the line inside the plane should be perpendicular to the normal vector
			//since they are not parallel there will be two equations
			if (EqualsZero(normal.Dot(temp))) {
				int i = 0;
				int ii = 0;
				float x2bx1[2] = { 0.0f,0.0f }; // x2 -x1
				float dx1[2] = { 0.0f,0.0f };
				float dx2[2] = { 0.0f,0.0f };
				while (i < 3) {
					if (!(EqualsZero(lineA.GetDirection().getValue(i))&& EqualsZero(LineB.GetDirection().getValue(i)))) {
						x2bx1[ii] = LineB.GetBase().getValue(i) - lineA.GetBase().getValue(i);
						dx1[ii] = lineA.GetDirection().getValue(i);
						dx2[ii] = LineB.GetDirection().getValue(i);
						ii++;
						if (ii == 2) {
							break;
						}
					}
					i++;
				}
				if (ii != 2) {
					DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "The two lines are parallel");
				}
				float determaint = 1.0f / dx2[0] * dx1[1] - dx1[0] * dx2[1]; //[0] == x [1] == y
				float t1 = determaint * (-dx2[1] * x2bx1[0] - dx1[1] * x2bx1[1]);
				IntersectPoint=(lineA.GetBase()+lineA.GetDirection()*t1);				
				return true;
			}
			else {
				return false;
			}
		}
	}
}
#include "Trace.h"
#include "Rectangle.h"
#include <algorithm>
#include "ConsolePrint.h"
#include "TransformComponent.h"
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
	//TODO add the plane size thing into account
	//return the intersection point between line and plane
	inline bool Intersect(const GStar::Trace& Line, const GStar::Rectangle& Plane, GStar::Vector3 IntersectPoint) {
		//if the line is perpendicular to the normal vector, the line could either on the plane or parallel to the plane
		if (EqualsZero(Line.GetDirection().Dot(Plane.GetDirection()))) {
			float temp = Plane.GetDirection().Dot(Line.GetBase() - Plane.GetCenter());
			if (EqualsZero(temp)) {
				IntersectPoint = Line.GetBase();
				return true;
			}
			else {
				return false;
			}
		}
		//if they are not parallel there will be a contact point, detect whether the contact point is on the plane and the line
		else {
			float t = Plane.GetDirection().Dot(Plane.GetCenter()) - Plane.GetDirection().Dot(Line.GetBase());
			t /= Plane.GetDirection().Dot(Plane.GetDirection());
			if (BigerThan(t, 0.0f) && SmallerThan(t, 1.0f)) {
				IntersectPoint = Line.GetBase() + t * Line.GetDirection();
				return true;
			}
			else {
				return false;
			}
		}
	}
	//This function used to generate contact point between triangles and an ray

	//This function used to generate contact point between built in cube box and an ray
	inline bool Intersect(const GStar::Trace& Line, const TransformComponent& Box, GStar::Vector3 IntersectPoint) {
		//Transfer the Ray to the Box object space
		GStar::Vector3 Base = Box.getInverseModel()*Line.GetBase();
		GStar::Vector3 Direction = Box.getInverseModel()* Line.GetDirection();
		//If the Start Point is Within the box Return Flase
		if (Base.x()> -.5f && Base.x()< .5f && Base.y()> -.5f && Base.y()<.5f && Base.z()> -.5f && Base.z()< .5f) {
			return false;
		}
		else
		{
			float t[3];
			for (int i = 0; i < 3; i++) {
				if (Direction.getValue(i)> 0.0f) {
					t[i] = (-.5 - Base.getValue(i)) / Direction.getValue(i);
				}
				else if (Direction.x()< 0.0f) {
					t[i] = (.5 - Base.getValue(i)) / Direction.getValue(i);
				}
				else {
					//Assume The distance will not be bigger that this amount
					t[i] = 1000000.0f;
				}
			}
			int index = (std::abs(t[0]) <= std::abs(t[1])) ? 0:1 ;
			index = (std::abs(t[index]) <= std::abs(t[2])) ? index : 2;
			if (Line.IsLine()) {
				if (t[index] > 1.0f) {
					return false;
				}
			}
			//The InterSection Point in the model space
			IntersectPoint = Base + t[index]*Direction ;
			return true;
		}
	}
}
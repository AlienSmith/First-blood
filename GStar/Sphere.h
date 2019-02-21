#pragma once
#include <math.h>
#include"Hitable.h"
namespace GStar {
	class Sphere: public Hitable {
	public:
		Sphere(const Vector3& center, float r): m_center(center),m_r(r){}
		bool hit(const Ray& ray, float t_min = 0.0f, float t_max = 100.0f, hit_record& rec = record) const override;
	private:
		Vector3 m_center;
		float m_r;
	};
}
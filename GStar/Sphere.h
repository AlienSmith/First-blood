#pragma once
#include <math.h>
#include"Hitable.h"
#include"SharedPointer.h"
namespace GStar {
	class material;
	class Sphere: public Hitable {
	public:
		Sphere(const Vector3& center, float r,material* m):Hitable(), m_center(center),m_r(r), m_material(m){}
		Sphere(const Sphere& other) = delete;
		Sphere& operator = (const Sphere& other) = delete;
		bool hit(const Ray& ray, float t_min = 0.0f, float t_max = 100.0f, hit_record& rec = record) const override;
		~Sphere() {}
	private:
		Vector3 m_center;
		float m_r;
		SharedPointer<material> m_material;
	};
}
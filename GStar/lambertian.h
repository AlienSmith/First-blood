#pragma once
#include"material.h"
#include "Vector3.h"
namespace GStar {
	class lambertian :public material {
	public:
		lambertian(const Vector3& a):albedo(a){}
		virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const;
		Vector3 albedo;
	};
}
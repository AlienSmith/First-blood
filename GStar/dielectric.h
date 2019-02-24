#pragma once
#include "material.h"
namespace GStar {
	//the material only do refraction
	class dielectric:public material {
	public:
		dielectric(float ri):ref_idx(ri){}
		bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const;
		float ref_idx;
	};
}
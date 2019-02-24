#pragma once
#include"material.h"
#include"Vector3.h"
namespace GStar {
	class metal:public material {
	public:
		metal(const Vector3& a,float f):albedo(a),fuzz(f){}
		virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const;
		Vector3 albedo;
		//for the glossy reflection set number smaller than 1;
		float fuzz;
	};
}
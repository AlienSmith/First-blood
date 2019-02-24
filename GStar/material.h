#pragma once
namespace GStar {
	class Ray;
	struct hit_record;
	class Vector3;
	class material {
	public:
		virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const = 0;
		virtual ~material() {}
	};
}
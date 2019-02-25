#include "dielectric.h"
#include "Hitable.h"
#include "Ray.h"
#include "Schlick.h"
bool GStar::dielectric::scatter(const Ray & r_in, const hit_record & rec, Vector3 & attenuation, Ray & scattered) const
{
	GStar::RayData ray = r_in.getValue();
	GStar::Vector3 outward_normal;
	GStar::Vector3 reflected = GStar::Vector3::Reflect(ray.direction, rec.n);
	float ni_over_nt;
	attenuation = GStar::Vector3(1.0f, 1.0f, 0.0f);
	GStar::Vector3 refracted;
	if (ray.direction.Dot(rec.n) > 0) {
		outward_normal = -1.0f*rec.n;
		ni_over_nt = ref_idx;
	}
	else {
		outward_normal = rec.n;
		ni_over_nt = 1.0f / ref_idx;
	}
	if (GStar::Vector3::Refract(ray.direction, outward_normal, ni_over_nt, refracted)) {
		scattered = GStar::Ray(rec.p, refracted);
		return true;
	}
	else {
		scattered = GStar::Ray(rec.p, reflected);
		return false;
	}
}

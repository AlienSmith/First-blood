#include "dielectric.h"
#include "Hitable.h"
#include "Ray.h"
#include "Schlick.h"
bool GStar::dielectric::scatter(const Ray & r_in, const hit_record & rec, Vector3 & attenuation, Ray & scattered) const
{
	RayData ray = r_in.getValue();
	Vector3 outward_normal;
	Vector3 reflected = Vector3::Reflect(ray.direction, rec.n);
	float ni_over_nt;
	attenuation = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 refracted;
	float reflect_prob;
	float cosine;
	if (ray.direction.Dot(rec.n) > 0) {
		outward_normal = -1.0f * rec.n;
		ni_over_nt = ref_idx;
		cosine = ref_idx * ray.direction.Dot(rec.n);
	}
	else {
		outward_normal = rec.n;
		ni_over_nt = 1.0f / ref_idx;
		cosine = -1.0f * ray.direction.Dot(rec.n);
	}
	if (Vector3::Refract(ray.direction, outward_normal, ni_over_nt, refracted)) {
		reflect_prob = schlik(cosine, ref_idx);
	}
	else {
		scattered = Ray(rec.p, reflected);
		reflect_prob = 1.0f;
	}if (UnitRandom() <= reflect_prob) {
		scattered = Ray(rec.p, reflected);
	}
	else {
		scattered = Ray(rec.p, refracted);
	}
	return true;
}

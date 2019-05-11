#include "lambertian.h"
#include "Ray.h"
#include "Hitable.h"
#include "SimpleExample.h"
bool GStar::lambertian::scatter(const Ray &, const hit_record & rec, Vector3 & attenuation, Ray & scattered) const
{
	GStar::Vector3 direction = rec.n + SimpleExample::random_in_unit_sphere();
	direction.Normalize();
	scattered = Ray(rec.p, direction);
	attenuation = albedo;
	return true;
}

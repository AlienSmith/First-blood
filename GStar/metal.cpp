#include "metal.h"
#include "Hitable.h"
#include "Ray.h"
#include "SimpleExample.h"
bool GStar::metal::scatter(const Ray & r_in, const hit_record & rec, Vector3 & attenuation, Ray & scattered) const
{
	Vector3 reflectdirection = Vector3::Reflect(r_in.getValue().direction, rec.n);
	reflectdirection.Normalize();
	reflectdirection += fuzz * SimpleExample::random_in_unit_sphere();
	reflectdirection.Normalize();
	scattered = Ray(rec.p, reflectdirection);
	attenuation = albedo;
	return  (reflectdirection.Dot(rec.n) > 0);
}

#include "hitable_list.h"

bool GStar::hitable_list::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const
{
	hit_record temp_rec;
	bool hit = false;
	double cloest_so_far = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(ray, t_min, cloest_so_far, temp_rec)) {
			hit = true;
			cloest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit;
}

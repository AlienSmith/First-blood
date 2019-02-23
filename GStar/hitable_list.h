#pragma once
#include "Hitable.h"
#include <list>
namespace GStar {
	class hitable_list: public Hitable {
	public:
		hitable_list() {}
		hitable_list(Hitable **l,int n):list(l),list_size(n){}
		virtual bool  hit(const Ray& ray, float t_min = Hitable::DEFAULT_RAY_MIN,
			float t_max = Hitable::DEFAULT_RAY_MAX, hit_record& rec = Hitable::record) const;

		Hitable ** list;
		int list_size;
		
	};
}
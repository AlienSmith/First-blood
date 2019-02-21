#pragma once
#include"Vector3.h"
namespace GStar {
	class Ray;
	struct hit_record {
		float t;
		Vector3 p;
		Vector3 n;
	};
	class Hitable {
	public:
		static constexpr float DEFAULT_RAY_MIN = 0.0f;
		static constexpr float DEFAULT_RAY_MAX = 100.0f;
		static hit_record record;
		virtual bool hit(const Ray& ray, float t_min = DEFAULT_RAY_MIN, float t_max = DEFAULT_RAY_MAX, hit_record& rec = record) const = 0;
	};
}
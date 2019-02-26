#pragma once
#include<math.h>
#include<random>
#include <limits>
namespace GStar {
	constexpr float MAXFLOAT = std::numeric_limits<float>::max();
	inline static float schlik(float cosine, float ref_idx) {
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0)* pow((1 - cosine), 5);
	}inline static float UnitRandom() {
			return ((float)rand() / (RAND_MAX));
	}
	inline static Vector3 random_in_unit_circle() {
		Vector3 p;
		do {
			p = 2.0f*Vector3(UnitRandom(), UnitRandom(), 0.0f) - Vector3(1, 1, 0);
		} while (p.Dot(p) >= 1.0);
		return p;
	}
}
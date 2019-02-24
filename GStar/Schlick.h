#pragma once
#include<math.h>
#include<random>
namespace GStar {
	inline static float schlik(float cosine, float ref_idx) {
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0)* pow((1 - cosine), 5);
	}inline static float UnitRandom() {
			return ((float)rand() / (RAND_MAX));
	}
}
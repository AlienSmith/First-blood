#pragma once
#define FLOAT_LIMIT 0.00001F
namespace GStar {
	inline bool BigerThan(float a, float b) {
		return a - b > FLOAT_LIMIT ? true:false;
	}
	inline bool Equals(float a, float b) {
		return (a - b < FLOAT_LIMIT && a-b > (-1)* FLOAT_LIMIT) ? true : false;
	}
	inline bool SmallerThan(float a, float b) {
		return b - a > FLOAT_LIMIT ? true : false;
	}
	inline bool EqualsZero(float a) {
		return a*a < FLOAT_LIMIT*FLOAT_LIMIT ? true : false;
	}
}
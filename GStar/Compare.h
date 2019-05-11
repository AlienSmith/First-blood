#pragma once
#define FLOAT_LIMIT 0.00001F
#include<stdlib.h>
#include<type_traits>
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
	//source https ://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
	template <typename T> inline constexpr
		int signum(T x, std::false_type is_signed) {
		return T(0) < x;
	}

	template <typename T> inline constexpr
		int signum(T x, std::true_type) {
		return (T(0) < x) - (x < T(0));
	}

	template <typename T> inline constexpr
		int signum(T x) {
		return signum(x, std::is_signed<T>());
	}
}
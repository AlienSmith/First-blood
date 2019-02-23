#pragma once
#include "Vector3.h"
#include "Ray.h"
namespace GStar {
	struct TRCdata {
		Vector3 origin;
		Vector3 lower_left_corner;
		Vector3 horizontal;
		Vector3 vertical;
	};
	class TRCamera {
	public:
		TRCamera() :m_data({orig,lf_cornor,hori,vert}) {}
		inline Ray get_ray(float u, float v) {
			return Ray(m_data.origin, m_data.lower_left_corner +
				m_data.horizontal*u + m_data.vertical*v -
				m_data.origin);
		}
	private:
		static const Vector3 lf_cornor;
		static const Vector3 hori;
		static const Vector3 vert;
		static const Vector3 orig;
		TRCdata m_data;
	};
}
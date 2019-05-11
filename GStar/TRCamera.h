#pragma once
#include "Vector3.h"
#include "Ray.h"
namespace GStar {
	static constexpr float M_PI_OVER_180 = 3.14159265359f / 180.0f;
	struct TRCdata {
		Vector3 origin;
		Vector3 lower_left_corner;
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 m_u, m_v, m_w;
		float lens_radius;
	};
	class TRCamera {
	public:
		TRCamera() :m_data({orig,lf_cornor,hori,vert,u,v,w,radius}) {
		}
		TRCamera(float vfov, float aspect);
		Ray get_ray(float u, float v) const;
		TRCamera(const GStar::Vector3& lookfrom, const GStar::Vector3& lookat, const GStar::Vector3& vup, float vfov, float aspect);
		TRCamera(const GStar::Vector3& lookfrom, const GStar::Vector3& lookat, const GStar::Vector3& vup, float vfov, float aspect,float aperture,float focus_distance);
	private:
		static const Vector3 lf_cornor;
		static const Vector3 hori;
		static const Vector3 vert;
		static const Vector3 orig;
		static const Vector3 u,v,w;
		static const float radius;
		TRCdata m_data;
	};
}
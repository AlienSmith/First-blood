#include"TRCamera.h"
#include"Schlick.h"
const GStar::Vector3 GStar::TRCamera::lf_cornor = GStar::Vector3(-2.0f, -2.0f, -1.0f);
const GStar::Vector3 GStar::TRCamera::hori = GStar::Vector3(4.0f, 0.0f, 0.0f);
const GStar::Vector3 GStar::TRCamera::vert = GStar::Vector3(0.0f, 4.0f, 0.0f);
const GStar::Vector3 GStar::TRCamera::orig = GStar::Vector3(0.0f, 0.0f, 0.0f);
const GStar::Vector3 GStar::TRCamera::u = GStar::Vector3(1.0f, 0.0f, 0.0f);
const GStar::Vector3 GStar::TRCamera::v = GStar::Vector3(0.0f, 1.0f, 0.0f);
const GStar::Vector3 GStar::TRCamera::w = GStar::Vector3(0.0f, 0.0f, 1.0f);
const float GStar::TRCamera::radius = 0.0f;

GStar::TRCamera::TRCamera(float vfov, float aspect)
{
	m_data.lens_radius = radius;
	m_data.m_u = u;
	m_data.m_v = v;
	m_data.m_w = w;
	float theta = vfov * M_PI_OVER_180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	m_data.lower_left_corner = GStar::Vector3(-1*half_width, -1*half_height, -1.0f);
	m_data.horizontal = GStar::Vector3(2*half_width, 0.0f, 0.0f);
	m_data.vertical = GStar::Vector3(0.0f, 2 * half_height, 0.0f);
	m_data.origin = GStar::Vector3(0.0f, 0.0f, 0.0f);
}

GStar::Ray GStar::TRCamera::get_ray(float u, float v) const
{
	Vector3 offset = Vector3(0, 0, 0);
	if (m_data.lens_radius > 0.00001f || m_data.lens_radius < -0.00001f) {
		Vector3 rd = m_data.lens_radius*random_in_unit_circle();
		offset = m_data.m_u * rd.x() + m_data.m_v * rd.y();
	}

	Vector3 direction = m_data.lower_left_corner +
	m_data.horizontal*u + m_data.vertical*v -
	m_data.origin - offset;
	direction.Normalize();
	return Ray(m_data.origin+offset, direction);
}

GStar::TRCamera::TRCamera(const GStar::Vector3 & lookfrom, const GStar::Vector3 & lookat, const GStar::Vector3 & vup, float vfov, float aspect)
{
	m_data.lens_radius = radius;
	m_data.m_u = u;
	m_data.m_v = v;
	m_data.m_w = w;
	float theta = vfov * M_PI_OVER_180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	m_data.origin = lookfrom;
	m_data.m_w = lookfrom - lookat;
	m_data.m_w.Normalize();
	m_data.m_u = Vector3::Cross(vup, m_data.m_w);
	m_data.m_u.Normalize();
	m_data.m_v = Vector3::Cross(m_data.m_w, m_data.m_u);
	m_data.lower_left_corner = m_data.origin - 1 *  m_data.m_w - 1 * half_width * m_data.m_u - 1 * half_height * m_data.m_v;
	m_data.horizontal = 2 * half_width * m_data.m_u;
	m_data.vertical = 2 * half_height *m_data.m_v;
	float a = 0;
}

GStar::TRCamera::TRCamera(const GStar::Vector3 & lookfrom, const GStar::Vector3 & lookat, const GStar::Vector3 & vup, float vfov, float aspect, float aperture, float focus_distance)
{
	m_data.lens_radius = aperture / 2;
	float theta = vfov * M_PI_OVER_180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	m_data.origin = lookfrom;
	m_data.m_w = lookfrom - lookat;
	m_data.m_w.Normalize();
	m_data.m_u = Vector3::Cross(vup, m_data.m_w);
	m_data.m_u.Normalize();
	m_data.m_v = Vector3::Cross(m_data.m_w, m_data.m_u);
	m_data.lower_left_corner = m_data.origin - 1 * focus_distance* m_data.m_w - 1 * half_width *focus_distance* m_data.m_u - 1 * half_height *focus_distance* m_data.m_v;
	m_data.horizontal = 2 * half_width *focus_distance* m_data.m_u;
	m_data.vertical = 2 * half_height*focus_distance*m_data.m_v;
	float a = 0;
}

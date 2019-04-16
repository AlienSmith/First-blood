#pragma once
#include <xmmintrin.h>
namespace GStar {
	class Matrix3 {
	private:
		union
		{
			struct 
			{
				float m_xx, my_xy, my_xz,my_xw, my_yx, my_yy, my_yz,my_yw, my_zx, my_zy, my_zz,my_zw;
			};
			__m128 m_x;
			__m128 m_y;
			__m128 m_z;                 
		};
	};
}
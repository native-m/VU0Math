#ifndef VECTOR4_H
#define VECTOR4_H

#include "VU0MathDefines.h"
#include "VectorConstants.h"

namespace VU0Math
{

class Vector4
{
public:
	union
	{
		struct { float x, y, z, w; };
		Vu0FVector vec;
	};

public:
	Vector4()
	{
		__asm__ __volatile__(
			"lq		$4, 0x0(%0)\n"
			"sq		$4, 0x0(%1)\n"
			:
			: "r" (VectorConstants::vec4Zero), "r" (this->vec)
			: "$4"
		);
	}

	Vector4(float x, float y, float z = 0.f, float w = 0.f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4(float s)
	{
		__asm__ __volatile__(
		"lqc2		vf1, 0x0(%0)\n"
		"mfc1		$s0, %2\n"
		"qmtc2		$s0, vf2\n"
		"vaddx.xyzw	vf3, vf1, vf2\n"
		"sqc2		vf3, 0x0(%1)\n"
		:
		: "r" (VectorConstants::vec4Zero), "r" (vec), "f" (s)
		);
	}

	Vector4 operator=(const Vector4& vec)
	{
		__asm__ __volatile__(
			"lq		$4, 0x0(%0)\n"
			"sq		$4, 0x0(%1)\n"
			:
			: "r" (vec.vec), "r" (this->vec)
			: "$4"
		);
		return *this;
	}

	Vector4 operator+(const Vector4& vec) const
	{
		Vu0FVector ret;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"lqc2		vf2, 0x0(%1)\n"
			"vadd.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "r" (vec.vec), "r" (ret)
		);

		return ret;
	}

	Vector4 operator-(const Vector4& vec) const
	{
		Vu0FVector ret;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"lqc2		vf2, 0x0(%1)\n"
			"vsub.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "r" (vec.vec), "r" (ret)
		);

		return ret;
	}

	Vector4 operator*(const Vector4& vec) const
	{
		Vu0FVector ret;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"lqc2		vf2, 0x0(%1)\n"
			"vmul.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "r" (vec.vec), "r" (ret)
		);

		return ret;
	}

	Vector4 operator/(const Vector4& vec) const
	{
		Vu0FVector ret;

		ret[0] = 1 / vec.x;
		ret[1] = 1 / vec.y;
		ret[2] = 1 / vec.z;
		ret[3] = 1 / vec.w;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"lqc2		vf2, 0x0(%1)\n"
			"vmul.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%1)\n"
			:
			: "r" (this->vec), "r" (ret)
		);

		return ret;
	}

	Vector4 operator+=(const Vector4& vec)
	{
		*this = *this + vec;
		return *this;
	}

	Vector4 operator-=(const Vector4& vec)
	{
		*this = *this - vec;
		return *this;
	}

	Vector4 operator*=(const Vector4& vec)
	{
		*this = *this * vec;
		return *this;
	}

	Vector4 operator/=(const Vector4& vec)
	{
		*this = *this / vec;
		return *this;
	}

	Vector4 operator+(float s) const
	{
		Vu0FVector ret;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"mfc1		$s0, %1\n"
			"qmtc2		$s0, vf2\n"
			"vaddx.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "f" (s), "r" (ret)
		);

		return ret;
	}

	Vector4 operator-(float s) const
	{
		Vu0FVector ret;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"mfc1		$s0, %1\n"
			"qmtc2		$s0, vf2\n"
			"vsubx.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "f" (s), "r" (ret)
		);

		return ret;
	}

	Vector4 operator*(float s) const
	{
		Vu0FVector ret;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"mfc1		$s0, %1\n"
			"qmtc2		$s0, vf2\n"
			"vmulx.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "f" (s), "r" (ret)
		);

		return ret;
	}

	Vector4 operator/(float s) const
	{
		Vu0FVector ret;
		float f = 1 / s;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"mfc1		$s0, %1\n"
			"qmtc2		$s0, vf2\n"
			"vmulx.xyzw	vf3, vf1, vf2\n"
			"sqc2		vf3, 0x0(%2)\n"
			:
			: "r" (this->vec), "f" (f), "r" (ret)
		);

		return ret;
	}

	Vector4 operator+=(float s)
	{
		*this = *this + s;
		return *this;
	}

	Vector4 operator-=(float s)
	{
		*this = *this - s;
		return *this;
	}

	Vector4 operator*=(float s)
	{
		*this = *this * s;
		return *this;
	}

	Vector4 operator/=(float s)
	{
		*this = *this / s;
		return *this;
	}

	float lengthSq() const
	{
		float f;
		Vu0FVector tmp;

		__asm__ __volatile__(
			"lqc2		vf1, 0x0(%0)\n"
			"vmul		vf2, vf1, vf1\n"
			"sqc2		vf2, 0x0(%1)\n"
			:
			: "r" (this->vec), "r" (tmp)
		);

		// help me
		f = tmp[0] + tmp[1] + tmp[2] + tmp[3];

		return f;
	}

	float dot() const
	{
		return lengthSq(); // lel
	}

	float length()
	{
		return sqrtf(lengthSq());
	}

private:
	Vector4(Vu0FVector v)
	{
		__asm__ __volatile__(
			"lq		$4, 0x0(%0)\n"
			"sq		$4, 0x0(%1)\n"
			:
			: "r" (v), "r" (this->vec)
			: "$4"
		);
	}
};

}

#endif

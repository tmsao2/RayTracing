#include "Plane.h"

Plane::Plane(Vector3 & no, float off, const Material& m):Object(m)
{
	_normal = no;
	_offset = off;
}

Plane::~Plane()
{
}

const Material & Plane::GetMaterial() const
{
	return material;
}

bool Plane::CheckHit(const RayLine & ray, Vector3 & pos, Vector3 & normal)
{
	auto r_ray = ray.vector* -1;
	if (Dot(r_ray, _normal.Normalized()) > 0)
	{
		auto t = (_offset - Dot(ray.start, _normal.Normalized())) / Dot(r_ray, _normal.Normalized());
		pos = ray.start + ray.vector*t;
		return true;
	}
	return false;
}

float Plane::DistanceFromStart(const Vector3 & pos)
{
	return 0.0f;
}


#include "Sphere.h"
#include <math.h>

Sphere::Sphere(Vector3& pos, float r, const Material& m):Object(m)
{
	_pos = pos;
	_radius = r;
}

Sphere::~Sphere()
{
}

const Material & Sphere::GetMaterial() const
{
	return material;
}

bool Sphere::CheckHit(const RayLine & ray, Vector3 & pos, Vector3 & normal)
{
	//視点から球体中心へのベクトル(視線)を作ります
	auto c = _pos - ray.start;		//中心へのベクトル
	auto dot = Dot(c, ray.vector);	//中心から視線への内積をとります＝＞ベクトル長
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
	auto vp = ray.vector * dot;

	if ((c - vp).Magnitude() <= _radius)
	{
		auto w = sqrt(pow(_radius,2) - (c - vp).Magnitude()*(c - vp).Magnitude());
		pos = ray.start + ray.vector * (dot - w);
		normal = (pos - _pos).Normalized();
		return true;
	}
	return false;
}

float Sphere::DistanceFromStart(const Vector3 & pos)
{
	return 0.0f;
}

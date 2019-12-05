#include "Sphere.h"

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
	//レイが正規化済みである前提で…
	//ray=垂線へのベクトル
	//視点から球体中心へのベクトル(視線)を作ります
	auto c = _pos - ray.vector;		//中心へのベクトル
								//
								//中心から視線への内積をとります＝＞ベクトル長
	auto dot = Dot(c, ray.start);
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
	auto vp = ray.start * dot;

	if ((c - vp).Magnitude() <= sp.radius)
	{
		auto w = sqrt(sp.radius*sp.radius - (c - vp).Magnitude()*(c - vp).Magnitude());
		t = (dot - w);
		return true;
	}
	return false;
}

float Sphere::DistanceFromStart(const Vector3 & pos)
{
	return 0.0f;
}

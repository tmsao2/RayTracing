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
	//���_���狅�̒��S�ւ̃x�N�g��(����)�����܂�
	auto c = _pos - ray.start;		//���S�ւ̃x�N�g��
	auto dot = Dot(c, ray.vector);	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
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

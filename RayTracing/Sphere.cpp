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
	//���C�����K���ς݂ł���O��Łc
	//ray=�����ւ̃x�N�g��
	//���_���狅�̒��S�ւ̃x�N�g��(����)�����܂�
	auto c = _pos - ray.vector;		//���S�ւ̃x�N�g��
								//
								//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	auto dot = Dot(c, ray.start);
	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
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

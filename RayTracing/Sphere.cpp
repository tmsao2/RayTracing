#include "Sphere.h"

Sphere::Sphere(Vector3& pos, float r, const Material& m):Object(m)
{
	_pos = pos;
	_radius = r;
}

Sphere::~Sphere()
{
}

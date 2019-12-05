#include "Plane.h"

Plane::Plane(Vector3 & no, float off, const Material& m):Object(m)
{
	_normal = no;
	_offset = off;
}

Plane::~Plane()
{
}


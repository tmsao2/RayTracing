#include "Material.h"



Material::Material()
{
	diffuse=Vector3(1, 1, 1);
	specular = Vector3(0, 0, 0);
	ambient = Vector3(0, 0, 0);
	specularity = 0;
	reflectance = 0;
}

Material::Material(Vector3 & diff, Vector3 & spec, Vector3 & amb, float power, float reflect)
{
	diffuse = diff;
	specular = spec;
	ambient = amb;
	specularity = power;
	reflectance = reflect;
}

Material::~Material()
{
}

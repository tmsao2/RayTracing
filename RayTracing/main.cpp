#include<dxlib.h>
#include <math.h>
#include <vector>
#include"Geometry.h"
#include "Plane.h"
#include "Sphere.h"
const int screen_width = 640;
const int screen_height = 480;

//�q���g�ɂȂ�Ǝv���āA�F�X�Ɗ֐���p�ӂ��Ă���܂���
//�ʂɂ��̊֐����g��Ȃ���΂����Ȃ��킯�ł��A����ɉ���Ȃ���΂����Ȃ��킯�ł�
//����܂���B���C�g���[�V���O���ł��Ă���΍\���܂���B

///���C(����)�Ƌ��̂̓����蔻��
///@param ray (���_����X�N���[���s�N�Z���ւ̃x�N�g��)
///@param sphere ��
///@hint ���C�͐��K�����Ƃ����ق����g���₷�����낤

Vector3 RefrectVector(const Vector3& in, const Vector3& normal)
{
	return in - normal * Dot(normal, in) * 2;
}

void
DrawPixelwithFloat(int x, int y, Vector3 color) {
	DrawPixel(x, y, GetColor(color.x * 0xff, color.y * 0xff, color.z * 0xff));
}

Vector3 Clamp(const Vector3& value,float minVal = 0.0f,float maxVal = 1.0f) {
	return Vector3 ( min(max(value.x , minVal), maxVal),
		min(max(value.y, minVal), maxVal),
		min(max(value.z, minVal), maxVal) );
}

Vector3 CalculateColor(const Vector3& albedo, const float diffuse, const float specular, const float ambient) {
	Vector3 color = Clamp(albedo*(diffuse + ambient) + Vector3(specular, specular, specular));
	return color;
}

Vector3 GetCheckerColor(Position3 pos,float x)
{
	if (x < screen_width/2)
	{
		if (((int)(pos.x / 50) + (int)(pos.z / 50)) % 2)
		{
			return Vector3(1, 1, 1);
		}
		if (!(((int)(pos.x / 50) + (int)(pos.z / 50)) % 2))
		{
			return Vector3(0, 0, 0);
		}
	}
	else
	{
		if (((int)(pos.x / 50) + (int)(pos.z / 50)) % 2)
		{
			return Vector3(0, 0, 0);
		}
		if (!(((int)(pos.x / 50) + (int)(pos.z / 50)) % 2))
		{
			return Vector3(1, 1, 1);
		}
	}
	
}



///���C�g���[�V���O
///@param eye ���_���W
///@param sphere ���I�u�W�F�N�g(���̂��������ɂ���)
void RayTracing(Vector3 toLight,const Vector3& eye,std::vector<Object*>& objects) 
{
	auto light = toLight.Normalized();

	for (int y = 0; y < screen_height; ++y) 
	{
		for (int x = 0; x < screen_width; ++x) 
		{
			Vector3 ray = (Vector3(x - screen_width / 2, screen_height / 2 - y, 0) - eye).Normalized();
			auto normal = Vector3(0, 0, 0);		//�@���x�N�g��
			float t;
			Vector3 hitPos;
			Vector3 sPos = Vector3(0, 0, 0);
			Vector3 pPos = Vector3(0, 0, 0);
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B
			if (objects[1]->CheckHit(RayLine(hitPos,ray),hitPos,normal))
			{
				if(objects[0]->CheckHit(RayLine(eye, ray), hitPos,normal))
				{
					if (objects[0]->DistanceFromStart(eye) >= objects[1]->DistanceFromStart(eye))
					{
						//DrawPixelwithFloat(x, y, GetCheckerColor(hitPos, x)*0.3f);
					}
				}
				else
				{
					DrawPixelwithFloat(x, y, GetCheckerColor(hitPos, x));
				}
			}
			if (objects[0]->CheckHit(RayLine(eye,ray), hitPos, normal))
			{
				auto material = objects[0]->GetMaterial();
				Vector3 albedo = { 1.0f,0.5f,0.5f };
				auto diffuse = Dot(normal,light);
				auto mirror = RefrectVector(light,normal);
				auto reflect = RefrectVector(ray, normal);
				auto specular = pow(max(Dot(mirror.Normalized(), ray), 0), 20);
				reflect.Normalize();
				if (objects[1]->CheckHit(RayLine(hitPos,reflect), hitPos, normal))
				{
					albedo = albedo * GetCheckerColor(hitPos,x);
				}
				if (objects[0]->DistanceFromStart(eye) >= objects[1]->DistanceFromStart(eye))
				{
					DrawPixelwithFloat(x, y, CalculateColor(albedo, diffuse, specular, 0));
				}
			}
		}
	}
}

int main() {
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("1701377_���{�^��"));
	DxLib_Init();
	std::vector<Object*> objects;
	objects.push_back(new Sphere(Vector3(0, 0, -200),100,
		Material(Vector3(1.0f, 0.7f, 0.7f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f), 10.0f, 1.0f)));
	objects.push_back(new Plane(Vector3(0, 1, 0), -100,
		Material(Vector3(1.0f, 0.7f, 0.7f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f), 10.0f, 1.0f)));
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();
		
		RayTracing(Vector3(-0.5f, 0.5f, 0.5f),Vector3(0, 0, 300),objects);

		ScreenFlip();
	}
	WaitKey();
	DxLib_End();
}
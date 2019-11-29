#include<dxlib.h>
#include <math.h>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//�q���g�ɂȂ�Ǝv���āA�F�X�Ɗ֐���p�ӂ��Ă���܂���
//�ʂɂ��̊֐����g��Ȃ���΂����Ȃ��킯�ł��A����ɉ���Ȃ���΂����Ȃ��킯�ł�
//����܂���B���C�g���[�V���O���ł��Ă���΍\���܂���B

///���C(����)�Ƌ��̂̓����蔻��
///@param ray (���_����X�N���[���s�N�Z���ւ̃x�N�g��)
///@param sphere ��
///@hint ���C�͐��K�����Ƃ����ق����g���₷�����낤
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp,float& t) {
	//���C�����K���ς݂ł���O��Łc
	//ray=�����ւ̃x�N�g��
	//���_���狅�̒��S�ւ̃x�N�g��(����)�����܂�
	auto c = sp.pos - eye;		//���S�ւ̃x�N�g��
	//
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	auto dot = Dot(c, ray);
	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
	auto vp = ray * dot;

	if ((c-vp).Magnitude()<=sp.radius)
	{
		auto w = sqrt(sp.radius*sp.radius - (c - vp).Magnitude()*(c - vp).Magnitude());
		t=(dot - w);
		return true;
	}
	
	return false;
}

Vector3 RefrectVector(const Vector3& in, const Vector3& normal)
{
	return in - normal * Dot(normal, in) * 2;
}

bool IsHitRayAndObject(const Position3& eye,const Vector3& ray, const Plane& pl,float& t)
{
	auto plane = pl;
	auto r_ray = ray * -1;
	if (Dot(r_ray, plane.normal.Normalized()) > 0)
	{
		t = (plane.offset - Dot(eye, plane.normal.Normalized())) / Dot(r_ray, plane.normal.Normalized());
		return true;
	}
	return false;
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
			return Vector3(1, 1, 0);
		}
		if (!(((int)(pos.x / 50) + (int)(pos.z / 50)) % 2))
		{
			return Vector3(1, 0, 0);
		}
	}
	else
	{
		if (((int)(pos.x / 50) + (int)(pos.z / 50)) % 2)
		{
			return Vector3(1, 0, 0);
		}
		if (!(((int)(pos.x / 50) + (int)(pos.z / 50)) % 2))
		{
			return Vector3(1, 1, 0);
		}
	}
	
}



///���C�g���[�V���O
///@param eye ���_���W
///@param sphere ���I�u�W�F�N�g(���̂��������ɂ���)
void RayTracing(const Position3& eye,const Sphere& sphere,const Plane& plane) {
	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			Position3 screenPos(x-screen_width/2, screen_height/2-y, 0);
			auto ray = screenPos - eye;			//�����x�N�g��
			auto toLight = Vector3(-0.5f,0.5f,0.5f);		//�����x�N�g��
			auto normal = Vector3(0, 0, 0);		//�@���x�N�g��
			ray.Normalize();
			toLight.Normalize();
			float t;
			Vector3 sPos = Vector3(0, 0, 0);
			Vector3 pPos = Vector3(0, 0, 0);
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B
			if (IsHitRayAndObject(eye, ray, plane, t))
			{
				pPos = eye + (-ray)*t;
				if(IsHitRayAndObject(pPos, toLight, sphere, t))
				{
					if (sPos.y >= pPos.y)
					{
						DrawPixelwithFloat(x, y, GetCheckerColor(pPos, x)*0.3f);
					}
				}
				else
				{
					DrawPixelwithFloat(x, y, GetCheckerColor(pPos, x));
				}
			}
			if (IsHitRayAndObject(eye,ray,sphere, t))
			{
				sPos = eye + ray * t;
				normal = sPos - sphere.pos;
				normal.Normalize();
				Vector3 albedo = { 1.0f,1.0f,1.0f };
				auto diffuse = Dot(normal, toLight);
				auto mirror = RefrectVector(toLight,normal);
				auto reflect = RefrectVector(ray, normal);
				auto specular = pow(max(Dot(mirror.Normalized(), ray), 0), 20);
				reflect.Normalize();
				if (IsHitRayAndObject(sPos, reflect, plane, t))
				{
					Vector3 rPos = eye + (-ray)*t;
					albedo = albedo * GetCheckerColor(rPos,x);
				}
				if (sPos.z >= pPos.z)
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
	float x = 0, y = 50,z=0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();
		if (CheckHitKey(KEY_INPUT_UP))
		{
			y+=10;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y-=10;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x+=10;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x-=10;
		}
		RayTracing(Vector3(0, 100, 300), Sphere(100, Position3(x, y, z)), Plane(Vector3(0, 1, 0), -50));

		ScreenFlip();
	}
	WaitKey();
	DxLib_End();
}
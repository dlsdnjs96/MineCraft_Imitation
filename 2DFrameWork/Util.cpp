#include "framework.h"

//////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열에서 comp 문자를 rep로 변경
///@param str : 체크하려는 문자열
///@param comp : 비교문자열
///@param rep : 바꿀문자열
//////////////////////////////////////////////////////////////////////////
void Util::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

void Util::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief string형을 wstring형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
wstring Util::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring형을 string형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
string Util::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}

float Util::NormalizeAngle(float angle)
{
	while (angle > PI)
		angle -= PI_2;
	while (angle < -PI)
		angle += PI_2;
	return angle;
}

Vector3 Util::NormalizeAngles(Vector3 angles)
{
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

Vector3 Util::QuaternionToYawPtichRoll(Quaternion q1)
{
	float sqw = q1.w * q1.w;
	float sqx = q1.x * q1.x;
	float sqy = q1.y * q1.y;
	float sqz = q1.z * q1.z;
	float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor

	float test = q1.x * q1.w - q1.y * q1.z;
	Vector3 v;
	if (test > 0.4995f * unit) { // singularity at north pole

		v.y = 2.0f * atan2f(q1.y, q1.x);
		v.x = PI / 2.0f;
		v.z = 0;
		return NormalizeAngles(v);
	}

	if (test < -0.4995f * unit) { // singularity at south pole

		v.y = -2.0f * atan2f(q1.y, q1.x);
		v.x = -PI / 2.0f;
		v.z = 0;
		return NormalizeAngles(v);
	}

	Quaternion q = Quaternion(q1.w, q1.z, q1.x, q1.y);
	// Yaw
	v.y = atan2f(2.0f * q.x * q.w + 2.0f * q.y * q.z, 1.0f - 2.0f * (q.z * q.z + q.w * q.w));
	// Pitch
	v.x = asinf(2.0f * (q.x * q.z - q.w * q.y));
	// Roll
	v.z = atan2f(2.0f * q.x * q.y + 2.0f * q.z * q.w, 1.0f - 2.0f * (q.y * q.y + q.z * q.z));

	return NormalizeAngles(v);
}

bool Util::RayIntersectTri(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint)
{
	if (not Target->mesh)return false;

	Matrix inverse = Target->W.Invert();
	WRay.direction = Vector3::TransformNormal(WRay.direction, inverse);
	WRay.direction.Normalize();

	WRay.position = Vector3::Transform(WRay.position, inverse);

	for (UINT i = 0; i < Target->mesh->GetIndexCount(); i += 3)
	{
		Vector3 v[3];
		v[0] = Target->mesh->GetVertexPosition(i);
		v[1] = Target->mesh->GetVertexPosition(i + 1);
		v[2] = Target->mesh->GetVertexPosition(i + 2);

		float Dis;
		if (WRay.Intersects(v[0], v[1], v[2], Dis))
		{
			//                         스칼라 x 방향
			HitPoint = WRay.position +  (WRay.direction * Dis);
			//다시 W 로 변환
			HitPoint = Vector3::Transform(HitPoint, Target->W);
			return true;
		}
	}
	return false;


}

bool Util::RayIntersectTriNear(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint)
{
	if (not Target->mesh)return false;

	Matrix inverse = Target->W.Invert();
	WRay.direction = Vector3::TransformNormal(WRay.direction, inverse);
	WRay.direction.Normalize();
	WRay.position = Vector3::Transform(WRay.position, inverse);

	float Dis = FLT_MAX;
	for (UINT i = 0; i < Target->mesh->GetIndexCount(); i += 3)
	{
		Vector3 v[3];
		v[0] = Target->mesh->GetVertexPosition(i);
		v[1] = Target->mesh->GetVertexPosition(i + 1);
		v[2] = Target->mesh->GetVertexPosition(i + 2);

		float temp;
		if (WRay.Intersects(v[0], v[1], v[2], temp))
		{
			if (Dis > temp)
			{
				Dis = temp;
				//                         스칼라 x 방향
				HitPoint = WRay.position + (WRay.direction * temp);
				//다시 W 로 변환
				HitPoint = Vector3::Transform(HitPoint, Target->W);
			}
		}
	}
	if (Dis == FLT_MAX)
		return false;
	else
		return true;
}

int Util::RayIntersectSquareNear(IN Ray WRay, IN GameObject* Target)
{
	if (not Target->mesh)return -1;

	Matrix inverse = Target->W.Invert();
	WRay.direction = Vector3::TransformNormal(WRay.direction, inverse);
	WRay.direction.Normalize();
	WRay.position = Vector3::Transform(WRay.position, inverse);

	float Dis = FLT_MAX;
	int vertexIndex = -1;
	//printf("Target->mesh->GetIndexCount() %d\r\n", Target->mesh->GetIndexCount());
	for (UINT i = 0; i < Target->mesh->GetIndexCount(); i += 3)
	{
		Vector3 v[3];
		v[0] = Target->mesh->GetVertexPosition(i);
		v[1] = Target->mesh->GetVertexPosition(i + 1);
		v[2] = Target->mesh->GetVertexPosition(i + 2);

		float temp;
		if (WRay.Intersects(v[0], v[1], v[2], temp))
		{
			if (Dis > temp)
			{
				Dis = temp;
				vertexIndex = i / 6;
			}
		}
	}
	return vertexIndex;
}

bool Util::RayIntersectMap(IN Ray WRay, IN GameObject* Terrain, OUT Vector3& HitPoint)
{
	if (not Terrain->mesh)return false;
	//역행렬 구하기
	Matrix inverse = Terrain->W.Invert();

	//w=0
	WRay.direction = Vector3::TransformNormal(WRay.direction, inverse);
	WRay.direction.Normalize();
	//w=1
	WRay.position = Vector3::Transform(WRay.position, inverse);

	//Terrain 중심점 0,0,0이 가운데가 아닌 왼쪽상단이 0,0,0이 되게끔 이동

	int terrainSize = (int)sqrt(Terrain->mesh->vertexCount);
	float half = terrainSize * 0.5f;
	int TerrainIdxX , TerrainIdxZ;
	TerrainIdxX = WRay.position.x + half;
	TerrainIdxZ = -(WRay.position.z - half);

	if (TerrainIdxX < 0 or TerrainIdxZ < 0 or
		TerrainIdxX >= terrainSize - 1 or TerrainIdxZ >= terrainSize - 1)
	{
		//cout << "OutofRange" << endl;
		return false;
	}
	//사각형 인덱스
	int index = (terrainSize - 1) * TerrainIdxZ + TerrainIdxX;
	//사각형의 첫번째 정점 인덱스
	index *= 6;

	for (int i = 0; i < 6; i += 3)
	{
		Vector3 v[3];
		v[0] = Terrain->mesh->GetVertexPosition(index + i);
		v[1] = Terrain->mesh->GetVertexPosition(index + i + 1);
		v[2] = Terrain->mesh->GetVertexPosition(index + i + 2);

		float Dis;
		if (WRay.Intersects(v[0], v[1], v[2], Dis))
		{
			//                         스칼라 x 방향
			HitPoint = WRay.position + Dis * WRay.direction;
			//다시 W 로 변환
			HitPoint = Vector3::Transform(HitPoint, Terrain->W);
			return true;
		}
	}
	return false;
}

Ray Util::MouseToRay(Vector3 Mouse, Camera* Cam)
{
	Mouse.x -= Cam->viewport.x;
	Mouse.y -= Cam->viewport.y;
	Vector2 MousePos;

	//ndc로의 변환
	MousePos.x = ((2.0f * Mouse.x) / Cam->viewport.width - 1.0f);
	MousePos.y = ((-2.0f * Mouse.y) / Cam->viewport.height + 1.0f);

	// view로의 변환
	MousePos.x /= Cam->proj._11;
	MousePos.y /= Cam->proj._22;

	Ray CamToMouse;
	CamToMouse.position = Cam->GetWorldPos();
	CamToMouse.direction = Vector3(MousePos.x, MousePos.y, 1.0f);
	Matrix inverse = Cam->view.Invert();
	CamToMouse.direction = Vector3::TransformNormal(CamToMouse.direction, inverse);
	CamToMouse.direction.Normalize();
	return CamToMouse;
}

Ray Util::AimToRay(Camera* Cam)
{
	Vector2 MousePos;

	//ndc로의 변환
	MousePos.x = ((2.0f * (App.GetHalfWidth() - Cam->viewport.x)) / Cam->viewport.width - 1.0f);
	MousePos.y = ((-2.0f * (App.GetHalfHeight() - Cam->viewport.y)) / Cam->viewport.height + 1.0f);

	// view로의 변환
	MousePos.x /= Cam->proj._11;
	MousePos.y /= Cam->proj._22;

	Ray CamToAim;
	CamToAim.position = Cam->GetWorldPos();
	CamToAim.direction = Vector3(MousePos.x, MousePos.y, 1.0f);
	Matrix inverse = Cam->view.Invert();
	CamToAim.direction = Vector3::TransformNormal(CamToAim.direction, inverse);
	CamToAim.direction.Normalize();
	return CamToAim;
}


void Util::NdcToScreen(Vector3& pos)
{
	pos.x = (pos.x + 1.f) * App.GetHalfWidth();
	pos.y = (pos.y - 1.f) * -App.GetHalfHeight();
}

void Util::ScreenToNdc(Vector3& pos)
{
	pos.x = pos.x / App.GetHalfWidth() - 1.0f;
	pos.y = pos.y / -App.GetHalfHeight() + 1.0f;
}

bool Util::WorldToScreen(Vector3 pos, Vector2& screen, Matrix matrix, int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vector4 clipCoords;
	clipCoords.x = pos.x * matrix._11 + pos.y * matrix._21 + pos.z * matrix._31 + matrix._41;
	clipCoords.y = pos.x * matrix._12 + pos.y * matrix._22 + pos.z * matrix._32 + matrix._42;
	clipCoords.z = pos.x * matrix._13 + pos.y * matrix._23 + pos.z * matrix._33 + matrix._43;
	clipCoords.w = pos.x * matrix._14 + pos.y * matrix._24 + pos.z * matrix._34 + matrix._44;
	/*
	clipCoords.x = pos.x * matrix._11 + pos.y * matrix._12 + pos.z * matrix._13 + matrix._14;
	clipCoords.y = pos.x * matrix._21 + pos.y * matrix._22 + pos.z * matrix._23 + matrix._24;
	clipCoords.z = pos.x * matrix._31 + pos.y * matrix._32 + pos.z * matrix._33 + matrix._34;
	clipCoords.w = pos.x * matrix._41 + pos.y * matrix._42 + pos.z * matrix._43 + matrix._44;*/

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

bool Util::IsInScreen(Vector3 pos, Matrix matrix)
{
	Vector4 clipCoords;
	clipCoords.x = pos.x * matrix._11 + pos.y * matrix._21 + pos.z * matrix._31 + matrix._41;
	clipCoords.y = pos.x * matrix._12 + pos.y * matrix._22 + pos.z * matrix._32 + matrix._42;
	clipCoords.z = pos.x * matrix._13 + pos.y * matrix._23 + pos.z * matrix._33 + matrix._43;
	clipCoords.w = pos.x * matrix._14 + pos.y * matrix._24 + pos.z * matrix._34 + matrix._44;

	if (clipCoords.w < 0.1f)
		return false;
	if (abs(clipCoords.x / clipCoords.w) > 1.0f or abs(clipCoords.y / clipCoords.w) > 1.0f)
		return false;
	return true;
}

void Util::ClipWindow(bool on)
{
	if (on) {
		RECT rtRect;
		POINT p1, p2;
		GetClientRect(App.GetHandle(), &rtRect);
		p1.x = rtRect.left; p1.y = rtRect.top; p2.x = rtRect.right; p2.y = rtRect.bottom;
		ClientToScreen(App.GetHandle(), &p1);
		ClientToScreen(App.GetHandle(), &p2); rtRect.left = p1.x; rtRect.top = p1.y; rtRect.right = p2.x; rtRect.bottom = p2.y;
		ClipCursor(&rtRect);
	} else
		ClipCursor(nullptr);
}

void Util::CursorVisible(bool _on)
{
	static int count = 1;

	if (_on)
	{
		while (count < 0)
		{
			ShowCursor(true);
			count++;
		}
	}
	else {
		while (count >= 0)
		{
			ShowCursor(false);
			count--;
		}
	}
}

void Util::LockMouse()
{
	POINT cursor;
	GetCursorPos(&cursor);
	INPUT->fixedMousePos = cursor;
	INPUT->prevPosition = INPUT->position;
	Util::CursorVisible(false);
	return;
}

void Util::UnLockMouse()
{
	INPUT->fixedMousePos = { -1, -1 };
	Util::CursorVisible(true);
	return;
}




float Util::SmoothNoise(int x, int y) // -4.f ~ 4.f
{
	return (noise2(x - 1, y - 1) + noise2(x + 1, y - 1) + noise2(x - 1, y + 1) + noise2(x + 1, y + 1))
	+((noise2(x - 1, y) + noise2(x + 1, y) + noise2(x, y + 1) + noise2(x, y - 1)) / 8.f)
		+ (noise2(x, y) / 4.f);
}
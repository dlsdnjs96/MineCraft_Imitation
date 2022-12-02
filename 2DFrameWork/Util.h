#pragma once
namespace Util
{

	void Replace(string* str, string comp, string rep);
	void Replace(wstring* str, wstring comp, wstring rep);

	wstring ToWString(string value);
	string ToString(wstring value);

	float NormalizeAngle(float angle);
	Vector3 NormalizeAngles(Vector3 angles);
	Vector3 QuaternionToYawPtichRoll(Quaternion q1);


	bool RayIntersectTri(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint);

	bool RayIntersectTriNear(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint);
	int RayIntersectSquareNear(IN Ray WRay, IN GameObject* Target);

	//수직으로 내다 꽂은 레이만 사용할것
	bool RayIntersectMap(IN Ray WRay, IN GameObject* Terrain, OUT Vector3& HitPoint);


	Ray MouseToRay(Vector3 Mouse, Camera* Cam);
	Ray AimToRay(Camera* Cam);

	template<typename T>
	//			3     5  
	T Lerp(T from, T to, float value)
	{
		return from + (to - from) * value;
	}
	template<typename T>
	T Quadratic(T p1, T p2, T p3, float value)
	{
		return Lerp(Lerp(p1, p2, value), Lerp(p2, p3, value), value);
	}
	template<typename T>
	T Cubic(T p1, T p2, T p3, T p4, float value)
	{
		return Quadratic(Lerp(p1, p2, value), Lerp(p2, p3, value), 
			Lerp(p3, p4, value), value);
	}
	template <typename T>
	static T Saturate(T& in, T min = 0, T max = 1)
	{
		if (in < min)
		{
			in = min;
			return min;
		}
		else if (in > max)
		{
			in = max;
			return max;
		}
		return in;
	}


	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	inline float noise1(int x)
	{
		x = (x << 13) ^ x;
		return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 107374);
	}

	inline float noise2(int x, int y)
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		return 1.f - ((float)nn / 1073741824.f);
	}

	float SmoothNoise(int x, int y);

	void NdcToScreen(Vector3& pos);
	void ScreenToNdc(Vector3& pos);
	bool WorldToScreen(Vector3 pos, Vector2& screen, Matrix matrix, int windowWidth, int windowHeight);
	bool IsInScreen(Vector3 pos, Matrix matrix);

	void ClipWindow(bool on);

	void CursorVisible(bool _on);
	void LockMouse();
	void UnLockMouse();
}
#pragma once


class Application
{
	friend class Direct3D11;
	friend class Window;
	friend class Gui;
	friend class Input;
private:
	float		x, y;
	float		width;
	float		height;
	HINSTANCE	instance;
	HWND		handle;
	wstring		appName;
	bool		fullScreen;
public:
	bool		vSync;
	Color		background;
	int			fixFrame;
	float		deltaScale;
	float		soundScale;
public:
	Application() :instance(nullptr), handle(nullptr), vSync(false), fullScreen(false)
		, appName(L" "), width(1280.0f), height(720.0f), background(Color(0.7f, 0.7f, 0.7f, 1.0f))
		, fixFrame(400), deltaScale(1.0f), soundScale(1.0f),x(0.0f),y(0.0f) {}
	HWND	GetHandle() { return handle; }
	float	GetWidth() { return width; }
	float	GetHeight() { return height; }
	float	GetHalfWidth() { return width / 2.0f; }
	float	GetHalfHeight() { return height / 2.0f; }
	void	SetInstance(HINSTANCE instance)
	{ 
		if(!this->instance)
		this->instance = instance;
	}
	void	SetAppName(wstring appName) 
	{ 
		if (this->appName == L" ")
		this->appName = appName; 
	}
	//해상도변경은 D3D의 리사이즈 함수 이용!
};

template <typename T>
class Singleton
{
	//static
private:
	static T* instance;
public:
	static T* GetInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	};
	//member
public:
	virtual ~Singleton() {};
	void DeleteSingleton()
	{
		delete instance;
		instance = nullptr;
	};
};
template <typename T>
T* Singleton<T>::instance = nullptr;

//씬타입으로는 객체를만들수 없다.

enum class SceneState
{
	NONE,
	FADEIN,
	FADEOUT
};
class Scene
{
public:
	SceneState	state = SceneState::NONE;
	float		passedTime;
	virtual ~Scene() {};
	//초기화
	virtual void Init() = 0;
	//해제
	virtual void Release() = 0;
	//Loop
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	//Window Resize
	virtual void ResizeScreen() = 0;

};


struct Int2
{
	int x;
	int y;
	Int2()
	{
		x = 0;
		y = 0;
	}
	Int2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator ==(Int2 dest)
	{
		return (x == dest.x && y == dest.y);
	}
	bool operator !=(Int2 dest)
	{
		return (x != dest.x || y != dest.y);
		//return !(*this == dest);
	}
	const Int2 operator * (const int rv)
	{
		x *= rv;
		y *= rv;
		return *this;
	}
	const Int2 operator / (const int rv)
	{
		x /= rv;
		y /= rv;
		return *this;
	}
};

struct Int3
{
	int x, y, z;
	Int3() { x = 0; y = 0; z = 0; }
	Int3(int _x, int _y, int _z) { x = _x; y = _y; z = _z; }
	Int3(Vector3 pos) {
		x = static_cast<int>(roundf(pos.x));
		y = static_cast<int>((pos.y));
		z = static_cast<int>(roundf(pos.z));
	}
	Vector3 GetVector3()
	{
		return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	}
	Int3 operator += (Int3 rv)
	{
		return { x + rv.x , y + rv.y , z + rv.z };
	}
	Int3 operator -= (Int3 rv)
	{
		return { x - rv.x , y - rv.y , z - rv.z };
	}
	Int3 operator *= (Int3 rv)
	{
		return { x * rv.x , y * rv.y , z * rv.z };
	}
	Int3 operator /= (Int3 rv)
	{
		return { x / rv.x , y / rv.y , z / rv.z };
	}

	const Int3 operator + (const Int3 rv)
	{
		return { x + rv.x, y + rv.y, z + rv.z };
	}
	const Int3 operator - (const Int3 rv)
	{
		return { x - rv.x, y - rv.y, z - rv.z };
	}
	const Int3 operator * (const Int3 rv)
	{
		return { x * rv.x, y * rv.y, z * rv.z };
	}
	const Int3 operator / (const Int3 rv)
	{
		return { x / rv.x, y / rv.y, z / rv.z };
	}

	//Int3 operator + (Int3& p) {
	//	x = x + p.x;
	//	y = y + p.y;
	//	z = z + p.z;
	//	return Int3(x, y, z);
	//}
	//Int3 operator - (Int3& p) {
	//	x = x - p.x;
	//	y = y - p.y;
	//	z = z - p.z;
	//	return Int3(x, y, z);
	//}
	//Int3 operator * (Int3& p) {
	//	x = x * p.x;
	//	y = y * p.y;
	//	z = z * p.z;
	//	return Int3(x, y, z);
	//}
	//Int3 operator / (Int3& p) {
	//	x = x / p.x;
	//	y = y / p.y;
	//	z = z / p.z;
	//	return Int3(x, y, z);
	//}

	Int3 operator *= (int divide)
	{
		return { x * divide , y * divide , z * divide };
	}
	Int3& operator *= (float rv)
	{
		x *= rv;
		y *= rv;
		z *= rv;
		return *this;
	}
	Int3& operator /= (int rv)
	{
		x /= rv;
		y /= rv;
		z /= rv;
		return *this;
	}
	Int3& operator /= (float rv)
	{
		x /= rv;
		y /= rv;
		z /= rv;
		return *this;
	}
	bool operator == (const Int3& rv)
	{
		return x == rv.x and y == rv.y and z == rv.z;
	}
	bool operator != (const Int3& rv)
	{
		return x != rv.x or y == rv.y or z != rv.z;
	}

	const Int3 operator * (const int rv)
	{
		x *= rv;
		y *= rv;
		z *= rv;
		return *this;
	}
	const Int3 operator / (const int rv)
	{
		x /= rv;
		y /= rv;
		z /= rv;
		return *this;
	}
	const Int3 operator * (const float rv)
	{
		x *= rv;
		y *= rv;
		z *= rv;
		return *this;
	}
	const Int3 operator / (const float rv)
	{
		x /= rv;
		y /= rv;
		z /= rv;
		return *this;
	}
};
#pragma once

#define TASK_MOUSE_FIX		0b000000000001
#define TASK_MOUSE_UNFIX	0b000000000010
#define TASK_MOUSE_LOCKUP	0b000000000100
#define TASK_MOUSE_UNLOCKUP	0b000000001000

class Window :public Singleton<Window>
{
	//static
private:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);


	//member
private:
	static Scene* main;
public:
	void	Create();
	void	Destroy();
	WPARAM	Run(Scene* main);
	void	Load();
	void	Save();
};


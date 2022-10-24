﻿#pragma once
//Popup Console
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

//C
#include <Windows.h>
#include <assert.h>

//C++
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <thread>
#include <mutex>
#include <functional>
#include <filesystem>
using namespace std;

//DirectX d3d 11
#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

//D2D
#include <d2d1_1.h>
#pragma comment(lib, "d2d1.lib")

//Direct Write
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

//DirectXTk 
#include "../Libs/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

//DirectXTex
#include "../Libs/DirectXTex/DirectXTex.h"
#pragma comment(lib, "../Libs/DirectXTex/DirectXTex.lib")

//Imgui
#include "../Libs/ImGui/imgui.h"
#include "../Libs/ImGui/imgui_internal.h"
#include "../Libs/ImGui/imgui_impl_dx11.h"
#include "../Libs/ImGui/imgui_impl_win32.h"
#pragma comment(lib, "../Libs/ImGui/example_win32_directx11.lib")

//Dialog
#include "../Libs/ImGui/dirent.h"
#include "../Libs/ImGui/ImGuiFileDialog.h"
#include "../Libs/ImGui/ImGuiFileDialogConfig.h"

//File
#include "Types.h"
#include "BinaryFile.h"
#include "Xml.h"


//Macro(Pascal)
#define Check(hr)			{ assert(SUCCEEDED(hr)); }
#define SafeRelease(p)		{ if(p){ (p)->Release(); (p) = nullptr; } }
#define SafeDelete(p)		{ if(p){ delete (p); (p) = nullptr; } }
#define SafeDeleteArray(p)	{ if(p){ delete[] (p); (p) = nullptr; } }
#define SafeReset(p)		{ if(p){ (p).reset(); (p) = nullptr; } }
//Macro(WINAPI Style)
#define	TORADIAN			0.0174532f
#define	PI_2				6.2831853f  //360
#define	PI					3.1415926f	//180
#define	PI_DIV2				1.5707963f	//90
#define	PI_DIV4				0.7853981f	//45
#define	PI_DIV8				0.3926991f	//22.5
#define	RIGHT				Vector3(1.0f,0.0f,0.0f)
#define	UP					Vector3(0.0f,1.0f,0.0f)
#define	FORWARD				Vector3(0.0f,0.0f,1.0f)

//2DFramework Header
#include "Window.h"
extern Application App;//Extern Global
#include "Direct3D11.h"
#include "Gui.h"
#include "Input.h"
#include "Timer.h"
#include "Random.h"


#include "VertexType.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Material.h"
#include "Collider.h"
#include "Skeleton.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Dwrite.h"

#include "GameObject.h"
//#include "ObRect.h"
#include "Camera.h"
#include "Dijkstra.h"
#include "Terrain.h"
#include "UI.h"
#include "DepthState.h"

#include "Util.h"

//Singleton Macro
#define	D3D			Direct3D11::GetInstance()
#define	WIN			Window::GetInstance()
#define	GUI			Gui::GetInstance()
#define INPUT		Input::GetInstance()
#define TIMER		Timer::GetInstance()
#define DELTA		Timer::GetInstance()->GetDeltaScaleTime()
#define RANDOM		Random::GetInstance()
#define RESOURCE	ResourceManager::GetInstance()
#define DWRITE		Dwrite::GetInstance()
#define SCENE		SceneManager::GetInstance()
#define DEPTH		DepthState::GetInstance()
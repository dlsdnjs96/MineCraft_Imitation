#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")


#include "MeshFactory.h"


#define WORLD World::GetInstance()
#define WORLD_GENERATOR WorldGenerator::GetInstance()
#define MESH_FACTORY MeshFactory::GetInstance()
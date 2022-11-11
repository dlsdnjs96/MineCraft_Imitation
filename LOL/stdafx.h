#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

#define BLOCK_FACE_UP		0b000001
#define BLOCK_FACE_DOWN		0b000010
#define BLOCK_FACE_RIGHT	0b000100
#define BLOCK_FACE_LEFT		0b001000
#define BLOCK_FACE_FORWARD	0b010000
#define BLOCK_FACE_BEHIND	0b100000

//#define BLOCK_UV_STONE		{ 1.f / 32.f, 0.f / 32.f }

#define BLOCK_LENGTH 10.f
#define SECTOR_SIZE 16
#define WORLD_HEIGHT 64
#define WATER_HEIGHT 15


enum class BlockType
{
	EMPTY		= 0,
	WATER		= 1,
	LEAF		= 2,
	GRASS		= 100,
	STONE		= 101,
	DIRT		= 102,
	SAND		= 103,
	WOOD_OAK	= 104,
	COAL_ORE	= 105,
	IRON_ORE	= 106,

};


#include "Block.h"
#include "TextureData.h"
#include "Sector.h"
#include "World.h"
#include "Item.h"
#include "ItemObject.h"
#include "QuickSlots.h"
#include "Player.h"
#include "WorldGenerator.h"
#include "WorldList.h"
#include "Setting.h"
#include "BlockCollider.h"
#include "ItemManager.h"



#include "LoadingScene.h"
#include "InGameScene.h"
#include "MenuScene.h"


#define WORLD World::GetInstance()
#define WORLD_GENERATOR WorldGenerator::GetInstance()
#define TEXTURE_DATA TextureData::GetInstance()
#define SETTING Setting::GetInstance()
#define ITEM_MANAGER ItemManager::GetInstance()
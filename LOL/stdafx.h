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
#define WATER_HEIGHT 20


enum class BlockType
{
	AIR							= 0,
	FLOWING_WATER				= 1,
	STILL_WATER					= 2,
	LEAVE						= 3,
	SPRUCE_LEAVES				= 4,
	BIRCH_LEAVES				= 5,
	JUNGLE_LEAVES				= 6,
	GLASS						= 7,
	STONE						= 10,
	GRASS_DIRT					= 11,
	DIRT						= 12,
	COBBLESTONE					= 13,
	BEDROCK						= 14,
	FLOWING_LAVA				= 15,
	STILL_LAVA					= 16,
	SAND						= 17,
	GRAVEL						= 18,
	GOLD_ORE					= 19,
	IRON_ORE					= 20,
	COAL_ORE					= 21,
	LAPIS_LAZULI_ORE			= 22,
	LAPIS_LAZULI_BLOCK			= 23,
	DISPENSER					= 24,
	SANDSTONE					= 25,
	COBWEB						= 30,
	GRASS						= 31,
	DANDELION					= 37,
	BROWN_MUSHROOM				= 39,
	RED_MUSHROOM				= 40,
	GOLD_BLOCK					= 41,
	IRON_BLOCK					= 42,
	BRICKS						= 45,
	TNT							= 46,
	BOOKSHELF					= 47,
	MOSS_STONE					= 48,
	OBSIDIAN					= 49,
	TORCH						= 50,
	FIRE						= 51,
	CHEST						= 54,
	DIAMOND_ORE					= 56,
	DIAMOND_BLOCK				= 57,
	CRAFTING_TABLE				= 58,
	WHEAT_CROPS					= 59,
	FARMLAND					= 60,
	FURNACE						= 61,
	BURNING_FURNACE				= 62,
	OAK_DOOR_BLOCK				= 64,
	LADDER						= 65,
	RAIL						= 66,
	SNOW						= 78,
	ICE							= 79,
	SNOW_BLOCK					= 80,
	JUKEBOX						= 84,
	OAK_FENCE					= 85,
	PUMPKIN						= 86,
	PUMPKIN_CARVED				= 87,
	GLOWSTONE					= 89,
	NETHER_PORTAL				= 90,
	JACK_O_LANTERN				= 91,
	CAKE_BLOCK					= 92,
	FARMLAND_WET				= 93,
	OAK_WOOD					= 100,
	SPRUCE_WOOD					= 101,
	BIRCH_WOOD					= 102,
	JUNGLE_WOOD					= 103,
	OAK_WOOD_PLANK				= 104,
	SPRUCE_WOOD_PLANK			= 105,
	BIRCH_WOOD_PLANK			= 106,
	JUNGLE_WOOD_PLANK			= 107,
	ACACIA_WOOD_PLANK			= 108,
	DARK_OAK_WOOD_PLANK			= 109,
	OAK_SAPLING					= 110,
	SPRUCE_SAPLING				= 111,
	BIRCH_SAPLING				= 112,
	JUNGLE_SAPLING				= 113,
	ACACIA_SAPLING				= 114,
	DARK_OAK_SAPLING			= 115,
	WHITE_WOOL					= 120,
	ORANGE_WOOL					= 121,
	MAGENTA_WOOL				= 122,
	LIGHT_BLUE_WOOL				= 123,
	YELLOW_WOOL					= 124,
	LIME_WOOL					= 125,
	PINK_WOOL					= 126,
	GRAY_WOOL					= 127,
	LIGHT_GRAY_WOOL				= 128,
	CYAN_WOOL					= 129,
	PURPLE_WOOL					= 130,
	BLUE_WOOL					= 131,
	BROWN_WOOL					= 132,
	GREEN_WOOL					= 133,
	RED_WOOL					= 134,
	BLACK_WOOL					= 135,
	POPPY						= 140,
	BLUE_ORCHID					= 141,
	ALLIUM						= 142,
	AZURE_BLUET					= 143,
	RED_TULIP					= 144,
	ORANGE_TULIP				= 145,
	WHITE_TULIP					= 146,
	PINK_TULIP					= 147,
	OXEYE_DAISY					= 148,
	STONE_SLAB					= 150,
	SANDSTONE_SLAB				= 151,
	WOODEN_SLAB					= 152,
	COBBLESTONE_SLAB			= 153,
	BRICK_SLAB					= 154,
	STONE_BRICK_SLAB			= 155,
	NETHER_BRICK_SLAB			= 156,
	QUARTZ_SLAB					= 157,
	QUARTZ_STAIRS				= 158,
	ACACIA_WOOD_STAIRS			= 163,
	DARK_OAK_WOOD_STAIRS		= 164,
	SLIME_BLOCK					= 165,
	BARRIER						= 166,
	IRON_TRAPDOOR				= 167,
	SEA_LANTERN					= 169,
	HAY_BALE					= 170,
	HARDENED_CLAY				= 172,
	BLOCK_OF_COAL				= 173,
	PACKED_ICE					= 174,
	SUNFLOWER					= 175,
	RED_SANDSTONE_SLAB			= 182,
	SPRUCE_FENCE_GATE			= 183,
	BIRCH_FENCE_GATE			= 184,
	JUNGLE_FENCE_GATE			= 185,
	DARK_OAK_FENCE_GATE			= 186,
	ACACIA_FENCE_GATE			= 187,
	SPRUCE_FENCE				= 188,
	BIRCH_FENCE					= 189,
	JUNGLE_FENCE				= 190,
	DARK_OAK_FENCE				= 191,
	ACACIA_FENCE				= 192,
	SPRUCE_DOOR_BLOCK			= 193,
	BIRCH_DOOR_BLOCK			= 194,
	JUNGLE_DOOR_BLOCK			= 195,
	ACACIA_DOOR_BLOCK			= 196,
	DARK_OAK_DOOR_BLOCK			= 197,
};


#include "ObjectPool.h"
#include "Block.h"
#include "TextureData.h"
#include "Sector.h"
#include "World.h"
#include "Item.h"
#include "ItemObject.h"
#include "Inventory.h"
#include "Player.h"
#include "WorldGenerator.h"
#include "WorldList.h"
#include "Setting.h"
#include "BlockCollider.h"
#include "ItemManager.h"
#include "Crafting.h"
#include "Monster.h"
#include "Pig.h"
#include "Cow.h"
#include "Chicken.h"
#include "Zombie.h"
#include "Sheep.h"
#include "SkeletonArcher.h"
#include "MonsterManager.h"
#include "ItemDetail.h"
#include "MonsterFactory.h"




#include "LoadingScene.h"
#include "InGameScene.h"
#include "MenuScene.h"


#define WORLD World::GetInstance()
#define WORLD_GENERATOR WorldGenerator::GetInstance()
#define TEXTURE_DATA TextureData::GetInstance()
#define SETTING Setting::GetInstance()
#define ITEM_MANAGER ItemManager::GetInstance()
#define CRAFTING Crafting::GetInstance()
#define INVENTORY Inventory::GetInstance()
#define ITEM_DETAIL ItemDetail::GetInstance()
#define MONSTER_MANAGER MonsterManager::GetInstance()
#define MONSTER_FACTORY MonsterFactory::GetInstance()
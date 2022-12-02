#include "stdafx.h"

TextureData::TextureData()
{
	blockUV[BlockType::GRASS_DIRT][BLOCK_FACE_UP]		= { 8.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS_DIRT][BLOCK_FACE_DOWN]		= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS_DIRT][BLOCK_FACE_RIGHT]	= { 3.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS_DIRT][BLOCK_FACE_LEFT]		= { 3.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS_DIRT][BLOCK_FACE_FORWARD]	= { 3.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS_DIRT][BLOCK_FACE_BEHIND]	= { 3.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::DIRT][BLOCK_FACE_UP]				= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_DOWN]			= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_RIGHT]			= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_LEFT]			= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_FORWARD]		= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_BEHIND]			= { 2.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::STILL_WATER][BLOCK_FACE_UP]		= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STILL_WATER][BLOCK_FACE_DOWN]	= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STILL_WATER][BLOCK_FACE_RIGHT]	= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STILL_WATER][BLOCK_FACE_LEFT]	= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STILL_WATER][BLOCK_FACE_FORWARD]	= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STILL_WATER][BLOCK_FACE_BEHIND]	= { 14.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::OAK_WOOD][BLOCK_FACE_UP]			= { 5.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::OAK_WOOD][BLOCK_FACE_DOWN]		= { 5.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::OAK_WOOD][BLOCK_FACE_RIGHT]		= { 4.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::OAK_WOOD][BLOCK_FACE_LEFT]		= { 4.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::OAK_WOOD][BLOCK_FACE_FORWARD]	= { 4.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::OAK_WOOD][BLOCK_FACE_BEHIND]		= { 4.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::LEAVE][BLOCK_FACE_UP]			= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAVE][BLOCK_FACE_DOWN]			= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAVE][BLOCK_FACE_RIGHT]			= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAVE][BLOCK_FACE_LEFT]			= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAVE][BLOCK_FACE_FORWARD]		= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAVE][BLOCK_FACE_BEHIND]		= { 4.f / 16.f, 3.f / 16.f };


	blockUV[BlockType::STONE][BLOCK_FACE_UP]			= { 1.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STONE][BLOCK_FACE_DOWN]			= { 1.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STONE][BLOCK_FACE_RIGHT]			= { 1.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STONE][BLOCK_FACE_LEFT]			= { 1.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STONE][BLOCK_FACE_FORWARD]		= { 1.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::STONE][BLOCK_FACE_BEHIND]		= { 1.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::OAK_WOOD_PLANK][BLOCK_FACE_UP]		= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::OAK_WOOD_PLANK][BLOCK_FACE_DOWN]		= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::OAK_WOOD_PLANK][BLOCK_FACE_RIGHT]	= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::OAK_WOOD_PLANK][BLOCK_FACE_LEFT]		= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::OAK_WOOD_PLANK][BLOCK_FACE_FORWARD]	= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::OAK_WOOD_PLANK][BLOCK_FACE_BEHIND]	= { 4.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::BRICKS][BLOCK_FACE_UP]		= { 7.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BRICKS][BLOCK_FACE_DOWN]		= { 7.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BRICKS][BLOCK_FACE_RIGHT]	= { 7.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BRICKS][BLOCK_FACE_LEFT]		= { 7.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BRICKS][BLOCK_FACE_FORWARD]	= { 7.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BRICKS][BLOCK_FACE_BEHIND]	= { 7.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::TNT][BLOCK_FACE_UP]			= { 9.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::TNT][BLOCK_FACE_DOWN]		= { 10.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::TNT][BLOCK_FACE_RIGHT]		= { 8.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::TNT][BLOCK_FACE_LEFT]		= { 8.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::TNT][BLOCK_FACE_FORWARD]		= { 8.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::TNT][BLOCK_FACE_BEHIND]		= { 8.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::COBBLESTONE][BLOCK_FACE_UP]			= { 0.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::COBBLESTONE][BLOCK_FACE_DOWN]		= { 0.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::COBBLESTONE][BLOCK_FACE_RIGHT]		= { 0.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::COBBLESTONE][BLOCK_FACE_LEFT]		= { 0.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::COBBLESTONE][BLOCK_FACE_FORWARD]		= { 0.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::COBBLESTONE][BLOCK_FACE_BEHIND]		= { 0.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::BEDROCK][BLOCK_FACE_UP]				= { 1.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::BEDROCK][BLOCK_FACE_DOWN]			= { 1.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::BEDROCK][BLOCK_FACE_RIGHT]			= { 1.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::BEDROCK][BLOCK_FACE_LEFT]			= { 1.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::BEDROCK][BLOCK_FACE_FORWARD]			= { 1.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::BEDROCK][BLOCK_FACE_BEHIND]			= { 1.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::SAND][BLOCK_FACE_UP]					= { 2.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::SAND][BLOCK_FACE_DOWN]				= { 2.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::SAND][BLOCK_FACE_RIGHT]				= { 2.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::SAND][BLOCK_FACE_LEFT]				= { 2.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::SAND][BLOCK_FACE_FORWARD]			= { 2.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::SAND][BLOCK_FACE_BEHIND]				= { 2.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::GRAVEL][BLOCK_FACE_UP]				= { 3.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GRAVEL][BLOCK_FACE_DOWN]				= { 3.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GRAVEL][BLOCK_FACE_RIGHT]			= { 3.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GRAVEL][BLOCK_FACE_LEFT]				= { 3.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GRAVEL][BLOCK_FACE_FORWARD]			= { 3.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GRAVEL][BLOCK_FACE_BEHIND]			= { 3.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::IRON_BLOCK][BLOCK_FACE_UP]			= { 6.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::IRON_BLOCK][BLOCK_FACE_DOWN]			= { 6.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::IRON_BLOCK][BLOCK_FACE_RIGHT]		= { 6.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::IRON_BLOCK][BLOCK_FACE_LEFT]			= { 6.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::IRON_BLOCK][BLOCK_FACE_FORWARD]		= { 6.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::IRON_BLOCK][BLOCK_FACE_BEHIND]		= { 6.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::GOLD_BLOCK][BLOCK_FACE_UP]			= { 7.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GOLD_BLOCK][BLOCK_FACE_DOWN]			= { 7.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GOLD_BLOCK][BLOCK_FACE_RIGHT]		= { 7.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GOLD_BLOCK][BLOCK_FACE_LEFT]			= { 7.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GOLD_BLOCK][BLOCK_FACE_FORWARD]		= { 7.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::GOLD_BLOCK][BLOCK_FACE_BEHIND]		= { 7.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::DIAMOND_BLOCK][BLOCK_FACE_UP]			= { 8.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::DIAMOND_BLOCK][BLOCK_FACE_DOWN]			= { 8.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::DIAMOND_BLOCK][BLOCK_FACE_RIGHT]			= { 8.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::DIAMOND_BLOCK][BLOCK_FACE_LEFT]			= { 8.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::DIAMOND_BLOCK][BLOCK_FACE_FORWARD]		= { 8.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::DIAMOND_BLOCK][BLOCK_FACE_BEHIND]		= { 8.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::GOLD_ORE][BLOCK_FACE_UP]				= { 0.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GOLD_ORE][BLOCK_FACE_DOWN]			= { 0.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GOLD_ORE][BLOCK_FACE_RIGHT]			= { 0.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GOLD_ORE][BLOCK_FACE_LEFT]			= { 0.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GOLD_ORE][BLOCK_FACE_FORWARD]		= { 0.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GOLD_ORE][BLOCK_FACE_BEHIND]			= { 0.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::IRON_ORE][BLOCK_FACE_UP]				= { 1.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::IRON_ORE][BLOCK_FACE_DOWN]			= { 1.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::IRON_ORE][BLOCK_FACE_RIGHT]			= { 1.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::IRON_ORE][BLOCK_FACE_LEFT]			= { 1.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::IRON_ORE][BLOCK_FACE_FORWARD]		= { 1.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::IRON_ORE][BLOCK_FACE_BEHIND]			= { 1.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::COAL_ORE][BLOCK_FACE_UP]				= { 2.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::COAL_ORE][BLOCK_FACE_DOWN]			= { 2.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::COAL_ORE][BLOCK_FACE_RIGHT]			= { 2.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::COAL_ORE][BLOCK_FACE_LEFT]			= { 2.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::COAL_ORE][BLOCK_FACE_FORWARD]		= { 2.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::COAL_ORE][BLOCK_FACE_BEHIND]			= { 2.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::BOOKSHELF][BLOCK_FACE_UP]			= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BOOKSHELF][BLOCK_FACE_DOWN]			= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BOOKSHELF][BLOCK_FACE_RIGHT]			= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BOOKSHELF][BLOCK_FACE_LEFT]			= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::BOOKSHELF][BLOCK_FACE_FORWARD]		= { 3.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::BOOKSHELF][BLOCK_FACE_BEHIND]		= { 4.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::OBSIDIAN][BLOCK_FACE_UP]				= { 5.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::OBSIDIAN][BLOCK_FACE_DOWN]			= { 5.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::OBSIDIAN][BLOCK_FACE_RIGHT]			= { 5.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::OBSIDIAN][BLOCK_FACE_LEFT]			= { 5.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::OBSIDIAN][BLOCK_FACE_FORWARD]		= { 5.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::OBSIDIAN][BLOCK_FACE_BEHIND]			= { 5.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::CRAFTING_TABLE][BLOCK_FACE_UP]				= { 11.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::CRAFTING_TABLE][BLOCK_FACE_DOWN]				= { 11.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::CRAFTING_TABLE][BLOCK_FACE_RIGHT]			= { 11.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::CRAFTING_TABLE][BLOCK_FACE_LEFT]				= { 11.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::CRAFTING_TABLE][BLOCK_FACE_FORWARD]			= { 12.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::CRAFTING_TABLE][BLOCK_FACE_BEHIND]			= { 11.f / 16.f, 3.f / 16.f };


	blockUV[BlockType::FURNACE][BLOCK_FACE_UP]					= { 14.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::FURNACE][BLOCK_FACE_DOWN]				= { 14.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::FURNACE][BLOCK_FACE_RIGHT]				= { 13.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::FURNACE][BLOCK_FACE_LEFT]				= { 13.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::FURNACE][BLOCK_FACE_FORWARD]				= { 12.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::FURNACE][BLOCK_FACE_BEHIND]				= { 13.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::BURNING_FURNACE][BLOCK_FACE_UP]					= { 14.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::BURNING_FURNACE][BLOCK_FACE_DOWN]				= { 14.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::BURNING_FURNACE][BLOCK_FACE_RIGHT]				= { 13.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::BURNING_FURNACE][BLOCK_FACE_LEFT]				= { 13.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::BURNING_FURNACE][BLOCK_FACE_FORWARD]				= { 13.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::BURNING_FURNACE][BLOCK_FACE_BEHIND]				= { 13.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::WHITE_WOOL][BLOCK_FACE_UP]					= { 0.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::WHITE_WOOL][BLOCK_FACE_DOWN]					= { 0.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::WHITE_WOOL][BLOCK_FACE_RIGHT]				= { 0.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::WHITE_WOOL][BLOCK_FACE_LEFT]					= { 0.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::WHITE_WOOL][BLOCK_FACE_FORWARD]				= { 0.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::WHITE_WOOL][BLOCK_FACE_BEHIND]				= { 0.f / 16.f, 4.f / 16.f };


	blockUV[BlockType::SNOW_BLOCK][BLOCK_FACE_UP]					= { 2.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_BLOCK][BLOCK_FACE_DOWN]					= { 2.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_BLOCK][BLOCK_FACE_RIGHT]				= { 2.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_BLOCK][BLOCK_FACE_LEFT]					= { 2.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_BLOCK][BLOCK_FACE_FORWARD]				= { 2.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_BLOCK][BLOCK_FACE_BEHIND]				= { 2.f / 16.f, 4.f / 16.f };


	blockUV[BlockType::ICE][BLOCK_FACE_UP]						= { 3.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::ICE][BLOCK_FACE_DOWN]					= { 3.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::ICE][BLOCK_FACE_RIGHT]					= { 3.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::ICE][BLOCK_FACE_LEFT]					= { 3.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::ICE][BLOCK_FACE_FORWARD]					= { 3.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::ICE][BLOCK_FACE_BEHIND]					= { 3.f / 16.f, 4.f / 16.f };


	blockUV[BlockType::FARMLAND][BLOCK_FACE_UP]						= { 7.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND][BLOCK_FACE_DOWN]					= { 7.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND][BLOCK_FACE_RIGHT]					= { 7.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND][BLOCK_FACE_LEFT]					= { 7.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND][BLOCK_FACE_FORWARD]				= { 7.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND][BLOCK_FACE_BEHIND]					= { 7.f / 16.f, 5.f / 16.f };


	blockUV[BlockType::FARMLAND_WET][BLOCK_FACE_UP]						= { 6.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND_WET][BLOCK_FACE_DOWN]					= { 6.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND_WET][BLOCK_FACE_RIGHT]					= { 6.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND_WET][BLOCK_FACE_LEFT]					= { 6.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND_WET][BLOCK_FACE_FORWARD]				= { 6.f / 16.f, 5.f / 16.f };
	blockUV[BlockType::FARMLAND_WET][BLOCK_FACE_BEHIND]					= { 6.f / 16.f, 5.f / 16.f };


	blockUV[BlockType::PUMPKIN][BLOCK_FACE_UP]						= { 6.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::PUMPKIN][BLOCK_FACE_DOWN]					= { 6.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::PUMPKIN][BLOCK_FACE_RIGHT]					= { 6.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::PUMPKIN][BLOCK_FACE_LEFT]					= { 6.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::PUMPKIN][BLOCK_FACE_FORWARD]					= { 6.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::PUMPKIN][BLOCK_FACE_BEHIND]					= { 6.f / 16.f, 7.f / 16.f };


	blockUV[BlockType::PUMPKIN_CARVED][BLOCK_FACE_UP]					= { 6.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::PUMPKIN_CARVED][BLOCK_FACE_DOWN]					= { 6.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::PUMPKIN_CARVED][BLOCK_FACE_RIGHT]				= { 6.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::PUMPKIN_CARVED][BLOCK_FACE_LEFT]					= { 6.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::PUMPKIN_CARVED][BLOCK_FACE_FORWARD]				= { 7.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::PUMPKIN_CARVED][BLOCK_FACE_BEHIND]				= { 6.f / 16.f, 7.f / 16.f };


	blockUV[BlockType::JUNGLE_WOOD][BLOCK_FACE_UP]					= { 10.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD][BLOCK_FACE_DOWN]				= { 10.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD][BLOCK_FACE_RIGHT]				= { 5.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD][BLOCK_FACE_LEFT]				= { 5.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD][BLOCK_FACE_FORWARD]				= { 5.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD][BLOCK_FACE_BEHIND]				= { 5.f / 16.f, 6.f / 16.f };


	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_UP]					= { 9.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_DOWN]				= { 9.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_RIGHT]				= { 4.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_LEFT]				= { 4.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_FORWARD]				= { 4.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_BEHIND]				= { 4.f / 16.f, 6.f / 16.f };


	blockUV[BlockType::BIRCH_WOOD][BLOCK_FACE_UP]					= { 9.f / 16.f, 14.f / 16.f };
	blockUV[BlockType::BIRCH_WOOD][BLOCK_FACE_DOWN]					= { 9.f / 16.f, 14.f / 16.f };
	blockUV[BlockType::BIRCH_WOOD][BLOCK_FACE_RIGHT]				= { 5.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::BIRCH_WOOD][BLOCK_FACE_LEFT]					= { 5.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::BIRCH_WOOD][BLOCK_FACE_FORWARD]				= { 5.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::BIRCH_WOOD][BLOCK_FACE_BEHIND]				= { 5.f / 16.f, 7.f / 16.f };


	blockUV[BlockType::LAPIS_LAZULI_ORE][BLOCK_FACE_UP]					= { 0.f / 16.f, 10.f / 16.f };
	blockUV[BlockType::LAPIS_LAZULI_ORE][BLOCK_FACE_DOWN]				= { 0.f / 16.f, 10.f / 16.f };
	blockUV[BlockType::LAPIS_LAZULI_ORE][BLOCK_FACE_RIGHT]				= { 0.f / 16.f, 10.f / 16.f };
	blockUV[BlockType::LAPIS_LAZULI_ORE][BLOCK_FACE_LEFT]				= { 0.f / 16.f, 10.f / 16.f };
	blockUV[BlockType::LAPIS_LAZULI_ORE][BLOCK_FACE_FORWARD]			= { 0.f / 16.f, 10.f / 16.f };
	blockUV[BlockType::LAPIS_LAZULI_ORE][BLOCK_FACE_BEHIND]				= { 0.f / 16.f, 10.f / 16.f };


	blockUV[BlockType::SANDSTONE][BLOCK_FACE_UP]					= { 0.f / 16.f, 11.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_DOWN]					= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_RIGHT]					= { 0.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_LEFT]					= { 0.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_FORWARD]				= { 0.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_BEHIND]				= { 0.f / 16.f, 12.f / 16.f };


	blockUV[BlockType::GLOWSTONE][BLOCK_FACE_UP]					= { 9.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::GLOWSTONE][BLOCK_FACE_DOWN]					= { 9.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::GLOWSTONE][BLOCK_FACE_RIGHT]					= { 9.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::GLOWSTONE][BLOCK_FACE_LEFT]					= { 9.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::GLOWSTONE][BLOCK_FACE_FORWARD]				= { 9.f / 16.f, 6.f / 16.f };
	blockUV[BlockType::GLOWSTONE][BLOCK_FACE_BEHIND]				= { 9.f / 16.f, 6.f / 16.f };


	blockUV[BlockType::JUNGLE_LEAVES][BLOCK_FACE_UP]					= { 5.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::JUNGLE_LEAVES][BLOCK_FACE_DOWN]					= { 5.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::JUNGLE_LEAVES][BLOCK_FACE_RIGHT]					= { 5.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::JUNGLE_LEAVES][BLOCK_FACE_LEFT]					= { 5.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::JUNGLE_LEAVES][BLOCK_FACE_FORWARD]				= { 5.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::JUNGLE_LEAVES][BLOCK_FACE_BEHIND]				= { 5.f / 16.f, 3.f / 16.f };


	blockUV[BlockType::SPRUCE_LEAVES][BLOCK_FACE_UP]					= { 4.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::SPRUCE_LEAVES][BLOCK_FACE_DOWN]					= { 4.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::SPRUCE_LEAVES][BLOCK_FACE_RIGHT]					= { 4.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::SPRUCE_LEAVES][BLOCK_FACE_LEFT]					= { 4.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::SPRUCE_LEAVES][BLOCK_FACE_FORWARD]				= { 4.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::SPRUCE_LEAVES][BLOCK_FACE_BEHIND]				= { 4.f / 16.f, 8.f / 16.f };


	blockUV[BlockType::BIRCH_LEAVES][BLOCK_FACE_UP]						= { 5.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::BIRCH_LEAVES][BLOCK_FACE_DOWN]					= { 5.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::BIRCH_LEAVES][BLOCK_FACE_RIGHT]					= { 5.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::BIRCH_LEAVES][BLOCK_FACE_LEFT]					= { 5.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::BIRCH_LEAVES][BLOCK_FACE_FORWARD]				= { 5.f / 16.f, 8.f / 16.f };
	blockUV[BlockType::BIRCH_LEAVES][BLOCK_FACE_BEHIND]					= { 5.f / 16.f, 8.f / 16.f };


	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_UP]						= { 9.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_DOWN]					= { 9.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_RIGHT]					= { 4.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_LEFT]					= { 4.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_FORWARD]					= { 4.f / 16.f, 7.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD][BLOCK_FACE_BEHIND]					= { 4.f / 16.f, 7.f / 16.f };


	blockUV[BlockType::SPRUCE_WOOD_PLANK][BLOCK_FACE_UP]					= { 6.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD_PLANK][BLOCK_FACE_DOWN]					= { 6.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD_PLANK][BLOCK_FACE_RIGHT]					= { 6.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD_PLANK][BLOCK_FACE_LEFT]					= { 6.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD_PLANK][BLOCK_FACE_FORWARD]				= { 6.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SPRUCE_WOOD_PLANK][BLOCK_FACE_BEHIND]				= { 6.f / 16.f, 12.f / 16.f };


	blockUV[BlockType::JUNGLE_WOOD_PLANK][BLOCK_FACE_UP]					= { 7.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD_PLANK][BLOCK_FACE_DOWN]					= { 7.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD_PLANK][BLOCK_FACE_RIGHT]					= { 7.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD_PLANK][BLOCK_FACE_LEFT]					= { 7.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD_PLANK][BLOCK_FACE_FORWARD]				= { 7.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::JUNGLE_WOOD_PLANK][BLOCK_FACE_BEHIND]				= { 7.f / 16.f, 12.f / 16.f };


	blockUV[BlockType::GLASS][BLOCK_FACE_UP]						= { 1.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::GLASS][BLOCK_FACE_DOWN]						= { 1.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::GLASS][BLOCK_FACE_RIGHT]						= { 1.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::GLASS][BLOCK_FACE_LEFT]						= { 1.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::GLASS][BLOCK_FACE_FORWARD]					= { 1.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::GLASS][BLOCK_FACE_BEHIND]					= { 1.f / 16.f, 3.f / 16.f };


	blockUV[BlockType::SNOW_DIRT][BLOCK_FACE_UP]						= { 2.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_DIRT][BLOCK_FACE_DOWN]						= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::SNOW_DIRT][BLOCK_FACE_RIGHT]						= { 4.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_DIRT][BLOCK_FACE_LEFT]						= { 4.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_DIRT][BLOCK_FACE_FORWARD]					= { 4.f / 16.f, 4.f / 16.f };
	blockUV[BlockType::SNOW_DIRT][BLOCK_FACE_BEHIND]					= { 4.f / 16.f, 4.f / 16.f };


	blockUV[BlockType::GRASS][BLOCK_FACE_UP]						= { 7.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_DOWN]						= { 7.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_RIGHT]						= { 7.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_LEFT]						= { 7.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_FORWARD]					= { 7.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_BEHIND]					= { 7.f / 16.f, 2.f / 16.f };


	blockUV[BlockType::DANDELION][BLOCK_FACE_UP]						= { 12.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DANDELION][BLOCK_FACE_DOWN]						= { 12.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DANDELION][BLOCK_FACE_RIGHT]						= { 12.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DANDELION][BLOCK_FACE_LEFT]						= { 12.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DANDELION][BLOCK_FACE_FORWARD]					= { 12.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DANDELION][BLOCK_FACE_BEHIND]					= { 12.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::ROSE][BLOCK_FACE_UP]							= { 13.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::ROSE][BLOCK_FACE_DOWN]						= { 13.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::ROSE][BLOCK_FACE_RIGHT]						= { 13.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::ROSE][BLOCK_FACE_LEFT]						= { 13.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::ROSE][BLOCK_FACE_FORWARD]					= { 13.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::ROSE][BLOCK_FACE_BEHIND]						= { 13.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::TULIP][BLOCK_FACE_UP]							= { 12.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::TULIP][BLOCK_FACE_DOWN]						= { 12.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::TULIP][BLOCK_FACE_RIGHT]						= { 12.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::TULIP][BLOCK_FACE_LEFT]						= { 12.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::TULIP][BLOCK_FACE_FORWARD]					= { 12.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::TULIP][BLOCK_FACE_BEHIND]						= { 12.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::ORCHID][BLOCK_FACE_UP]						= { 13.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::ORCHID][BLOCK_FACE_DOWN]						= { 13.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::ORCHID][BLOCK_FACE_RIGHT]					= { 13.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::ORCHID][BLOCK_FACE_LEFT]						= { 13.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::ORCHID][BLOCK_FACE_FORWARD]					= { 13.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::ORCHID][BLOCK_FACE_BEHIND]					= { 13.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::SANDSTONE][BLOCK_FACE_UP]						= { 0.f / 16.f, 11.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_DOWN]						= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_RIGHT]						= { 0.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_LEFT]						= { 0.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_FORWARD]					= { 0.f / 16.f, 12.f / 16.f };
	blockUV[BlockType::SANDSTONE][BLOCK_FACE_BEHIND]					= { 0.f / 16.f, 12.f / 16.f };


	blockUV[BlockType::SANDSTONE_SHAVED][BLOCK_FACE_UP]						= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE_SHAVED][BLOCK_FACE_DOWN]					= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE_SHAVED][BLOCK_FACE_RIGHT]					= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE_SHAVED][BLOCK_FACE_LEFT]					= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE_SHAVED][BLOCK_FACE_FORWARD]				= { 0.f / 16.f, 13.f / 16.f };
	blockUV[BlockType::SANDSTONE_SHAVED][BLOCK_FACE_BEHIND]					= { 0.f / 16.f, 13.f / 16.f };

}

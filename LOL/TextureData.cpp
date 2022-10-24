#include "stdafx.h"

TextureData::TextureData()
{
	blockUV[BlockType::GRASS][BLOCK_FACE_UP]		= { 8.f / 16.f, 2.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_DOWN]		= { 2.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_RIGHT]		= { 3.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_LEFT]		= { 3.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_FORWARD]	= { 3.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::GRASS][BLOCK_FACE_BEHIND]	= { 3.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::DIRT][BLOCK_FACE_UP]			= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_DOWN]		= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_RIGHT]		= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_LEFT]		= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_FORWARD]	= { 4.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::DIRT][BLOCK_FACE_BEHIND]		= { 4.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::WATER][BLOCK_FACE_UP]		= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::WATER][BLOCK_FACE_DOWN]		= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::WATER][BLOCK_FACE_RIGHT]		= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::WATER][BLOCK_FACE_LEFT]		= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::WATER][BLOCK_FACE_FORWARD]	= { 14.f / 16.f, 0.f / 16.f };
	blockUV[BlockType::WATER][BLOCK_FACE_BEHIND]	= { 14.f / 16.f, 0.f / 16.f };


	blockUV[BlockType::WOOD_OAK][BLOCK_FACE_UP]			= { 5.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::WOOD_OAK][BLOCK_FACE_DOWN]		= { 5.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::WOOD_OAK][BLOCK_FACE_RIGHT]		= { 4.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::WOOD_OAK][BLOCK_FACE_LEFT]		= { 4.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::WOOD_OAK][BLOCK_FACE_FORWARD]	= { 4.f / 16.f, 1.f / 16.f };
	blockUV[BlockType::WOOD_OAK][BLOCK_FACE_BEHIND]		= { 4.f / 16.f, 1.f / 16.f };


	blockUV[BlockType::LEAF][BLOCK_FACE_UP]			= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAF][BLOCK_FACE_DOWN]		= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAF][BLOCK_FACE_RIGHT]		= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAF][BLOCK_FACE_LEFT]		= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAF][BLOCK_FACE_FORWARD]	= { 4.f / 16.f, 3.f / 16.f };
	blockUV[BlockType::LEAF][BLOCK_FACE_BEHIND]		= { 4.f / 16.f, 3.f / 16.f };

}

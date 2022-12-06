#include "stdafx.h"

Sector::Sector()
{
	shader		= RESOURCE->shaders.Load("block.hlsl");
	waterShader = RESOURCE->shaders.Load("Water.hlsl");
	material	= RESOURCE->materials.Load("BaseBlock.mtl");
	for (int x = 0; x < SECTOR_SIZE; x++)
	{
		for (int z = 0; z < SECTOR_SIZE; z++)
		{
			for (int y = 0; y < WORLD_HEIGHT; y++)
				blocks[x][y][z].blockType = BlockType::AIR;
			for (int y = 1; y < 19; y++)
				blocks[x][y][z].blockType = BlockType::DIRT;
			for (int y = 19; y < 20; y++)
				blocks[x][y][z].blockType = BlockType::GRASS_DIRT;
		}
	}
}

bool Sector::RenderHierarchy()
{
	GameObject::RenderHierarchy();
	return false;
}

void Sector::PreRender()
{
	if (visible)
	{
		if (blockMesh and shader and material)
		{
			Transform::Set();
			shader->Set();
			blockMesh->Set();
			material->Set();

			D3D->GetDC()->DrawIndexed(blockMesh->indexCount, 0, 0);
		}
	}
}

void Sector::Render()
{
	if (visible)
	{
		if (waterMesh and waterShader and material)
		{
			Transform::Set();
			waterShader->Set();
			waterMesh->Set();
			material->Set();

			D3D->GetDC()->DrawIndexed(waterMesh->indexCount, 0, 0);
		}
	}
}

void Sector::Update()
{
	GameObject::Update();
}

void Sector::UpdateBlockMesh()
{
	if (blockMesh)
		blockMesh->~Mesh();

	vector<VertexPTN>	vertexBuffer;
	vector<UINT>		indexBuffer;

	Int3 from;
	for (from.x = 0; from.x < SECTOR_SIZE; from.x++)
	{
		for (from.y = 0; from.y < WORLD_HEIGHT; from.y++)
		{
			for (from.z = 0; from.z < SECTOR_SIZE; from.z++)
			{
				if (blocks[from.x][from.y][from.z].renderFace == 0)
					continue;
				if (blocks[from.x][from.y][from.z].blockType < BlockType::STILL_WATER)
					continue;

				switch(blocks[from.x][from.y][from.z].blockType) {
					case BlockType::LEAVE:
					case BlockType::BIRCH_LEAVES:
					case BlockType::JUNGLE_LEAVES:
					case BlockType::SPRUCE_LEAVES:
					case BlockType::GLASS:
						for (int i = 0; i < 6; i++) {
							if ((blocks[from.x][from.y][from.z].renderFace & sixFaces[i]) != 0)
								AddDoubleFace(vertexBuffer, indexBuffer, from, sixFaces[i], blocks[from.x][from.y][from.z].blockType);
						}
					break;
					case BlockType::GRASS:
					case BlockType::DANDELION:
					case BlockType::ROSE:
					case BlockType::TULIP:
					case BlockType::ORCHID:
						for (int i = 0; i < 6; i++) {
							if ((blocks[from.x][from.y][from.z].renderFace & sixFaces[i]) != 0)
								AddCrossFace(vertexBuffer, indexBuffer, from, sixFaces[i], blocks[from.x][from.y][from.z].blockType);
						}
						break;
					default:
						for (int i = 0; i < 6; i++) {
							if ((blocks[from.x][from.y][from.z].renderFace & sixFaces[i]) != 0)
								AddMeshFace(vertexBuffer, indexBuffer, from, sixFaces[i], blocks[from.x][from.y][from.z].blockType);
						}
				}
			}
		}
	}

	if (vertexBuffer.size() == 0)
		return;

	//int arr[6] = { 0, 1, 2, 0, 2, 3 };
	//for (int i = 0; i < vertexBuffer.size() * 3 / 2; i++)
	//{
	//	for (int j = 0; j < 6; j++)
	//		indexBuffer.push_back(arr[j] + (i * 4));
	//}


	VertexPTN* vertices;
	UINT vertexCount = vertexBuffer.size();
	UINT* indices;
	UINT indexCount = indexBuffer.size();
	VertexType type = VertexType::PTN;

	vertices = new VertexPTN[vertexCount];
	indices = new UINT[indexCount];

	for (int i = 0; i < vertexCount; i++)
		vertices[i] = vertexBuffer[i];
	for (int i = 0; i < indexCount; i++)
		indices[i] = indexBuffer[i];
	
	blockMesh = new Mesh(vertices, vertexCount, indices, indexCount, VertexType::PTN);
}

void Sector::UpdateWaterMesh()
{
	if (waterMesh)
		waterMesh->~Mesh();

	vector<VertexPTN>	vertexBuffer;
	vector<UINT>		indexBuffer;

	Int3 from;
	for (from.x = 0; from.x < SECTOR_SIZE; from.x++)
	{
		for (from.y = 0; from.y < WORLD_HEIGHT; from.y++)
		{
			for (from.z = 0; from.z < SECTOR_SIZE; from.z++)
			{
				if (blocks[from.x][from.y][from.z].renderFace == 0)
					continue;
				if (blocks[from.x][from.y][from.z].blockType != BlockType::STILL_WATER)
					continue;

				for (int i = 0; i < 6; i++) {
					if ((blocks[from.x][from.y][from.z].renderFace & sixFaces[i]) != 0)
						AddMeshFace(vertexBuffer, indexBuffer, from, sixFaces[i], blocks[from.x][from.y][from.z].blockType);
				}
			}
		}
	}

	if (vertexBuffer.size() == 0)
		return;

	//int arr[6] = { 0, 1, 2, 0, 2, 3 };
	//for (int i = 0; i < vertexBuffer.size() * 3 / 2; i++)
	//{
	//	for (int j = 0; j < 6; j++)
	//		indexBuffer.push_back(arr[j] + (i * 4));
	//}


	VertexPTN* vertices;
	UINT vertexCount = vertexBuffer.size();
	UINT* indices;
	UINT indexCount = indexBuffer.size();
	VertexType type = VertexType::PTN;

	vertices = new VertexPTN[vertexCount];
	indices = new UINT[indexCount];

	for (int i = 0; i < vertexCount; i++)
		vertices[i] = vertexBuffer[i];
	for (int i = 0; i < indexCount; i++)
		indices[i] = indexBuffer[i];

	waterMesh = new Mesh(vertices, vertexCount, indices, indexCount, VertexType::PTN);
}



void Sector::AddMeshFace(vector<VertexPTN>& vertices, vector<UINT>& indexBuffer, Int3& pos, const int& renderFace, BlockType& blockType)
{
	const Vector2 uvCube[4] = { { 0.f, 1.f / 16.f }, { 0.f, 0.f }, { 1.f / 16.f, 0.f }, { 1.f / 16.f, 1.f / 16.f } };
	const int arr[6] = { 0, 1, 2, 0, 2, 3 };
	UINT vIndex = vertices.size();

	for (int i = 0;i < 4;i++)
		vertices.push_back({ { float(pos.x), float(pos.y),  float(pos.z) }, uvCube[i], { 0.f, 0.f, 0.f } });


	switch (renderFace) {
	case BLOCK_FACE_UP:
		{
			vertices[vIndex + 0].position += { -0.5f, 0.5f, -0.5f };
			vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
			vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
			vertices[vIndex + 3].position += { 0.5f, 0.5f, -0.5f };
			break;
		}
		case BLOCK_FACE_DOWN:
		{
			vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
			vertices[vIndex + 1].position += { 0.5f, -0.5f, 0.5f };
			vertices[vIndex + 2].position += { -0.5f, -0.5f, 0.5f };
			vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
			break;
		}
		case BLOCK_FACE_RIGHT:
		{
			vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
			vertices[vIndex + 1].position += { 0.5f, 0.5f, -0.5f };
			vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
			vertices[vIndex + 3].position += { 0.5f, -0.5f, 0.5f };
			break;
		}
		case BLOCK_FACE_LEFT:
		{
			vertices[vIndex + 0].position += { -0.5f, -0.5f, 0.5f };
			vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
			vertices[vIndex + 2].position += { -0.5f, 0.5f, -0.5f };
			vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
			break;
		}
		case BLOCK_FACE_FORWARD:
		{
			vertices[vIndex + 0].position += { -0.5f, -0.5f, -0.5f };
			vertices[vIndex + 1].position += { -0.5f, 0.5f, -0.5f };
			vertices[vIndex + 2].position += { 0.5f, 0.5f, -0.5f };
			vertices[vIndex + 3].position += { 0.5f, -0.5f, -0.5f };
			break;
		}
		case BLOCK_FACE_BEHIND:
		{
			vertices[vIndex + 0].position += { 0.5f, -0.5f, 0.5f };
			vertices[vIndex + 1].position += { 0.5f, 0.5f, 0.5f };
			vertices[vIndex + 2].position += { -0.5f, 0.5f, 0.5f };
			vertices[vIndex + 3].position += { -0.5f, -0.5f, 0.5f };
			break;
		}
	}

	vertices[vIndex + 0].position *= BLOCK_LENGTH;
	vertices[vIndex + 1].position *= BLOCK_LENGTH;
	vertices[vIndex + 2].position *= BLOCK_LENGTH;
	vertices[vIndex + 3].position *= BLOCK_LENGTH;

	vertices[vIndex + 0].uv = { 0.f, 1.f / 16.f };
	vertices[vIndex + 1].uv = { 0.f, 0.f };
	vertices[vIndex + 2].uv = { 1.f / 16.f, 0.f };
	vertices[vIndex + 3].uv = { 1.f / 16.f, 1.f / 16.f };

	for (int i = 0; i < 4; i++)
		vertices[vIndex + i].uv += TEXTURE_DATA->blockUV[blockType][renderFace];

	for (int j = 0; j < 6; j++)
		indexBuffer.push_back(arr[j] + vertices.size() - 4);
}
void Sector::AddDoubleFace(vector<VertexPTN>& vertices, vector<UINT>& indexBuffer, Int3& pos, const int& renderFace, BlockType& blockType)
{
	const Vector2 uvCube[4] = { { 0.f, 1.f / 16.f }, { 0.f, 0.f }, { 1.f / 16.f, 0.f }, { 1.f / 16.f, 1.f / 16.f } };
	const int arr[6] = { 0, 1, 2, 0, 2, 3 };
	UINT vIndex = vertices.size();

	for (int i = 0; i < 4; i++)
		vertices.push_back({ { float(pos.x), float(pos.y),  float(pos.z) }, uvCube[i], { 0.f, 0.f, 0.f } });


	switch (renderFace) {
	case BLOCK_FACE_UP:
	{
		vertices[vIndex + 0].position += { -0.5f, 0.5f, -0.5f };
		vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
		vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
		vertices[vIndex + 3].position += { 0.5f, 0.5f, -0.5f };
		break;
	}
	case BLOCK_FACE_DOWN:
	{
		vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
		vertices[vIndex + 1].position += { 0.5f, -0.5f, 0.5f };
		vertices[vIndex + 2].position += { -0.5f, -0.5f, 0.5f };
		vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
		break;
	}
	case BLOCK_FACE_RIGHT:
	{
		vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
		vertices[vIndex + 1].position += { 0.5f, 0.5f, -0.5f };
		vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
		vertices[vIndex + 3].position += { 0.5f, -0.5f, 0.5f };
		break;
	}
	case BLOCK_FACE_LEFT:
	{
		vertices[vIndex + 0].position += { -0.5f, -0.5f, 0.5f };
		vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
		vertices[vIndex + 2].position += { -0.5f, 0.5f, -0.5f };
		vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
		break;
	}
	case BLOCK_FACE_FORWARD:
	{
		vertices[vIndex + 0].position += { -0.5f, -0.5f, -0.5f };
		vertices[vIndex + 1].position += { -0.5f, 0.5f, -0.5f };
		vertices[vIndex + 2].position += { 0.5f, 0.5f, -0.5f };
		vertices[vIndex + 3].position += { 0.5f, -0.5f, -0.5f };
		break;
	}
	case BLOCK_FACE_BEHIND:
	{
		vertices[vIndex + 0].position += { 0.5f, -0.5f, 0.5f };
		vertices[vIndex + 1].position += { 0.5f, 0.5f, 0.5f };
		vertices[vIndex + 2].position += { -0.5f, 0.5f, 0.5f };
		vertices[vIndex + 3].position += { -0.5f, -0.5f, 0.5f };
		break;
	}
	}

	vertices[vIndex + 0].position *= BLOCK_LENGTH;
	vertices[vIndex + 1].position *= BLOCK_LENGTH;
	vertices[vIndex + 2].position *= BLOCK_LENGTH;
	vertices[vIndex + 3].position *= BLOCK_LENGTH;

	vertices[vIndex + 0].uv = { 0.f, 1.f / 16.f };
	vertices[vIndex + 1].uv = { 0.f, 0.f };
	vertices[vIndex + 2].uv = { 1.f / 16.f, 0.f };
	vertices[vIndex + 3].uv = { 1.f / 16.f, 1.f / 16.f };

	for (int i = 0; i < 4; i++)
		vertices[vIndex + i].uv += TEXTURE_DATA->blockUV[blockType][renderFace];

	for (int j = 0; j < 6; j++)
		indexBuffer.push_back(arr[j] + vertices.size() - 4);
	for (int j = 0; j < 6; j++)
		indexBuffer.push_back(arr[5 - j] + vertices.size() - 4);
}
void Sector::AddCrossFace(vector<VertexPTN>& vertices, vector<UINT>& indexBuffer, Int3& pos, const int& renderFace, BlockType& blockType)
{
	const Vector2 uvCube[4] = { { 0.f, 1.f / 16.f }, { 0.f, 0.f }, { 1.f / 16.f, 0.f }, { 1.f / 16.f, 1.f / 16.f } };
	const int arr[6] = { 0, 1, 2, 0, 2, 3 };
	UINT vIndex = vertices.size();

	if (renderFace == BLOCK_FACE_UP || renderFace == BLOCK_FACE_DOWN)
		return;

	for (int i = 0; i < 4; i++)
		vertices.push_back({ { float(pos.x), float(pos.y),  float(pos.z) }, uvCube[i], { 0.f, 0.f, 0.f } });


	switch (renderFace) {
	case BLOCK_FACE_RIGHT:
	{
		vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
		vertices[vIndex + 1].position += { 0.5f, 0.5f, -0.5f };
		vertices[vIndex + 2].position += { -0.5f, 0.5f, 0.5f };
		vertices[vIndex + 3].position += { -0.5f, -0.5f, 0.5f };
		break;
	}
	case BLOCK_FACE_LEFT:
	{
		vertices[vIndex + 0].position += { -0.5f, -0.5f, 0.5f };
		vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
		vertices[vIndex + 2].position += { 0.5f, 0.5f, -0.5f };
		vertices[vIndex + 3].position += { 0.5f, -0.5f, -0.5f };
		break;
	}
	case BLOCK_FACE_FORWARD:
	{
		vertices[vIndex + 0].position += { -0.5f, -0.5f, -0.5f };
		vertices[vIndex + 1].position += { -0.5f, 0.5f, -0.5f };
		vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
		vertices[vIndex + 3].position += { 0.5f, -0.5f, 0.5f };
		break;
	}
	case BLOCK_FACE_BEHIND:
	{
		vertices[vIndex + 0].position += { 0.5f, -0.5f, 0.5f };
		vertices[vIndex + 1].position += { 0.5f, 0.5f, 0.5f };
		vertices[vIndex + 2].position += { -0.5f, 0.5f, -0.5f };
		vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
		break;
	}
	}

	vertices[vIndex + 0].position *= BLOCK_LENGTH;
	vertices[vIndex + 1].position *= BLOCK_LENGTH;
	vertices[vIndex + 2].position *= BLOCK_LENGTH;
	vertices[vIndex + 3].position *= BLOCK_LENGTH;

	vertices[vIndex + 0].uv = { 0.f, 1.f / 16.f };
	vertices[vIndex + 1].uv = { 0.f, 0.f };
	vertices[vIndex + 2].uv = { 1.f / 16.f, 0.f };
	vertices[vIndex + 3].uv = { 1.f / 16.f, 1.f / 16.f };

	for (int i = 0; i < 4; i++)
		vertices[vIndex + i].uv += TEXTURE_DATA->blockUV[blockType][renderFace];

	for (int j = 0; j < 6; j++)
		indexBuffer.push_back(arr[j] + vertices.size() - 4);
	for (int j = 0; j < 6; j++)
		indexBuffer.push_back(arr[5 - j] + vertices.size() - 4);
}
//
//void Sector::AddMeshFace(vector<VertexPTN>& vertices, Int3& pos, const int& renderFace, BlockType& blockType)
//{
//	for (int i = 0; i < 4; i++)
//		vertices[vIndex + i].position = { float(pos.x), float(pos.y),  float(pos.z) };
//
//	switch (renderFace) {
//	case BLOCK_FACE_UP:
//	{
//		vertices[vIndex + 0].position += { -0.5f, 0.5f, -0.5f };
//		vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
//		vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
//		vertices[vIndex + 3].position += { 0.5f, 0.5f, -0.5f };
//		break;
//	}
//	case BLOCK_FACE_DOWN:
//	{
//		vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
//		vertices[vIndex + 1].position += { 0.5f, -0.5f, 0.5f };
//		vertices[vIndex + 2].position += { -0.5f, -0.5f, 0.5f };
//		vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
//		break;
//	}
//	case BLOCK_FACE_RIGHT:
//	{
//		vertices[vIndex + 0].position += { 0.5f, -0.5f, -0.5f };
//		vertices[vIndex + 1].position += { 0.5f, 0.5f, -0.5f };
//		vertices[vIndex + 2].position += { 0.5f, 0.5f, 0.5f };
//		vertices[vIndex + 3].position += { 0.5f, -0.5f, 0.5f };
//		break;
//	}
//	case BLOCK_FACE_LEFT:
//	{
//		vertices[vIndex + 0].position += { -0.5f, -0.5f, 0.5f };
//		vertices[vIndex + 1].position += { -0.5f, 0.5f, 0.5f };
//		vertices[vIndex + 2].position += { -0.5f, 0.5f, -0.5f };
//		vertices[vIndex + 3].position += { -0.5f, -0.5f, -0.5f };
//		break;
//	}
//	case BLOCK_FACE_FORWARD:
//	{
//		vertices[vIndex + 0].position += { -0.5f, -0.5f, -0.5f };
//		vertices[vIndex + 1].position += { -0.5f, 0.5f, -0.5f };
//		vertices[vIndex + 2].position += { 0.5f, 0.5f, -0.5f };
//		vertices[vIndex + 3].position += { 0.5f, -0.5f, -0.5f };
//		break;
//	}
//	case BLOCK_FACE_BEHIND:
//	{
//		vertices[vIndex + 0].position += { 0.5f, -0.5f, 0.5f };
//		vertices[vIndex + 1].position += { 0.5f, 0.5f, 0.5f };
//		vertices[vIndex + 2].position += { -0.5f, 0.5f, 0.5f };
//		vertices[vIndex + 3].position += { -0.5f, -0.5f, 0.5f };
//		break;
//	}
//	}
//	vIndex += 4;
//	vertices[vIndex - 4].position *= BLOCK_LENGTH;
//	vertices[vIndex - 3].position *= BLOCK_LENGTH;
//	vertices[vIndex - 2].position *= BLOCK_LENGTH;
//	vertices[vIndex - 1].position *= BLOCK_LENGTH;
//
//	vertices[vIndex - 4].uv = { 0.f, 1.f / 16.f };
//	vertices[vIndex - 3].uv = { 0.f, 0.f };
//	vertices[vIndex - 2].uv = { 1.f / 16.f, 0.f };
//	vertices[vIndex - 1].uv = { 1.f / 16.f, 1.f / 16.f };
//
//	for (int i = 1; i <= 4; i++)
//		vertices[vIndex - i].uv += TEXTURE_DATA->blockUV[blockType][renderFace];
//}

void Sector::Save(BinaryWriter& out)
{
    for (int x = 0; x < SECTOR_SIZE; x++)
    {
        for (int z = 0; z < SECTOR_SIZE; z++)
        {
            for (int y = 0; y < WORLD_HEIGHT; y++)
            {
                out.Uchar(static_cast<unsigned char>(blocks[x][y][z].blockType));
            }
        }
    }
}

void Sector::Load(BinaryReader& in)
{
	for (int x = 0; x < SECTOR_SIZE; x++)
	{
		for (int z = 0; z < SECTOR_SIZE; z++)
		{
			for (int y = 0; y < WORLD_HEIGHT; y++)
			{
				blocks[x][y][z].blockType = static_cast<BlockType>(in.Uchar());
				blocks[x][y][z].renderFace = 0;
			}
		}
	}
}

int Sector::GetBlockSize()
{
	int count = 0;
	for (int i = 0; i < SECTOR_SIZE; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			for (int k = 0; k < SECTOR_SIZE; k++)
			{
				if (blocks[i][j][k].blockType != BlockType::AIR)
					count++;
			}
		}
	}
	return 0;

}

#include "stdafx.h"

Sector::Sector()
{
	shader = RESOURCE->shaders.Load("block.hlsl");
	material = RESOURCE->materials.Load("BaseBlock.mtl");
	for (int x = 0; x < SECTOR_SIZE; x++)
	{
		for (int z = 0; z < SECTOR_SIZE; z++)
		{
			for (int y = 0; y < 3; y++)
				blocks[x][y][z].blockType = BlockType::EMPTY;
			for (int y = 3; y < 10; y++)
				blocks[x][y][z].blockType = BlockType::EMPTY;
			for (int y = 10; y < WORLD_HEIGHT; y++)
				blocks[x][y][z].blockType = BlockType::EMPTY;
		}
	}
}

bool Sector::RenderHierarchy()
{
	GameObject::RenderHierarchy();
	return false;
}

void Sector::Render()
{
	if (visible)
	{
		if (customMesh and shader and material)
		{
			Transform::Set();
			shader->Set();
			customMesh->Set();
			material->Set();

			D3D->GetDC()->DrawIndexed(customMesh->indexCount, 0, 0);
		}
	}
}

void Sector::Update()
{
	GameObject::Update();
}

void Sector::UpdateMesh()
{
	if (customMesh)
		customMesh->~Mesh();

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

				for (int i = 0; i < 6; i++) {
					if ((blocks[from.x][from.y][from.z].renderFace & sixFaces[i]) != 0)
						AddMeshFace(vertexBuffer, from, sixFaces[i], blocks[from.x][from.y][from.z].blockType);
				}
			}
		}
	}

	if (vertexBuffer.size() == 0)
		return;

	int arr[6] = { 0, 1, 2, 0, 2, 3 };
	for (int i = 0; i < vertexBuffer.size() * 3 / 2; i++)
	{
		for (int j = 0; j < 6; j++)
			indexBuffer.push_back(arr[j] + (i * 4));
	}


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
	
	customMesh = new Mesh(vertices, vertexCount, indices, indexCount, VertexType::PTN);
}

void Sector::AddMeshFace(vector<VertexPTN>& vertices, Int3& pos, const int& renderFace, BlockType& blockType)
{
	const Vector2 uvCube[4] = { { 0.f, 1.f / 16.f }, { 0.f, 0.f }, { 1.f / 16.f, 0.f }, { 1.f / 16.f, 1.f / 16.f } };
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

	//for (int i = 1; i <= 4; i++)
	//	printf("%.1f %.1f %.1f\r\n", vertices[vIndex - i].position.x, vertices[vIndex - i].position.y, vertices[vIndex - i].position.z);
	//printf("\r\n");
	//printf("\r\n");
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
                out.Char(static_cast<char>(blocks[x][y][z].blockType));
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
				blocks[x][y][z].blockType = static_cast<BlockType>(in.Char());
				blocks[x][y][z].renderFace = 0;
			}
		}
	}
}
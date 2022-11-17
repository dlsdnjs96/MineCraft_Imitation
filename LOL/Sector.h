#pragma once




struct Block
{
	BlockType	blockType;
	Vector3		position;
	int			renderFace = 0;
};

struct WorldBlock
{
	BlockType	blockType;
	int			renderFace = 0;
	string to_string() {
		//switch (blockType) {
		//case BlockType::EMPTY:
		//	return "AIR";
		//case BlockType::GRASS:
		//	return "GRASS";
		//case BlockType::WOOD_OAK:
		//	return "WOOD_OAK";
		//case BlockType::WATER:
		//	return "WATER";
		//case BlockType::STONE:
		//	return "STONE";
		//case BlockType::DIRT:
		//	return "DIRT";
		//case BlockType::LEAF:
		//	return "LEAF";
		//}
		return "None";
	}
};

class Sector : public GameObject
{
private:
	const int sixFaces[6] = { BLOCK_FACE_UP, BLOCK_FACE_DOWN, BLOCK_FACE_RIGHT, BLOCK_FACE_LEFT, BLOCK_FACE_FORWARD, BLOCK_FACE_BEHIND };
	Mesh* blockMesh = nullptr;
	Mesh* waterMesh = nullptr;

	shared_ptr<Shader> waterShader = nullptr;

public:
	WorldBlock blocks[SECTOR_SIZE][WORLD_HEIGHT][SECTOR_SIZE];
	int exposureCount = 0;
	Sector();

	bool RenderHierarchy();
	void PreRender();
	void Render();
	void Update();

	void UpdateBlockMesh();
	void UpdateWaterMesh();
	void AddMeshFace(vector<VertexPTN>& vertices, Int3& pos, const int& renderFace, BlockType& blockType);

	void Save(BinaryWriter& out);
	void Load(BinaryReader& in);
};


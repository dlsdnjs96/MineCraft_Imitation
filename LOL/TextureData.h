#pragma once

class TextureData : public Singleton<TextureData>
{
private:

public:
	unordered_map<BlockType, unordered_map<int, Vector2>> blockUV;

	TextureData();
};


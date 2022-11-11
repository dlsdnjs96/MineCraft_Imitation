#include "framework.h"

Text* Text::Create(string name)
{
    Text* temp = new Text();
    temp->name = name;
    temp->type = ObType::TEXT;


    temp->shader = RESOURCE->shaders.Load("6.Cube.hlsl");
    temp->material = RESOURCE->materials.Load("ascii.mtl");
    return temp;
}



void Text::ChangeText(string _text)
{
	//if (mesh) mesh->~Mesh();

    text = _text;

    VertexPT* vertices;
    UINT vertexCount = text.size() * 4;
    UINT* indices;
    UINT indexCount = text.size() * 6;
    VertexType type = VertexType::PT;

    vertices = new VertexPT[vertexCount];
    indices = new UINT[indexCount];

    int vIndex = 0, iIndex = 0;

    for (int i = 0; i < text.size(); i++)
    {
        char ch = text.c_str()[i];
        Vector2 from;
        Vector3 pos;

        Util::Saturate(ch, char(0), char(127));
        from.x = static_cast<float>(ch % 16) / 16.f;
        from.y = static_cast<float>(ch / 16) / 16.f;
        pos.x = static_cast<float>(i) * 0.1f;
        pos.y = 0.f;
        pos.z = 0.f;


        vertices[vIndex].position = { pos.x + 0.1f, pos.y - 0.1f, pos.z };
        vertices[vIndex].uv = from + Vector2{ 1.f / 16.f, 1.f / 16.f };
        vIndex++;
        vertices[vIndex].position = { pos.x + 0.1f, pos.y, pos.z };
        vertices[vIndex].uv = from + Vector2{ 1.f / 16.f, 0.f };
        vIndex++;
        vertices[vIndex].position = { pos.x, pos.y, pos.z };
        vertices[vIndex].uv = from + Vector2{ 0.f, 0.f };
        vIndex++;
        vertices[vIndex].position = { pos.x, pos.y - 0.1f, pos.z };
        vertices[vIndex].uv = from + Vector2{ 0.f, 1.f / 16.f };
        vIndex++;

        int arr[6] = { 3, 2, 0, 2, 1, 0 };
        for (int j = 0; j < 6; j++) {
            indices[iIndex] = arr[j] + vIndex - 4;
            iIndex++;
        }
    }


    mesh = make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);
}

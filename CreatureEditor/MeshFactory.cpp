#include "stdafx.h"

void MeshFactory::OneFaceBlock()
{
    VertexP cubeEdges[8] = {
    {{ -1.f, 1.f,  -1.f }},
    {{ -1.f, 1.f,  1.f }},
    {{ 1.f,  1.f,  1.f }},
    {{ 1.f,  1.f,  -1.f }},
    {{ -1.f, -1.f, -1.f }},
    {{ -1.f, -1.f, 1.f }},
    {{ 1.f,  -1.f, 1.f }},
    {{ 1.f,  -1.f, -1.f }}
    };

    int edgesIndex[6][4] = {
        { 3, 2, 1, 0 },
        { 6, 7, 4, 5 },
        { 6, 2, 3, 7 },
        { 4, 0, 1, 5 },
        { 7, 3, 0, 4 },
        { 5, 1, 2, 6 }
    };
    Vector2 uvs[4] = {
        { 1.f, 1.f },
        { 0.f, 1.f },
        { 0.f, 0.f },
        { 1.f, 0.f }
    };
    Vector3 normals[6] = {
        { 0.f, 1.f, 0.f },
        { 0.f, -1.f, 0.f },
        { 1.f, 0.f, 0.f },
        { -1.f, 0.f, 0.f },
        { 0.f, 0.f, -1.f },
        { 0.f, 0.f, 1.f }
    };

    VertexPTN* vertices;
    UINT vertexCount = 6 * 4;
    UINT* indices;
    UINT indexCount = 6 * 6;
    VertexType type = VertexType::PTN;

    vertices = new VertexPTN[vertexCount];
    indices = new UINT[indexCount];

    int vIndex = 0, iIndex = 0;


    for (int j = 0; j < 6; j++) {

        for (int i = 0; i < 4; i++) {
            vertices[vIndex].position = cubeEdges[edgesIndex[j][i]].position;
            vertices[vIndex].position *= 1.f;
            vertices[vIndex].normal = normals[j];
            vertices[vIndex].uv = uvs[i];
            vIndex++;
        }
        // int arr[6] = { 0, 1, 2, 0, 2, 3 };
        int arr[6] = { 3, 2, 0, 2, 1, 0 };

        for (int i = 0; i < 6; i++) {
            indices[iIndex] = arr[i] + vIndex - 4;
            iIndex++;
        }
    }


    Mesh* newMesh = new Mesh(vertices, vertexCount, indices, indexCount, type);
    newMesh->SaveFile("6.OneFaceBlock.mesh");

    printf("Saved mesh\r\n");
}

shared_ptr<Mesh> MeshFactory::EditMesh(EditObject& _editObject)
{
    VertexP cubeEdges[8] = {
    {{ -1.f, 1.f,  -1.f }},
    {{ -1.f, 1.f,  1.f }},
    {{ 1.f,  1.f,  1.f }},
    {{ 1.f,  1.f,  -1.f }},
    {{ -1.f, -1.f, -1.f }},
    {{ -1.f, -1.f, 1.f }},
    {{ 1.f,  -1.f, 1.f }},
    {{ 1.f,  -1.f, -1.f }}
    };

    int edgesIndex[6][4] = {
        { 3, 2, 1, 0 },
        { 6, 7, 4, 5 },
        { 6, 2, 3, 7 },
        { 4, 0, 1, 5 },
        { 7, 3, 0, 4 },
        { 5, 1, 2, 6 }
    };
    Vector2 uvs[4] = {
        { 1.f, 1.f },
        { 0.f, 1.f },
        { 0.f, 0.f },
        { 1.f, 0.f }
    };
    Vector3 normals[6] = {
        { 0.f, 1.f, 0.f },
        { 0.f, -1.f, 0.f },
        { 1.f, 0.f, 0.f },
        { -1.f, 0.f, 0.f },
        { 0.f, 0.f, -1.f },
        { 0.f, 0.f, 1.f }
    };

    pair<Vector2, Vector2> uvArr[6] = { _editObject.uvUp, _editObject.uvDown, _editObject.uvRight, _editObject.uvLeft, _editObject.uvBack, _editObject.uvFront };

    VertexPTN* vertices;
    UINT vertexCount = 6 * 4;
    UINT* indices;
    UINT indexCount = 6 * 6;
    VertexType type = VertexType::PTN;

    vertices = new VertexPTN[vertexCount];
    indices = new UINT[indexCount];

    int vIndex = 0, iIndex = 0;

    for (int i = 0; i < 8; i++)
    {
        cubeEdges[i].position.x *= _editObject.meshSize.x;
        cubeEdges[i].position.y *= _editObject.meshSize.y;
        cubeEdges[i].position.z *= _editObject.meshSize.z;

        cubeEdges[i].position.x += _editObject.meshFrom.x;
        cubeEdges[i].position.y += _editObject.meshFrom.y;
        cubeEdges[i].position.z += _editObject.meshFrom.z;
    }


    for (int j = 0; j < 6; j++) {

        for (int i = 0; i < 4; i++) {
            vertices[vIndex].position = cubeEdges[edgesIndex[j][i]].position;
            vertices[vIndex].position *= 1.f;
            vertices[vIndex].normal = normals[j];
            vertices[vIndex].uv = uvs[i];
            vIndex++;
        }
        vertices[vIndex - 4].uv = uvArr[j].second;
        vertices[vIndex - 3].uv = { uvArr[j].second.x, uvArr[j].first.y };
        vertices[vIndex - 2].uv = uvArr[j].first;
        vertices[vIndex - 1].uv = { uvArr[j].first.x, uvArr[j].second.y };


        int arr[6] = { 3, 2, 0, 2, 1, 0 };

        for (int i = 0; i < 6; i++) {
            indices[iIndex] = arr[i] + vIndex - 4;
            iIndex++;
        }
    }


    printf("Edited mesh\r\n");
    return make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);
}

#include "framework.h"
Mesh::Mesh()
    :vertices(nullptr), indices(nullptr)
    , vertexBuffer(nullptr), indexBuffer(nullptr)
{


    ////////////////////////////////////////////////////
    vertexType = VertexType::PT;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;


    VertexPT* Vertex;
    byteWidth = sizeof(VertexPT);
    vertexCount = 4;
    indexCount = 4;
    file = "6.UI.mesh";

    Vertex = new VertexPT[vertexCount];
    indices = new UINT[indexCount];

    Vertex[0].position = Vector3(-0.5f, -0.5f, 0.1f);
    Vertex[0].uv = Vector2(0.0f, 1.0f);
    indices[0] = 0;

    Vertex[1].position = Vector3(-0.5f, 0.5f, 0.1f);
    Vertex[1].uv = Vector2(0.0f, 0.0f);
    indices[1] = 1;

    Vertex[2].position = Vector3(0.5f, -0.5f, 0.1f);
    Vertex[2].uv = Vector2(1.0f, 1.0f);
    indices[2] = 2;

    Vertex[3].position = Vector3(0.5f, 0.5f, 0.1f);
    Vertex[3].uv = Vector2(1.0f, 0.0f);
    indices[3] = 3;

    /////////////////////////////////////////////////////
    vertices = (void*)Vertex;
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }
    //저장용
    //SaveFile(file);
}

Mesh::Mesh(void* vertices, UINT vertexCount, UINT* indices, UINT indexCount, VertexType type)
{
    vertexType = type;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    switch (type)
    {
    case VertexType::P:
        byteWidth = sizeof(VertexP);
        break;
    case VertexType::PC:
        byteWidth = sizeof(VertexPC);
        break;
    case VertexType::PCN:
        byteWidth = sizeof(VertexPCN);
        break;
    case VertexType::PTN:
        byteWidth = sizeof(VertexPTN);
        break;
    case VertexType::MODEL:
        byteWidth = sizeof(VertexModel);
        break;

    case VertexType::TERRAIN:
        byteWidth = sizeof(VertexTerrain);
        break;
    case VertexType::PT:
        byteWidth = sizeof(VertexPT);
        break;
    case VertexType::PS:
        byteWidth = sizeof(VertexPS);
        break;
    case VertexType::PSV:
        byteWidth = sizeof(VertexPSV);
        break;
    }
    ////////////////////////////////////////////////////

    ///////////////////////////////////////////////////
    this->vertices = vertices;
    this->vertexCount = vertexCount;
    this->indices = indices;
    this->indexCount = indexCount;

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }
}


Mesh::~Mesh()
{
    switch (vertexType)
    {
    case VertexType::P:
        delete[](VertexP*)vertices;
        break;
    case VertexType::PC:
        delete[](VertexPC*)vertices;
        break;
    case VertexType::PCN:
        delete[](VertexPCN*)vertices;
        break;
    case VertexType::PTN:
        delete[](VertexPTN*)vertices;
        break;
    case VertexType::MODEL:
        delete[](VertexModel*)vertices;
        break;
    case VertexType::TERRAIN:
        delete[](VertexTerrain*)vertices;
        break;
    case VertexType::PT:
        delete[](VertexPT*)vertices;
        break;
    case VertexType::PS:
        delete[](VertexPS*)vertices;
        break;
    case VertexType::PSV:
        delete[](VertexPSV*)vertices;
        break;
    }
    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
    SafeDeleteArray(indices);
}

void Mesh::Set()
{
    UINT offset = 0;
    D3D->GetDC()->IASetVertexBuffers(0,
        1,
        &vertexBuffer,
        &byteWidth,
        &offset);
    D3D->GetDC()->IASetPrimitiveTopology
    (primitiveTopology);
    D3D->GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::LoadFile(string file)
{
    this->file = file;
   

    BinaryReader in;
    wstring path = L"../Contents/Mesh/" + Util::ToWString(file);
    in.Open(path);

    vertexType = (VertexType)in.UInt();

    //읽기전
    switch (vertexType)
    {
    case VertexType::P:
        if (vertices)delete[](VertexP*)vertices;
        break;
    case VertexType::PC:
        if (vertices)delete[](VertexPC*)vertices;
        break;
    case VertexType::PCN:
        if (vertices)delete[](VertexPCN*)vertices;
        break;
    case VertexType::PTN:
        if (vertices)delete[](VertexPTN*)vertices;
        break;
    case VertexType::MODEL:
        if (vertices)delete[](VertexModel*)vertices;
        break;
    case VertexType::TERRAIN:
        if (vertices)delete[](VertexTerrain*)vertices;
        break;
    case VertexType::PT:
        if (vertices)delete[](VertexPT*)vertices;
        break;
    case VertexType::PS:
        if (vertices)delete[](VertexPS*)vertices;
        break;
    case VertexType::PSV:
        if (vertices)delete[](VertexPSV*)vertices;
        break;
    }

    primitiveTopology = (D3D_PRIMITIVE_TOPOLOGY)in.UInt();
    byteWidth = in.UInt();
    vertexCount = in.UInt();
    indexCount = in.UInt();

    SafeDeleteArray(indices);
    indices = new UINT[indexCount];


    //읽고난후
    switch (vertexType)
    {
    case VertexType::P:
    {
        vertices = new VertexP[vertexCount];
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
        }
        break;
    }

    case VertexType::PC:
    {
        vertices = new VertexPC[vertexCount];
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
        }
        break;
    }
    case VertexType::PCN:
    {
        vertices = new VertexPCN[vertexCount];
        VertexPCN* vertex = (VertexPCN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
            vertex[i].normal = in.vector3();
        }
        break;
    }
    case VertexType::PTN:
    {
        vertices = new VertexPTN[vertexCount];
        VertexPTN* vertex = (VertexPTN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
        }
        break;
    }
    case VertexType::MODEL:
    {
        vertices = new VertexModel[vertexCount];
        VertexModel* vertex = (VertexModel*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
            vertex[i].tangent = in.vector3();
            vertex[i].indices = in.vector4();
            vertex[i].weights = in.vector4();
        }
        break;
    }
    case VertexType::TERRAIN:
    {
        vertices = new VertexTerrain[vertexCount];
        VertexTerrain* vertex = (VertexTerrain*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
            vertex[i].weights = in.Float();
        }
        break;
    }
    case VertexType::PT:
    {
        vertices = new VertexPT[vertexCount];
        VertexPT* vertex = (VertexPT*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
        }
        break;
    }
    case VertexType::PS:
    {
        vertices = new VertexPS[vertexCount];
        VertexPS* vertex = (VertexPS*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].size = in.vector2();
        }
        break;
    }
    case VertexType::PSV:
    {
        vertices = new VertexPSV[vertexCount];
        VertexPSV* vertex = (VertexPSV*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].size = in.vector2();
            vertex[i].velocity = in.vector3();
        }
        break;
    }
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        indices[i] = in.UInt();
    }
    in.Close();

    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }

}

void Mesh::SaveFile(string file)
{
    this->file = file;
    BinaryWriter out;
    wstring path = L"../Contents/Mesh/" + Util::ToWString(file);
    out.Open(path);

    out.UInt((UINT)vertexType);
    out.UInt((UINT)primitiveTopology);
    out.UInt(byteWidth);
    out.UInt(vertexCount);
    out.UInt(indexCount);

    switch (vertexType)
    {
    case VertexType::P:
    {
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
        }
        break;
    }

    case VertexType::PC:
    {
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
        }
        break;
    }
    case VertexType::PCN:
    {
        VertexPCN* vertex = (VertexPCN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
            out.vector3(vertex[i].normal);
        }
        break;
    }
    case VertexType::PTN:
    {
        VertexPTN* vertex = (VertexPTN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
        }
        break;
    }
    case VertexType::MODEL:
    {
        VertexModel* vertex = (VertexModel*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
            out.vector3(vertex[i].tangent);
            out.vector4(vertex[i].indices);
            out.vector4(vertex[i].weights);
        }
        break;
    }
    case VertexType::TERRAIN:
    {
        VertexTerrain* vertex = (VertexTerrain*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
            out.Float(vertex[i].weights);
        }
        break;
    }
    case VertexType::PT:
    {
        VertexPT* vertex = (VertexPT*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
        }
        break;
    }
    case VertexType::PS:
    {
        VertexPS* vertex = (VertexPS*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].size);
        }
        break;
    }
    case VertexType::PSV:
    {
        VertexPSV* vertex = (VertexPSV*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].size);
            out.vector3(vertex[i].velocity);
        }
        break;
    }
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        out.UInt(indices[i]);
    }
    out.Close();
}

const Vector3& Mesh::GetVertexPosition(UINT idx)
{
    if (vertexType == VertexType::PC)
    {
        VertexPC* Vertices = (VertexPC*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PCN)
    {
        VertexPCN* Vertices = (VertexPCN*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PTN)
    {
        VertexPTN* Vertices = (VertexPTN*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::MODEL)
    {
        VertexModel* Vertices = (VertexModel*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::TERRAIN)
    {
        VertexTerrain* Vertices = (VertexTerrain*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PT)
    {
        VertexPT* Vertices = (VertexPT*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PS)
    {
        VertexPS* Vertices = (VertexPS*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PSV)
    {
        VertexPSV* Vertices = (VertexPSV*)vertices;
        return Vertices[indices[idx]].position;
    }

    VertexP* Vertices = (VertexP*)vertices;
    return Vertices[indices[idx]].position;
}

Vector3& Mesh::SetVertexPosition(UINT idx)
{
    if (vertexType == VertexType::PC)
    {
        VertexPC* Vertices = (VertexPC*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PCN)
    {
        VertexPCN* Vertices = (VertexPCN*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PTN)
    {
        VertexPTN* Vertices = (VertexPTN*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::MODEL)
    {
        VertexModel* Vertices = (VertexModel*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::TERRAIN)
    {
        VertexTerrain* Vertices = (VertexTerrain*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PT)
    {
        VertexPT* Vertices = (VertexPT*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PS)
    {
        VertexPS* Vertices = (VertexPS*)vertices;
        return Vertices[indices[idx]].position;
    }
    else if (vertexType == VertexType::PSV)
    {
        VertexPSV* Vertices = (VertexPSV*)vertices;
        return Vertices[indices[idx]].position;
    }

    VertexP* Vertices = (VertexP*)vertices;
    return Vertices[indices[idx]].position;
}

void Mesh::UpdateMesh()
{
    D3D->GetDC()->UpdateSubresource
    (vertexBuffer, 0, NULL, vertices, 0, 0);
}



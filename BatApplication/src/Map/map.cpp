#include "BatApplication/precompiled.h"
#include "ProtoGraphicsLib/mesh.h"
#include "BatApplication/Map/map.h"
#include "BatApplication/Map/jsonmaploader.h"

//Eventually when a map is created I should save a mesh from that file but for now whateva
Map::Map(std::string path) : m_Width(0), m_Height(0),m_tWidth(0),m_tHeight(0)
{
    JSONMapLoader maploader;
    maploader.Parse(path.c_str());
    m_Height = maploader.m_h;
    m_Width = maploader.m_w;
    m_tHeight = maploader.m_th;
    m_tWidth = maploader.m_tw;
    m_Layers = maploader.m_Layers;
    m_TileSets = maploader.m_TileSets;
}

Map::~Map()
{
}
void Map::Init()
{
}
void Map::GenerateLayerMesh(Layer& layer, RenderSystem& entity)
{
    u32 vertIndex = 0;
    std::vector<Vertex> vertices(m_Width * m_Height * 6);
    for(u32 y = 0; y < m_Height; ++y)
    {
        for(u32 x = 0; x < m_Width; ++x)
        {
            u32 id = layer.m_Tiles[x + y * m_Width];
            if(id != 0)
            {
                glm::vec3 vec1 = glm::vec3((x+1) * m_tWidth,-(s32)((y+1) * m_tHeight),0);
                glm::vec3 vec2 = glm::vec3(x * m_tWidth,-(s32)((y+1) * m_tHeight),0);
                glm::vec3 vec3 = glm::vec3(x * m_tWidth,-(s32)(y * m_tHeight),0);
                glm::vec3 vec4 = glm::vec3((x+1) * m_tWidth,-(s32)(y * m_tHeight),0);

                Vertex& vert0 = vertices[vertIndex++];
                Vertex& vert1 = vertices[vertIndex++];
                Vertex& vert2 = vertices[vertIndex++];
                Vertex& vert3 = vertices[vertIndex++];
                Vertex& vert4 = vertices[vertIndex++];
                Vertex& vert5 = vertices[vertIndex++];

                vert0.Position = vec1;
                vert1.Position = vec2;
                vert2.Position = vec3;
                vert3.Position = vec3;
                vert4.Position = vec1;
                vert5.Position = vec4;

                f32 f = 32.0f/256.0f;
                f32 u1 = (f32)(id-1) * f;
                f32 u2 = (f32)id * f;
                f32 v1 = 1-(f32)((u32)((id-1)/8)+1) * f;
                f32 v2 = 1-(f32)(u32)((id-1)/8) * f;

                vert0.UV = glm::vec2(u2,v1);
                vert1.UV = glm::vec2(u1,v1);
                vert2.UV = glm::vec2(u1,v2);
                vert3.UV = glm::vec2(u1,v2);
                vert4.UV = glm::vec2(u2,v1);
                vert5.UV = glm::vec2(u2,v2);
            }
        }
    }

    entity.p_Mesh = new Mesh(vertices);
}
void Map::GetObjectIDs(Layer& layer, std::vector<u32>& ids)
{
    u32 index = 0;
    u32 firstID = m_TileSets[layer.m_TileSetID].m_firstgid-1;
    ids.reserve(m_Width * m_Height);
    for(u32 y = 0; y < m_Height; ++y)
    {
        for(u32 x = 0; x < m_Width; ++x)
        {
            u32 id = layer.m_Tiles[x + y * m_Width];
            if(id != 0)
            {
                ids.push_back(id - firstID);
            }
            else
            {
                ids.push_back(id);
            }
            ++index;
        }
    }
}

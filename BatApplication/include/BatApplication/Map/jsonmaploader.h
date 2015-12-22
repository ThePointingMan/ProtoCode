#ifndef JSONMAPLOADER_H
#define JSONMAPLOADER_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "map.h"

using namespace rapidjson;
class JSONMapLoader
{
    public:
        JSONMapLoader();
        ~JSONMapLoader();
        bool Parse(const char* path);
        std::vector<Layer> m_Layers;

        u32 m_w, m_h, m_tw, m_th;
        glm::vec2 m_ImageDimensions;
        std::string m_ImagePath;
        Document m_Doc;
};

#endif // JSONMAPLOADER_H

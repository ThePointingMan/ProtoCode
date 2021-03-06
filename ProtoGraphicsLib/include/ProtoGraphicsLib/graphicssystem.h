#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H


// File: graphicssystem.h
// Description: The main Graphics system, handles rendering crap, and general initialization/destruction of the graphics system
// Copywrite: Nathan Boyes - 07/03/2015

#include "renderobject.h"
#include "ProtoGraphicsLib/shader.h"
#include "ProtoGraphicsLib/mesh.h"
#include "BatKernel/batcore.h"
class GraphicsSystem : public IBatGraphicsSystem
{
    public:
        GraphicsSystem();
        virtual ~GraphicsSystem();

        //TODO Delete this
        typeid_t id;
        virtual void DrawRenderObject(const System& target,glm::mat4 matrix);
        virtual bool Initialize(ResourceManager* resSystem);
        //virtual void DrawRenderObject(const RenderObject& target,glm::mat4 matrix);

    protected:
        ResourceManager* m_ResourceData;
    private:
};

#endif // GRAPHICSSYSTEM_H

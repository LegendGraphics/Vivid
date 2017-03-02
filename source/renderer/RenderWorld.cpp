#include "RenderWorld.h"

#include "common/Object.h"
#include "renderer/Device/RenderContext.h"
#include "renderer/Device/RenderDevice.h"
#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/PipelineResource.h"

#include "math/Vector3.h"

namespace te
{
    void renderKernel(RenderWorld::RenderParams& params, RenderContext* rContext)
    {
        // culling, prepare RenderQueue
        RenderQueue& rQueue = params._renderQueue;

        // iterate each object
        for (RenderQueueItem& rqItem : rQueue)
        {
            if (rqItem.type == RenderMeshObject::TYPE)
                ((RenderMeshObject*)rqItem.node)->render(rContext, params._camera, params._device);
        }
    }

    void RenderWorld::render(RenderParams& params)
    {
        RenderContext* renderContext = (params._device->newContext());
        renderContext->_camera = params._camera;

        // process pipeline config here
        for (PipelineStage& stage :params._pipelineRes->_stages)
        {
            for (PipelineCommand& pc : stage.commands)
            {
                switch (pc.command)
                {
                case PipelineCommand::List::SetTarget:
                    break;
                case PipelineCommand::List::DrawGeometry:
                    // generate render job package (commands) into RenderContext
                    // separate this from real job will benefit for multi-thread
                    renderKernel(params, renderContext);
                    break;
                case PipelineCommand::List::ClearTarget:
                    break;
                }
            }
        }

        // send render job package to RenderDevice for real work
        params._device->dispatch(renderContext);
    }

    // helper function
    void RenderWorld::createPrimitives(RenderDevice* device)
    {
        //// Unit cube
        //float cubeVerts[8 * 3] = {  // x, y, z
        //    0.f, 0.f, 1.f,   1.f, 0.f, 1.f,   1.f, 1.f, 1.f,   0.f, 1.f, 1.f,
        //    0.f, 0.f, 0.f,   1.f, 0.f, 0.f,   1.f, 1.f, 0.f,   0.f, 1.f, 0.f
        //};
        //uint16 cubeInds[36] = {
        //    0, 1, 2, 2, 3, 0,   1, 5, 6, 6, 2, 1,   5, 4, 7, 7, 6, 5,
        //    4, 0, 3, 3, 7, 4,   3, 2, 6, 6, 7, 3,   4, 5, 1, 1, 0, 4
        //};
        //_vbCube = device->createVertexBuffer(8 * 3 * sizeof(float), cubeVerts);
        //_ibCube = device->createIndexBuffer(36 * sizeof(uint16), cubeInds);

        //// Unit (geodesic) sphere (created by recursively subdividing a base octahedron)
        //Vec3f spVerts[126] = {  // x, y, z
        //    Vec3f(0.f, 1.f, 0.f),   Vec3f(0.f, -1.f, 0.f),
        //    Vec3f(-0.707f, 0.f, 0.707f),   Vec3f(0.707f, 0.f, 0.707f),
        //    Vec3f(0.707f, 0.f, -0.707f),   Vec3f(-0.707f, 0.f, -0.707f)
        //};
        //uint16 spInds[128 * 3] = {  // Number of faces: (4 ^ iterations) * 8
        //    2, 3, 0,   3, 4, 0,   4, 5, 0,   5, 2, 0,   2, 1, 3,   3, 1, 4,   4, 1, 5,   5, 1, 2
        //};
        //for (uint32 i = 0, nv = 6, ni = 24; i < 2; ++i)  // Two iterations
        //{
        //    // Subdivide each face into 4 tris by bisecting each edge and push vertices onto unit sphere
        //    for (uint32 j = 0, prevNumInds = ni; j < prevNumInds; j += 3)
        //    {
        //        spVerts[nv++] = ((spVerts[spInds[j + 0]] + spVerts[spInds[j + 1]]) * 0.5f).normalized();
        //        spVerts[nv++] = ((spVerts[spInds[j + 1]] + spVerts[spInds[j + 2]]) * 0.5f).normalized();
        //        spVerts[nv++] = ((spVerts[spInds[j + 2]] + spVerts[spInds[j + 0]]) * 0.5f).normalized();

        //        spInds[ni++] = spInds[j + 0]; spInds[ni++] = nv - 3; spInds[ni++] = nv - 1;
        //        spInds[ni++] = nv - 3; spInds[ni++] = spInds[j + 1]; spInds[ni++] = nv - 2;
        //        spInds[ni++] = nv - 2; spInds[ni++] = spInds[j + 2]; spInds[ni++] = nv - 1;
        //        spInds[j + 0] = nv - 3; spInds[j + 1] = nv - 2; spInds[j + 2] = nv - 1;
        //    }
        //}
        //_vbSphere = device->createVertexBuffer(126 * sizeof(Vec3f), spVerts);
        //_ibSphere = device->createIndexBuffer(128 * 3 * sizeof(uint16), spInds);
    }
}
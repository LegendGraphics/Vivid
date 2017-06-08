// *************************************************************************************************
//
// Horde3D
//   Next-Generation Graphics Engine
// --------------------------------------
// Copyright (C) 2006-2011 Nicolas Schulz
//
// This software is distributed under the terms of the Eclipse Public License v1.0.
// A copy of the license may be obtained at: http://www.eclipse.org/legal/epl-v10.html
//
// *************************************************************************************************

#ifndef _converter_H_
#define _converter_H_

#include "daeMain.h"
#include "utMath.h"
#include <string.h> // memset

using namespace Horde3D;

// the data structure to write
// should be almost the same as reading part


struct Vertex
{
    Vec3f  storedPos, pos;
    Vec3f  storedNormal, normal, tangent, bitangent;
    Vec3f  texCoords[4];
    int    daePosIndex;
};


struct TriGroup
{
    unsigned int  first, count;
    unsigned int  vertRStart, vertREnd;
    std::string   matName;

    unsigned int                 numPosIndices;
    std::vector< unsigned int >  *posIndexToVertices;

    TriGroup() : posIndexToVertices(0x0)
    {
    }

    ~TriGroup() { delete[] posIndexToVertices; }
};


struct SceneNode
{
    char                        name[256];
    Matrix4f                    matRel, matAbs;
    DaeNode                     *daeNode;
    DaeInstance                 *daeInstance;
    SceneNode                   *parent;
    std::vector< SceneNode * >  children;

    SceneNode()
    {
        memset(name, 0, sizeof(name));
        daeNode = 0x0;
        daeInstance = 0x0;
        parent = 0x0;
    }

    virtual ~SceneNode()
    {
        for( unsigned int i = 0; i < children.size(); ++i ) delete children[i];
    }
};


struct Mesh : public SceneNode
{
    std::vector< TriGroup* > triGroups;
    
    Mesh()
    {
        parent = 0x0;
    }

    ~Mesh() { for( int i = triGroups.size(); i>0; ) delete triGroups[--i];  }

};


class Converter
{
public:
    Converter( ColladaDocument &doc, const std::string &outPath);
    ~Converter();
    
    bool convertModel( bool optimize );
    
    bool writeModel( const std::string &assetPath, const std::string &assetName, const std::string &modelName );
private:
    Matrix4f getNodeTransform( DaeNode &node, unsigned int frame );
    SceneNode *findNode( const char *name, SceneNode *ignoredNode );
    void checkNodeName( SceneNode *node );
    bool validateInstance( const std::string &instanceId );
    SceneNode *processNode( DaeNode &node, SceneNode *parentNode,
                            Matrix4f transAccum);
    void calcTangentSpaceBasis( std::vector< Vertex > &vertices );
 
    void processMeshes( bool optimize );
    bool writeMesh( const std::string &assetPath, const std::string &assetName );
    void writeSGNode( const std::string &assetPath, const std::string &modelName, SceneNode *node, unsigned int depth, std::ofstream &outf );
    bool writeSceneGraph( const std::string &assetPath, const std::string &assetName, const std::string &modelName );

private:
    ColladaDocument              &_daeDoc;

    unsigned int                 _vertex_type;
    
    std::vector< Vertex >        _vertices;
    std::vector< unsigned int >  _indices;
    std::vector< Mesh * >        _meshes;
    std::vector< SceneNode* >    _nodes;

    std::string                  _outPath;
};

#endif // _converter_H_

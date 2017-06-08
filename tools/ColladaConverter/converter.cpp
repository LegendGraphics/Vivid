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

#if defined( _MSC_VER )
#   if _MSC_VER >= 1400
#       define _CRT_SECURE_NO_DEPRECATE
#   endif
#endif

#include "converter.h"
#include "optimizer.h"
#include "utPlatform.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


Converter::Converter( ColladaDocument &doc, const string &outPath) :
    _daeDoc( doc )
{
    _outPath = outPath;
}


Converter::~Converter()
{
    for( unsigned int i = 0; i < _nodes.size(); ++i ) delete _nodes[i];	
}


SceneNode *Converter::findNode( const char *name, SceneNode *ignoredNode )
{
    for( size_t i = 0, s = _meshes.size(); i < s; ++i )
    {
        if( _meshes[i] != ignoredNode && strcmp( _meshes[i]->name, name ) == 0 )
            return _meshes[i];
    }

    return 0x0;
}


void Converter::checkNodeName( SceneNode *node )
{
    // Check if a different node with the same name exists
    if( findNode( node->name, node ) != 0x0 )
    {
        // If necessary, cut name to make room for the postfix
        if( strlen( node->name ) > 240 ) node->name[240] = '\0';

        char newName[256];
        unsigned int index = 2;

        // Find a free name
        while( true )
        {
            sprintf( newName, "%s_%i", node->name, index++ );

            if( !findNode( newName, node ) )
            {
                char msg[1024];
                sprintf( msg, "Warning: Node with name '%s' already exists. "
                         "Node was renamed to '%s'.", node->name, newName );
                log( msg );
                
                strcpy( node->name, newName );
                break;
            }
        }
    }
}


bool Converter::validateInstance( const std::string &instanceId )
{
    string id = instanceId;
    
    DaeSkin *skin = _daeDoc.libControllers.findSkin( id );
    DaeMorph *morpher = _daeDoc.libControllers.findMorph( id );
    
    // Resolve controller stack
    if( skin != 0x0 )
    {	
        id = skin->ownerId;
        morpher = _daeDoc.libControllers.findMorph( id );
        if( morpher != 0x0 ) id = morpher->ownerId;
    }
    else if( morpher != 0x0 )
    {
        id = morpher->ownerId;
        skin = _daeDoc.libControllers.findSkin( id );
        if( skin != 0x0 ) id = skin->ownerId;
    }
    
    DaeGeometry *geo = _daeDoc.libGeometries.findGeometry( id );
    return geo != 0x0 && !geo->triGroups.empty();
}


SceneNode *Converter::processNode( DaeNode &node, SceneNode *parentNode,
                                   Matrix4f transAccum)
{
    // Note: animTransAccum is used for pure transformation nodes of Collada that are no joints or meshes
    
    // Process instances and create nodes using the following rules:
    //		* DaeJoint and no Instance -> create joint
    //		* DaeJoint and one Instance -> create joint and mesh
    //		* DaeJoint and several Instances -> create joint and mesh with submeshes
    //		* DaeNode and no Instance -> forward transformation to children (pure transformation node)
    //		* DaeNode and one Instance -> create mesh
    //		* DaeNode and several Instances -> create mesh with submeshes
    
    if (node.reference )
    {
        DaeNode* n = _daeDoc.libNodes.findNode( node.name );
        if( n )	return processNode( *n, parentNode, transAccum);
        else log( "Warning: undefined reference '"+ node.name +"' in instance_node" );
        return 0x0;
    }

    // Assemble matrix
    Matrix4f relMat = transAccum * makeMatrix4f( node.assembleMatrix().transposed().x, _daeDoc.y_up );
    
    SceneNode *oNode = 0x0;
    
    // Find valid instances
    std::vector< int > validInsts;
    for( unsigned int i = 0; i < node.instances.size(); ++i )
    {
        if( validateInstance( node.instances[i].url ) )
            validInsts.push_back( i );
    }
    
    // Create node
    if (!validInsts.empty())
    {
        oNode = new Mesh();
        _meshes.push_back((Mesh *)oNode);
        oNode->daeInstance = &node.instances[validInsts[0]];
    }
    
    // Set node params
    if( oNode != 0x0 )
    {
        oNode->parent = parentNode;
        oNode->daeNode = &node;
        oNode->matRel = relMat;
        
        // Name
        if( node.name.length() > 255 )
        {
            log( "Warning: node name is too long" );
            node.name.erase( 255, node.name.length() - 255 );
        }
        strcpy( oNode->name, node.name.c_str() );

        // Check for duplicate node name
        checkNodeName( oNode );
            
        // Calculate absolute transformation
        if( parentNode != 0x0 ) oNode->matAbs = parentNode->matAbs * oNode->matRel;
        else oNode->matAbs = oNode->matRel;
    }

    // Create sub-nodes if necessary
    if( oNode != 0x0 )
    {
        if( !node.joint && validInsts.size() > 1 )
        {
            // Create submeshes
            for( unsigned int i = 1; i < validInsts.size(); ++i )
            {
                SceneNode *oNode2 = new Mesh();
                _meshes.push_back( (Mesh *)oNode2 );
                oNode->children.push_back( _meshes.back() );

                *oNode2 = *oNode;
                oNode2->matRel = Matrix4f();
                oNode2->daeInstance = &node.instances[validInsts[i]];
                oNode2->parent = oNode;
                oNode2->children.clear();
            }
        }
    }

    if( oNode != 0x0 ) transAccum = Matrix4f();
    else transAccum = relMat;
    
    // Process children
    for( unsigned int i = 0; i < node.children.size(); ++i )
    {
        SceneNode *parNode = oNode != 0x0 ? oNode : parentNode;
        
        SceneNode *childNode = processNode( *node.children[i], parNode,
                                            transAccum );
        if( childNode != 0x0 && parNode != 0x0 ) parNode->children.push_back( childNode );
    }

    return oNode;
}


void Converter::calcTangentSpaceBasis( vector<Vertex> &verts )
{
    for( unsigned int i = 0; i < verts.size(); ++i )
    {
        verts[i].normal = Vec3f( 0, 0, 0 );
        verts[i].tangent = Vec3f( 0, 0, 0 );
        verts[i].bitangent = Vec3f( 0, 0, 0 );
    }
    
    // Basic algorithm: Eric Lengyel, Mathematics for 3D Game Programming & Computer Graphics
    for( unsigned int i = 0; i < _meshes.size(); ++i )
    {
        for( unsigned int j = 0; j < _meshes[i]->triGroups.size(); ++j )
        {
            TriGroup *triGroup = _meshes[i]->triGroups[j];
            
            for( unsigned int k = triGroup->first; k < triGroup->first + triGroup->count; k += 3 )
            {
                // Compute basis vectors for triangle
                Vec3f edge1uv = verts[_indices[k + 1]].texCoords[0] - verts[_indices[k]].texCoords[0];
                Vec3f edge2uv = verts[_indices[k + 2]].texCoords[0] - verts[_indices[k]].texCoords[0];
                Vec3f edge1 = verts[_indices[k + 1]].pos - verts[_indices[k]].pos;
                Vec3f edge2 = verts[_indices[k + 2]].pos - verts[_indices[k]].pos;
                Vec3f normal = edge1.cross( edge2 );  // Normal weighted by triangle size (hence unnormalized)

                float r = 1.0f / (edge1uv.x * edge2uv.y - edge2uv.x * edge1uv.y); // UV area normalization
                Vec3f uDir = (edge1 * edge2uv.y - edge2 * edge1uv.y) * r;
                Vec3f vDir = (edge2 * edge1uv.x - edge1 * edge2uv.x) * r;

                // Accumulate basis for vertices
                for( unsigned int l = 0; l < 3; ++l )
                {
                    verts[_indices[k + l]].normal += normal;
                    verts[_indices[k + l]].tangent += uDir;
                    verts[_indices[k + l]].bitangent += vDir;

                    // Handle texture seams where vertices were split
                    vector< unsigned int > &vertList =
                        triGroup->posIndexToVertices[verts[_indices[k + l]].daePosIndex];
                    for( unsigned int m = 0; m < vertList.size(); ++m )
                    {
                        if( vertList[m] != _indices[k + l] &&
                            verts[vertList[m]].storedNormal == verts[_indices[k + l]].storedNormal )
                        {
                            verts[vertList[m]].normal += normal;
                            verts[vertList[m]].tangent += uDir;
                            verts[vertList[m]].bitangent += vDir;
                        }
                    }
                }
            }
        }
    }

    // Normalize tangent space basis
    unsigned int numInvalidBasis = 0;
    for( unsigned int i = 0; i < verts.size(); ++i )
    {
        // Check if tangent space basis is invalid
        if( verts[i].normal.length() == 0 || verts[i].tangent.length() == 0 || verts[i].bitangent.length() == 0 )
            ++numInvalidBasis;
        
        // Gram–Schmidt orthogonalization
        verts[i].normal.normalize();
        Vec3f &n = verts[i].normal;
        Vec3f &t = verts[i].tangent;
        verts[i].tangent = (t - n * n.dot( t )).normalized();
        
        // Calculate handedness (required to support mirroring) and final bitangent
        float handedness = n.cross( t ).dot( verts[i].bitangent ) < 0 ? -1.0f : 1.0f;
        verts[i].bitangent = n.cross( t ) * handedness;
    }

    if( numInvalidBasis > 0 )
    {
        log( "Warning: Geometry has zero-length basis vectors" );
        log( "   Maybe two faces point in opposite directions and share same vertices" );
    }
}

void Converter::processMeshes(bool optimize)
{
    // Note: At the moment the geometry for all nodes is copied and not referenced
    for (unsigned int i = 0; i < _meshes.size(); ++i)
    {
        // Find geometry/controller for node
        string id = _meshes[i]->daeInstance->url;

        DaeGeometry *geo = _daeDoc.libGeometries.findGeometry(id);
        ASSERT(geo != 0x0);

        unsigned int firstGeoVert = (unsigned int)_vertices.size();

        for (unsigned int j = 0; j < geo->triGroups.size(); ++j)
        {
            DaeTriGroup &iTriGroup = geo->triGroups[j];
            TriGroup* oTriGroup = new TriGroup();

            DaeMaterial *mat = _daeDoc.libMaterials.findMaterial(
                _meshes[i]->daeInstance->materialBindings[iTriGroup.matId]);
            if (mat != 0x0)
            {
                oTriGroup->matName = mat->name;
                mat->used = true;
            }
            else
                log("Warning: Material '" + oTriGroup->matName + "' not found");

            oTriGroup->first = (unsigned int)_indices.size();
            oTriGroup->count = (unsigned int)iTriGroup.indices.size();
            oTriGroup->vertRStart = (unsigned int)_vertices.size();

            // Add indices and vertices
            oTriGroup->numPosIndices = (unsigned int)iTriGroup.vSource->posSource->floatArray.size() /
                iTriGroup.vSource->posSource->paramsPerItem;
            oTriGroup->posIndexToVertices = new vector< unsigned int >[oTriGroup->numPosIndices];

            for (unsigned int k = 0; k < iTriGroup.indices.size(); ++k)
            {
                // Try to find vertex
                vector< unsigned int > &vertList = oTriGroup->posIndexToVertices[iTriGroup.indices[k].posIndex];
                bool found = false;
                unsigned int index = (unsigned int)_vertices.size();

                // Only check vertices that have the same Collada position index
                for (unsigned int l = 0; l < vertList.size(); ++l)
                {
                    Vertex &v = _vertices[vertList[l]];

                    if (v.storedPos == iTriGroup.getPos(iTriGroup.indices[k].posIndex) &&
                        v.storedNormal == iTriGroup.getNormal(iTriGroup.indices[k].normIndex) /*&&
                        v.texCoords[0] == iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[0], 0) &&
                        v.texCoords[1] == iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[1], 1) &&
                        v.texCoords[2] == iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[2], 2) &&
                        v.texCoords[3] == iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[3], 3)*/)

                    {
                        found = true;
                        index = vertList[l];
                        break;
                    }
                }

                if (found)
                {
                    _indices.push_back(index);
                }
                else
                {
                    Vertex v;

                    v.daePosIndex = iTriGroup.indices[k].posIndex;
                    int normIndex = iTriGroup.indices[k].normIndex;

                    // Position
                    v.storedPos = iTriGroup.getPos(v.daePosIndex);
                    v.pos = v.storedPos;
                    if (!_daeDoc.y_up)
                    {
                        swap(v.pos.y, v.pos.z);
                        v.pos.z *= -1;
                    }

                    // Texture coordinates
                    v.texCoords[0] = iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[0], 0);
                    v.texCoords[1] = iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[1], 1);
                    v.texCoords[2] = iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[2], 2);
                    v.texCoords[3] = iTriGroup.getTexCoords(iTriGroup.indices[k].texIndex[3], 3);

                    // Normal
                    v.storedNormal = iTriGroup.getNormal(normIndex);

                    _vertices.push_back(v);
                    _indices.push_back(index);

                    vertList.push_back((unsigned int)_vertices.size() - 1);
                }
            }

            oTriGroup->vertREnd = (unsigned int)_vertices.size() - 1;

            // Remove degenerated triangles
            unsigned int numDegTris = MeshOptimizer::removeDegeneratedTriangles(oTriGroup, _vertices, _indices);
            if (numDegTris > 0)
            {
                stringstream ss;
                ss << numDegTris;
                log("Removed " + ss.str() + " degenerated triangles from mesh " + _meshes[i]->daeNode->id);
            }

            _meshes[i]->triGroups.push_back(oTriGroup);
        }

        unsigned int numGeoVerts = (unsigned int)_vertices.size() - firstGeoVert;

    }

    // Calculate tangent space basis for base mesh
    calcTangentSpaceBasis( _vertices );

    // Optimization and clean up
    float optEffBefore = 0, optEffAfter = 0;
    unsigned int optNumCalls = 0;
    for( unsigned int i = 0; i < _meshes.size(); ++i )
    {
        for( unsigned int j = 0; j < _meshes[i]->triGroups.size(); ++j )
        {
            // Optimize order of indices for best vertex cache usage and remap vertices
            if( optimize )
            {
                map< unsigned int, unsigned int > vertMap;
                
                ++optNumCalls;
                optEffBefore += MeshOptimizer::calcCacheEfficiency( _meshes[i]->triGroups[j], _indices );
                MeshOptimizer::optimizeIndexOrder( _meshes[i]->triGroups[j], _vertices, _indices, vertMap );
                optEffAfter += MeshOptimizer::calcCacheEfficiency( _meshes[i]->triGroups[j], _indices );
            }
            
            // Clean up
            delete[] _meshes[i]->triGroups[j]->posIndexToVertices;
            _meshes[i]->triGroups[j]->posIndexToVertices = 0x0;
        }
    }

    // Output info about optimization
    /*if( optNumCalls > 0 )
    {
        stringstream ss;
        ss << fixed << setprecision( 3 );
        ss << "Optimized geometry for vertex cache: from ATVR " << optEffBefore / optNumCalls;
        ss << " to ATVR " << optEffAfter / optNumCalls;
        log( ss.str() );
    }*/
}


bool Converter::convertModel( bool optimize )
{
    if( _daeDoc.scene == 0x0 ) return true;		// Nothing to convert
    
    // Process all nodes
    for( unsigned int i = 0; i < _daeDoc.scene->nodes.size(); ++i )
    {
        _nodes.push_back( processNode( *_daeDoc.scene->nodes[i], 0x0, Matrix4f() ) );
    }

    // Process joints and meshes
    processMeshes( optimize );
    
    return true;
}


bool Converter::writeMesh( const string &assetPath, const string &assetName )
{
    string fileName = _outPath + assetPath + assetName + ".mesh";
    FILE *f = fopen( fileName.c_str(), "wb" );
    if( f == 0x0 )
    {	
        log( "Failed to write " + fileName + " file" );
        return false;
    }

    // Write header
    unsigned int version = 1;
    fwrite( "TEM", 3, 1, f );
    fwrite( &version, sizeof( int ), 1, f ); 
    
    unsigned int vertex_type = _daeDoc.libGeometries.getVertexType();
    unsigned int count = -1;
    fwrite(&vertex_type, sizeof(int), 1, f);

    // vertex type with different number of attributes
    // 0 == position, 
    // 1 == position and normal, 
    // 2 == position, normal and texture1
    switch (vertex_type) 
    {
    case 0:
        count = 1;
        break;
    case 1:
        count = 2;
        break;
    case 2:
        count = 3;
        break;
    default:
        break;
    }

    // Write vertex stream data
    fwrite( &count, sizeof( int ), 1, f );
    int vert_count = (unsigned int)_vertices.size();
    fwrite( &vert_count, sizeof( int ), 1, f );

    for( unsigned int i = 0; i < count; ++i )
    {        
        short sh;
        unsigned int streamElemSize;
        
        switch( i )
        {
        case 0:		// Position
            fwrite( &i, sizeof( int ), 1, f );
            streamElemSize = 3 * sizeof( float ); fwrite( &streamElemSize, sizeof( int ), 1, f );
            for( unsigned int j = 0; j < vert_count; ++j )
            {
                fwrite( &_vertices[j].pos.x, sizeof( float ), 1, f );
                fwrite( &_vertices[j].pos.y, sizeof( float ), 1, f );
                fwrite( &_vertices[j].pos.z, sizeof( float ), 1, f );
            }
            break;
        case 1:		// Normal
            fwrite( &i, sizeof( int ), 1, f );
            streamElemSize = 3 * sizeof( short ); fwrite( &streamElemSize, sizeof( int ), 1, f );
            for( unsigned int j = 0; j < vert_count; ++j )
            {
                sh = (short)(_vertices[j].normal.x * 32767); fwrite( &sh, sizeof( short ), 1, f );
                sh = (short)(_vertices[j].normal.y * 32767); fwrite( &sh, sizeof( short ), 1, f );
                sh = (short)(_vertices[j].normal.z * 32767); fwrite( &sh, sizeof( short ), 1, f );
            }
            break;
        case 2:		// Texture1
            fwrite(&i, sizeof(int), 1, f);
            streamElemSize = 2 * sizeof(float); fwrite(&streamElemSize, sizeof(int), 1, f);
            for (unsigned int j = 0; j < vert_count; ++j)
            {
                fwrite(&_vertices[j].texCoords[0].x, sizeof(float), 1, f);
                fwrite(&_vertices[j].texCoords[0].y, sizeof(float), 1, f);
               // fwrite(&_vertices[j].texCoords[0].z, sizeof(float), 1, f);
            }
            break;
        //case 2:		// Tangent
        //    fwrite( &i, sizeof( int ), 1, f );
        //    streamElemSize = 3 * sizeof( short ); fwrite( &streamElemSize, sizeof( int ), 1, f );
        //    for( unsigned int j = 0; j < vert_count; ++j )
        //    {
        //        sh = (short)(_vertices[j].tangent.x * 32767); fwrite( &sh, sizeof( short ), 1, f );
        //        sh = (short)(_vertices[j].tangent.y * 32767); fwrite( &sh, sizeof( short ), 1, f );
        //        sh = (short)(_vertices[j].tangent.z * 32767); fwrite( &sh, sizeof( short ), 1, f );
        //    }
        //    break;
        //case 3:		// Bitangent
        //    fwrite( &i, sizeof( int ), 1, f );
        //    streamElemSize = 3 * sizeof( short ); fwrite( &streamElemSize, sizeof( int ), 1, f );
        //    for( unsigned int j = 0; j < vert_count; ++j )
        //    {
        //        sh = (short)(_vertices[j].bitangent.x * 32767); fwrite( &sh, sizeof( short ), 1, f );
        //        sh = (short)(_vertices[j].bitangent.y * 32767); fwrite( &sh, sizeof( short ), 1, f );
        //        sh = (short)(_vertices[j].bitangent.z * 32767); fwrite( &sh, sizeof( short ), 1, f );
        //    }
        //    break;
        }
    }

    // Write triangle indices
    int idx_count = _indices.size();
    fwrite( &idx_count, sizeof( int ), 1, f );

    for( int i = 0; i < _indices.size(); ++i )
    {
        fwrite( &_indices[i], sizeof( int ), 1, f );
    }
    
    fclose( f );

    return true;
}


void Converter::writeSGNode( const string &assetPath, const string &modelName, SceneNode *node, unsigned int depth, ofstream &outf )
{
    Vec3f trans, rot, scale;
    node->matRel.decompose( trans, rot, scale );
    rot.x = radToDeg( rot.x );
    rot.y = radToDeg( rot.y );
    rot.z = radToDeg( rot.z );

    // Write mesh
    Mesh *mesh = (Mesh *)node;

    // Write triangle groups as submeshes of first triangle group
    for (unsigned int i = 0; i < mesh->triGroups.size(); ++i)
    {
        for (unsigned int j = 0; j < depth + 1; ++j) outf << "\t";
        if (i > 0) outf << "\t";
        outf << "<Mesh ";
        outf << "name=\"" << (i > 0 ? "#" : "") << mesh->name << "\" ";
        outf << "material=\"";
        outf << assetPath + modelName + mesh->triGroups[i]->matName + ".material.xml\" ";

        if (i == 0)
        {
            if (trans != Vec3f(0, 0, 0))
                outf << "tx=\"" << trans.x << "\" ty=\"" << trans.y << "\" tz=\"" << trans.z << "\" ";
            if (rot != Vec3f(0, 0, 0))
                outf << "rx=\"" << rot.x << "\" ry=\"" << rot.y << "\" rz=\"" << rot.z << "\" ";
            if (scale != Vec3f(1, 1, 1))
                outf << "sx=\"" << scale.x << "\" sy=\"" << scale.y << "\" sz=\"" << scale.z << "\" ";
        }

        outf << "batchStart=\"";
        outf << mesh->triGroups[i]->first;
        outf << "\" batchCount=\"";
        outf << mesh->triGroups[i]->count;
        outf << "\" vertRStart=\"";
        outf << mesh->triGroups[i]->vertRStart;
        outf << "\" vertREnd=\"";
        outf << mesh->triGroups[i]->vertREnd;
        outf << "\"";

        if (i == 0 && mesh->triGroups.size() > 1) outf << ">\n";
        if (i > 0) outf << " />\n";
    }

    if( node->children.size() == 0 )
    {
        if(((Mesh *)node)->triGroups.size() > 1 )
        {
            for( unsigned int j = 0; j < depth + 1; ++j ) outf << "\t";
            outf << "</Mesh>\n";
        }
        else
        {
            outf << " />\n";
        }
    }
    else
    {
        outf << ">\n";
        for( unsigned int j = 0; j < node->children.size(); ++j )
            writeSGNode( assetPath, modelName, node->children[j], depth + 1, outf );

        // Closing tag
        for( unsigned int j = 0; j < depth + 1; ++j ) outf << "\t";
        outf << "</Mesh>\n";
    }
}


bool Converter::writeSceneGraph( const string &assetPath, const string &assetName, const string &modelName )
{
    ofstream outf;
    outf.open( (_outPath + assetPath + assetName + ".scene.xml").c_str(), ios::out );
    if( !outf.good() )
    {
        log( "Failed to write " + _outPath + assetPath + assetName + ".scene file" );
        return false;
    }
    
    outf << "<Model name=\"" << assetName << "\" geometry=\"" << assetPath << assetName << ".mesh\"";

    outf << "\n";
    
    // Meshes
    for( unsigned int i = 0; i < _meshes.size(); ++i )
    {
        if( _meshes[i]->parent == 0x0 ) writeSGNode( assetPath, modelName, _meshes[i], 0, outf );
    }

    outf << "</Model>\n";

    outf.close();
    
    return true;
}


bool Converter::writeModel( const std::string &assetPath, const std::string &assetName, const std::string &modelName )
{
    bool result = true;
    
    if( !writeMesh( assetPath, assetName ) ) result = false;
    if( !writeSceneGraph( assetPath, assetName, modelName ) ) result = false;

    return result;
}


/**
 * Copyright (c) 2014 Xavier Gouchet
 *
 * This file is licensed under The MIT License (MIT).
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Shader.h"
#include <GLES2/gl2.h>

#define     VTX_MASK_POSITION   0X01
#define     VTX_MASK_NORMAL     0X02
#define     VTX_MASK_TEXCOORDS  0X04
#define     VTX_MASK_TANGENT    0X08
#define     VTX_MASK_BINORM     0X10

/**
 * The Geometry class holds a vertex buffer 
 */
class Geometry {

public:

    /** Constructor */
    Geometry();

    /** Destructor */
    ~Geometry();

    /**
     * Initializes the geometry with the given vertices array. 
     * 
     * The array contains each vertex information successively (meaning that all info for a single 
     * vertex is consecutive). Each vertex can have a position, a normal, tangent and binormal vector, 
     * a texture coordinate. 
     * 
     * If a field is not used at all in the geometry (for instance, there is no normal information
     * throughout the geometry), then you can ommit the data, and set the vtxMask accordingly.
     * 
     * The order in which the vertex attributes are set should be respected : Position (3 floats), 
     * Normal (3 floats), Tangent (3 floats), Binormal (3 float), Texture Coordinates (2 floats)
     * 
     * The vtxMask value can be a composition of VTX_MASK_POSITION, VTX_MASK_NORMAL, 
     * VTX_MASK_TANGENT, VTX_MASK_BINORM, VTX_MASK_TEXCOORDS
     */
    bool initVertices(GLfloat *vertices, int vertices_count, unsigned short vtxMask);

    /**
     * Initializes the geometry with the given indices arrays. 
     * 
     * If the indices array is NULL or the index count is 0, then the natural vertex order will be used. 
     * 
     * The drawing mode can be GL_POINTS, GL_LINES, GL_LINE_STRIP, 
     * GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN).
     */
     void initIndices(GLubyte *indices, int idxCount, GLenum mode);


    /**
     * Draws the geometry using the given shader. Any attribute or parameter not set by the geometry
     * should already be set on the Shader
     */
    void drawGeometry(Shader *shader);

private:

    /** the vertex buffer */
    GLuint mVtxBufferHandle;
    /** the number of vertex in the buffer */
    int mVtxCount;
    /** the offset between two consecutive vertices */
    int mVtxStride;
    /** the offset for each data */
    int mVtxPositionOffset;
    int mVtxNormalOffset;
    int mVtxTangentOffset;
    int mVtxBinormalOffset;
    int mVtxTexCoordsOffset;
    
    /** the mask of what data is available for each vertex */
    unsigned short mVtxMask;

    /** the index buffer */
    GLubyte *mIdxBuffer;
    int mIdxCount;

    /** the basic array mode */
    GLenum mArrayMode;

};

#endif

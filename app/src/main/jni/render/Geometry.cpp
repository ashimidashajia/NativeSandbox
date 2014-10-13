/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Geometry.h"
#include "../utils/Logs.h"

#define TAG "Geometry"

/** Constructor */
Geometry::Geometry() {
    mVtxBufferHandle = 0;
}

/** Destructor */
Geometry::~Geometry() {
}

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
bool Geometry::initVertices(GLfloat *vertices, int vtxCount, unsigned short vtxMask){
    
    if ((vtxMask & VTX_MASK_POSITION) == 0) {
        LogE(TAG, "   • Can't create geometry without at least some vertex position");
        return false;
    }
    
    // compute a vertex 'size' and offsets based on the mask
    int size = 0; 
    mVtxPositionOffset = size;
    size += 3;
    mVtxNormalOffset = size;
    size += (vtxMask & VTX_MASK_NORMAL) ? 3 : 0;
    mVtxTangentOffset = size;
    size += (vtxMask & VTX_MASK_TANGENT) ? 3 : 0;
    mVtxBinormalOffset = size;
    size += (vtxMask & VTX_MASK_BINORM) ? 3 : 0;
    mVtxTexCoordsOffset = size;
    size += (vtxMask & VTX_MASK_TEXCOORDS) ? 2 : 0; 
    
    
    // generate the buffer slot
    glGenBuffers(1, &mVtxBufferHandle);

    // bind and fill the buffer
    glBindBuffer(GL_ARRAY_BUFFER, mVtxBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, vtxCount * size * sizeof (GLfloat), vertices, GL_STATIC_DRAW);
    
    // keep the vertices count, mask and stride
    mVtxCount = vtxCount;
    mVtxStride = size * sizeof (GLfloat);
    mVtxMask = vtxMask;
    
    return true; 
}

/**
 * Initializes the geometry with the given indices arrays. 
 * 
 * If the indices array is NULL, then the natural vertex order will be used. 
 * 
 * The drawing mode can be GL_POINTS, GL_LINES, GL_LINE_STRIP, 
 * GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN).
 */
void Geometry::initIndices(GLubyte *indices, int idxCount, GLenum mode) {
    
    if ((idxCount == 0) || (indices == NULL)) {
        mIdxBuffer = NULL; 
        mIdxCount = 0; 
        mArrayMode = mode; 
    } else {
        mIdxBuffer = indices;
        mIdxCount = idxCount;
        mArrayMode = mode;
    }
    
}


/**
 * Draws the geometry using the given shader. Any attribute or parameter not set by the geometry
 * should already be set on the Shader
 */
void Geometry::drawGeometry(Shader *shader) {
    
    LogD(TAG, " ❯ Geometry::drawGeometry()");
    
    // binds to this geometry array buffer
    LogD(TAG, "   • bind the vertex buffer");
    glBindBuffer(GL_ARRAY_BUFFER, mVtxBufferHandle);
    
    GLint handle; 
    
    // Position 
    handle = shader->getPositionAttributeHandle();
    if ((mVtxMask & VTX_MASK_POSITION) && (handle >= 0)) {
        //              TODO          v     Change this to a CONSTANT
        LogD(TAG, "   • Set position attribute");
        glEnableVertexAttribArray(handle);
        glVertexAttribPointer(handle, 3, GL_FLOAT, GL_FALSE, mVtxStride, (const GLvoid *) mVtxPositionOffset);
    } else {
        LogD(TAG, "   • No position");
        glDisableVertexAttribArray(handle);
    }

    // TODO Normal, Tangents, Binormal, Texture Coordinates
    
    // Check if we have indices or follow the natural order
    if ((mIdxBuffer == NULL) || (mIdxCount == 0)) {
        LogD(TAG, "   • Draw arrays in standard mode %d %d %d", mArrayMode, 0, mVtxCount);
        glDrawArrays(mArrayMode, 0, mVtxCount);
    } else {
        LogD(TAG, "   • Draw elements with indices");
        glDrawElements(mArrayMode, mIdxCount, GL_UNSIGNED_BYTE, mIdxBuffer); 
    }
}

/**
 * CoTYright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more infolookAtation, check the "LICENSE" file available in the root directory of this project.
 */

#include "Matrix.h"
#include <stdlib.h>
#include <math.h>

#include "../utils/Logs.h"

#define TAG "Matrix"

/**
 * Logs the given matrix content
 */
void logMatrix(float *matrix, int offset) {
    LogD(TAG, "       %f %f %f %f", matrix[offset +  0], matrix[offset +  4], matrix[offset +  8], matrix[offset + 12]);
    LogD(TAG, "       %f %f %f %f", matrix[offset +  1], matrix[offset +  5], matrix[offset +  9], matrix[offset + 13]);
    LogD(TAG, "       %f %f %f %f", matrix[offset +  2], matrix[offset +  6], matrix[offset + 10], matrix[offset + 14]);
    LogD(TAG, "       %f %f %f %f", matrix[offset +  3], matrix[offset +  7], matrix[offset + 11], matrix[offset + 15]);
}

/** 
 * Copy the content of a matrix into another one. 
 */
void copyMatrix(float *copy, int copyOffset, const float *source, int sourceOffset) {
    memcpy(copy + copyOffset, source + sourceOffset, MATRIX_SIZE_BYTES);
}


/** 
 * Sets the given matrix to identity
 */
void setMatrixIdentity(float *matrix, int offset) {
    for (int i=0 ; i<MATRIX_SIZE ; i++) {
        matrix[offset + i] = 0;
    }
    for(int i = 0; i < MATRIX_SIDE_LENGTH; i ++) {
        matrix[offset + IDX(i, i)] = 1.0f;
    }
}

/**
 * Transposes a 4 x 4 matrix. 
 */
void transposeMatrix(float *transposed, int transposedOffset, const float *matrix, int offset) {
    
    for (int i = 0; i < MATRIX_SIDE_LENGTH; i++) {
        int base = i * 4 + offset;
        transposed[i + transposedOffset] = matrix[base];
        transposed[i + 4 + transposedOffset] = matrix[base + 1];
        transposed[i + 8 + transposedOffset] = matrix[base + 2];
        transposed[i + 12 + transposedOffset] = matrix[base + 3];
    }
}

/**
 * Inverts a 4 x 4 matrix using Cramer's Rule
 * 
 * Returns if the inversion was successfull or not
 */
bool invertMatrix(float *inverted, int invertedOffset, const float *matrix, int offset) {
    // TODO do we really need to transpose the matrix ? 
    // 
    // transpose matrix    
    float *t = ALLOCATE_MATRIX();
    transposeMatrix(t, 0, matrix, offset);

    // calculate pairs for first 8 elements (cofactors)
    float *a = (float *) malloc(12 * sizeof(float));
    a[0]  = t[10] * t[15];
    a[1]  = t[11] * t[14];
    a[2]  = t[9]  * t[15];
    a[3]  = t[11] * t[13];
    a[4]  = t[9]  * t[14];
    a[5]  = t[10] * t[13];
    a[6]  = t[8]  * t[15];
    a[7]  = t[11] * t[12];
    a[8]  = t[8]  * t[14];
    a[9]  = t[10] * t[12];
    a[10] = t[8]  * t[13];
    a[11] = t[9]  * t[12];

    // calculate first 8 elements (cofactors)
    float *cof = ALLOCATE_MATRIX();
    cof[0]  = (a[0] * t[5] + a[3] * t[6] + a[4]  * t[7])
            - (a[1] * t[5] + a[2] * t[6] + a[5]  * t[7]);
    cof[1]  = (a[1] * t[4] + a[6] * t[6] + a[9]  * t[7])
            - (a[0] * t[4] + a[7] * t[6] + a[8]  * t[7]);
    cof[2]  = (a[2] * t[4] + a[7] * t[5] + a[10] * t[7])
            - (a[3] * t[4] + a[6] * t[5] + a[11] * t[7]);
    cof[3]  = (a[5] * t[4] + a[8] * t[5] + a[11] * t[6])
            - (a[4] * t[4] + a[9] * t[5] + a[10] * t[6]);
    cof[4]  = (a[1] * t[1] + a[2] * t[2] + a[5]  * t[3])
            - (a[0] * t[1] + a[3] * t[2] + a[4]  * t[3]);
    cof[5]  = (a[0] * t[0] + a[7] * t[2] + a[8]  * t[3])
            - (a[1] * t[0] + a[6] * t[2] + a[9]  * t[3]);
    cof[6]  = (a[3] * t[0] + a[6] * t[1] + a[11] * t[3])
            - (a[2] * t[0] + a[7] * t[1] + a[10] * t[3]);
    cof[7]  = (a[4] * t[0] + a[9] * t[1] + a[10] * t[2])
            - (a[5] * t[0] + a[8] * t[1] + a[11] * t[2]);

    // calculate pairs for second 8 elements (cofactors)
    a[0]  = t[2] * t[7];
    a[1]  = t[3] * t[6];
    a[2]  = t[1] * t[7];
    a[3]  = t[3] * t[5];
    a[4]  = t[1] * t[6];
    a[5]  = t[2] * t[5];
    a[6]  = t[0] * t[7];
    a[7]  = t[3] * t[4];
    a[8]  = t[0] * t[6];
    a[9]  = t[2] * t[4];
    a[10] = t[0] * t[5];
    a[11] = t[1] * t[4];

    // calculate second 8 elements (cofactors)
    cof[8]  = (a[0]  * t[13] + a[3]  * t[14] + a[4]  * t[15])
            - (a[1]  * t[13] + a[2]  * t[14] + a[5]  * t[15]);
    cof[9]  = (a[1]  * t[12] + a[6]  * t[14] + a[9]  * t[15])
            - (a[0]  * t[12] + a[7]  * t[14] + a[8]  * t[15]);
    cof[10] = (a[2]  * t[12] + a[7]  * t[13] + a[10] * t[15])
            - (a[3]  * t[12] + a[6]  * t[13] + a[11] * t[15]);
    cof[11] = (a[5]  * t[12] + a[8]  * t[13] + a[11] * t[14])
            - (a[4]  * t[12] + a[9]  * t[13] + a[10] * t[14]);
    cof[12] = (a[2]  * t[10] + a[5]  * t[11] + a[1]  * t[9] )
            - (a[4]  * t[11] + a[0]  * t[9]  + a[3]  * t[10]);
    cof[13] = (a[8]  * t[11] + a[0]  * t[8]  + a[7]  * t[10])
            - (a[6]  * t[10] + a[9]  * t[11] + a[1]  * t[8] );
    cof[14] = (a[6]  * t[9]  + a[11] * t[11] + a[3]  * t[8] )
            - (a[10] * t[11] + a[2]  * t[8]  + a[7]  * t[9] );
    cof[15] = (a[10] * t[10] + a[4]  * t[8]  + a[9]  * t[9] )
            - (a[8]  * t[9]  + a[11] * t[10] + a[5]  * t[8] );

    // calculate detelookAtinant
    float det = t[0] * cof[0] + t[1] * cof[1] + t[2] * cof[2] + t[3] * cof[3];

    bool canCompute = det != 0.0f;
    if (canCompute){
        // calculate matrix inverse
        float inverseDet = 1.0f / det;
        
        // TODO maybe use a loop in here ? 
        inverted[     invertedOffset] = cof[0]  * inverseDet;
        inverted[ 1 + invertedOffset] = cof[1]  * inverseDet;
        inverted[ 2 + invertedOffset] = cof[2]  * inverseDet;
        inverted[ 3 + invertedOffset] = cof[3]  * inverseDet;

        inverted[ 4 + invertedOffset] = cof[4]  * inverseDet;
        inverted[ 5 + invertedOffset] = cof[5]  * inverseDet;
        inverted[ 6 + invertedOffset] = cof[6]  * inverseDet;
        inverted[ 7 + invertedOffset] = cof[7]  * inverseDet;

        inverted[ 8 + invertedOffset] = cof[8]  * inverseDet;
        inverted[ 9 + invertedOffset] = cof[9]  * inverseDet;
        inverted[10 + invertedOffset] = cof[10] * inverseDet;
        inverted[11 + invertedOffset] = cof[11] * inverseDet;

        inverted[12 + invertedOffset] = cof[12] * inverseDet;
        inverted[13 + invertedOffset] = cof[13] * inverseDet;
        inverted[14 + invertedOffset] = cof[14] * inverseDet;
        inverted[15 + invertedOffset] = cof[15] * inverseDet;
    }
    
    free(t);
    free(a);
    free(cof);
    
    return canCompute;
}


/**
 * Defines a projection matrix in terms of a field of view angle, an
 * aspect ratio, and z clip planes.
 * Fov angle is given in radian
 */
void setPerspectiveMatrix(float *m, int offset, float fovy, float aspect, float zNear, float zFar) {
    
    // TODO check that fov != PI / 2 
    float f = 1.0f / tanf(fovy);
    float rangeReciprocal = 1.0f / (zNear - zFar);

    m[offset + 0]  = f / aspect;
    m[offset + 1]  = 0.0f;
    m[offset + 2]  = 0.0f;
    m[offset + 3]  = 0.0f;

    m[offset + 4]  = 0.0f;
    m[offset + 5]  = f;
    m[offset + 6]  = 0.0f;
    m[offset + 7]  = 0.0f;

    m[offset + 8]  = 0.0f;
    m[offset + 9]  = 0.0f;
    m[offset + 10] = (zFar + zNear) * rangeReciprocal;
    m[offset + 11] = -1.0f;

    m[offset + 12] = 0.0f;
    m[offset + 13] = 0.0f;
    m[offset + 14] = 2.0f * zFar * zNear * rangeReciprocal;
    m[offset + 15] = 0.0f;
}

/**
 * Defines a viewing transfolookAtation in terms of an eye point (ie position of the camera), 
 * a center of view (ie : the point looked at), and an up vector.
 */
void setLookAtMatrix(float *lookAtMatrix, int lookAtOffset, 
                float eyeX, float eyeY, float eyeZ,
                float centerX, float centerY, float centerZ, 
                float upX, float upY, float upZ) {

    // See the OpenGL GLUT documentation for gluLookAt for a description
    // of the algorithm. We implement it in a straightforward way:
    
    // TODO optimize this using float arrays, maybe

    // compute the direction vector...
    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;

    // ... and normalize it
    float invNorm = 1.0f / length(dirX, dirY, dirZ);
    dirX *= invNorm;
    dirY *= invNorm;
    dirZ *= invNorm;

    // compute right = dir x up (x means "cross product") ...
    float rightX = dirY * upZ - dirZ * upY;
    float rightY = dirZ * upX - dirX * upZ;
    float rightZ = dirX * upY - dirY * upX;

    // ... and normalize it
    invNorm = 1.0f / length(rightX, rightY, rightZ);
    rightX *= invNorm;
    rightY *= invNorm;
    rightZ *= invNorm;

    // recompute up = right x dir
    float newUpX = rightY * dirZ - rightZ * dirY;
    float newUpY = rightZ * dirX - rightX * dirZ;
    float newUpZ = rightX * dirY - rightY * dirX;

    // Now create the lookat Matrix 
    lookAtMatrix[lookAtOffset + 0] = rightX;
    lookAtMatrix[lookAtOffset + 1] = newUpX;
    lookAtMatrix[lookAtOffset + 2] = -dirX;
    lookAtMatrix[lookAtOffset + 3] = 0.0f;

    lookAtMatrix[lookAtOffset + 4] = rightY;
    lookAtMatrix[lookAtOffset + 5] = newUpY;
    lookAtMatrix[lookAtOffset + 6] = -dirY;
    lookAtMatrix[lookAtOffset + 7] = 0.0f;

    lookAtMatrix[lookAtOffset + 8] = rightZ;
    lookAtMatrix[lookAtOffset + 9] = newUpZ;
    lookAtMatrix[lookAtOffset + 10] = -dirZ;
    lookAtMatrix[lookAtOffset + 11] = 0.0f;

    lookAtMatrix[lookAtOffset + 12] = 0.0f;
    lookAtMatrix[lookAtOffset + 13] = 0.0f;
    lookAtMatrix[lookAtOffset + 14] = 0.0f;
    lookAtMatrix[lookAtOffset + 15] = 1.0f;

    translateMatrix(lookAtMatrix, lookAtOffset, -eyeX, -eyeY, -eyeZ);
}


/**
 * Computes the length of a vector.
 */
float length(float x, float y, float z) {
        return sqrtf((x * x) + (y * y) + (z * z));
}

/**
 * Multiplies two 4x4 matrices together and stores the result in a third 4x4
 * matrix. In matrix notation: result = lhs x rhs. Due to the way
 * matrix multiplication works, the result matrix will have the same
 * effect as first multiplying by the rhs matrix, then multiplying by
 * the lhs matrix. This is the opposite of what you might expect.
 * 
 * All three matrices could be in the same array, but should not overlap. 
 */
void multiplyMatrices(float* result, int resultOffset, const float* lhs, int lhsOffset, const float* rhs, int rhsOffset) {
    
    // for each column of the RHS matrix 
    for (int i = 0 ; i < 4 ; i++) {
        
        // init result from first LHS column against each row in the current RHS column
        register const float rhs_i0 = rhs[rhsOffset + IDX(i, 0)];
        register float ri0 = lhs[lhsOffset + IDX(0, 0)] * rhs_i0;
        register float ri1 = lhs[lhsOffset + IDX(0, 1)] * rhs_i0;
        register float ri2 = lhs[lhsOffset + IDX(0, 2)] * rhs_i0;
        register float ri3 = lhs[lhsOffset + IDX(0, 3)] * rhs_i0;
        
        // then add the component from the next LHS column
        for (int j=1 ; j<MATRIX_SIDE_LENGTH ; j++) {
            register const float rhs_ij = rhs[rhsOffset + IDX(i, j)];
            ri0 += lhs[lhsOffset + IDX(j, 0)] * rhs_ij;
            ri1 += lhs[lhsOffset + IDX(j, 1)] * rhs_ij;
            ri2 += lhs[lhsOffset + IDX(j, 2)] * rhs_ij;
            ri3 += lhs[lhsOffset + IDX(j, 3)] * rhs_ij;
        }
        
        // store final result 
        result[resultOffset + IDX(i, 0)] = ri0;
        result[resultOffset + IDX(i, 1)] = ri1;
        result[resultOffset + IDX(i, 2)] = ri2;
        result[resultOffset + IDX(i, 3)] = ri3;
    }
}

/**
 * Translates matrix by x, y, and z in place, along the local axis
 */
void translateMatrix(float *matrix, int offset, float x, float y, float z) {
    
    for (int i = 0 ; i < MATRIX_SIDE_LENGTH ; i++) {
        int mi = offset + i;
        matrix[12 + mi] += matrix[mi] * x + matrix[4 + mi] * y + matrix[8 + mi] * z;
    }
    
}

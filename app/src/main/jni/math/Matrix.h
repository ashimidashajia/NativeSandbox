/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

#define MATRIX_SIDE_LENGTH       4
#define IDENTITY_OFFSET          5
#define MATRIX_SIZE             16
#define MATRIX_SIZE_BYTES       (MATRIX_SIZE * sizeof(float))

// helper to get index in matrix 
#define IDX(_i, _j)     ((_j) + (MATRIX_SIDE_LENGTH * (_i)))

#define ALLOCATE_MATRIX()   ((float *) malloc(MATRIX_SIZE_BYTES))

/**
 * Matrix math utilities. These methods operate on OpenGL ES format
 * matrices and vectors stored in float arrays.
 *
 * Matrices are 4 x 4 column-vector matrices stored in column-major
 * order:
 *
 *  matrix[offset +  0] matrix[offset +  4] matrix[offset +  8] matrix[offset + 12]
 *  matrix[offset +  1] matrix[offset +  5] matrix[offset +  9] matrix[offset + 13]
 *  matrix[offset +  2] matrix[offset +  6] matrix[offset + 10] matrix[offset + 14]
 *  matrix[offset +  3] matrix[offset +  7] matrix[offset + 11] matrix[offset + 15]
 * 
 * 3D informations are available as : 
 *  Right X     Right Y     Right Z       Pos X
 *     Up X        Up Y        Up Z       Pos Y
 *    Dir X       Dir Y       Dir Z       Pos Z
 *   Skew X      Skew Y      Skew Z
 * 
 * Vectors are 4 x 1 column vectors stored in order:

 * v[offset + 0]
 * v[offset + 1]
 * v[offset + 2]
 * v[offset + 3]
 */
 
/**
 * Logs the given matrix content
 */
void logMatrix(float *matrix, int offset);

/** 
 * Copy the content of a matrix into another one. 
 */
void copyMatrix(float *copy, int copyOffset, const float *source, int sourceOffset);

/** 
 * Sets the given matrix to identity
 */
void setMatrixIdentity(float *matrix, int offset);

/**
 * Transposes a 4 x 4 matrix. 
 */
void transposeMatrix(float *transposed, int transposedOffset, const float *matrix, int offset);

/**
 * Inverts a 4 x 4 matrix using Cramer's Rule
 * 
 * Returns if the inversion was successfull or not
 */
bool invertMatrix(float *inverted, int invertedOffset, const float *matrix, int offset);


/**
 * Multiplies two 4x4 matrices together and stores the result in a third 4x4
 * matrix. In matrix notation: result = lhs x rhs. Due to the way
 * matrix multiplication works, the result matrix will have the same
 * effect as first multiplying by the rhs matrix, then multiplying by
 * the lhs matrix. This is the opposite of what you might expect.
 * 
 * All three matrices could be in the same array, but should not overlap. 
 */
void multiplyMatrices(float* result, int resultOffset, const float* lhs, int lhsOffset, const float* rhs, int rhsOffset);

/**
 * Translates matrix by x, y, and z in place. 
 */
void translateMatrix(float *matrix, int offset, float x, float y, float z) ;


/**
 * Defines a projection matrix in terms of a field of view angle, an
 * aspect ratio, and z clip planes.
 * Fov angle is given in radian
 */
void setPerspectiveMatrix(float *m, int offset, float fovy, float aspect, float zNear, float zFar);

/**
 * Defines a viewing transfolookAtation in terms of an eye point (ie position of the camera), 
 * a center of view (ie : the point looked at), and an up vector.
 */
void setLookAtMatrix(float *lookAtMatrix, int lookAtOffset, 
                float eyeX, float eyeY, float eyeZ,
                float centerX, float centerY, float centerZ, 
                float upX, float upY, float upZ) ;

/**
 * Computes the length of a vector.
 */
inline float length(float x, float y, float z);


/**
 * Translates matrix by x, y, and z in place. 
 */
void translateMatrix(float *matrix, int offset, float x, float y, float z);

#endif


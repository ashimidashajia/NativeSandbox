/**
 * CoTYright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Matrix.h"
#include <stdlib.h>
#include <math.h>

#include "../utils/Logs.h"

#define TAG "Matrix"

/** Constructor (identity) */
Matrix::Matrix(){
    m_data = (float *) malloc(MATRIX_SIZE * sizeof(float));
    set_identity();
}

/** Destructor */
Matrix::~Matrix(){
    free(m_data);
}

void Matrix::log(){
    LogD(TAG, "   • Matrix  ");
    LogD(TAG, "       %f %f %f %f", m_data[RX], m_data[UX], m_data[DX], m_data[KX]);
    LogD(TAG, "       %f %f %f %f", m_data[RY], m_data[UY], m_data[DY], m_data[KY]);
    LogD(TAG, "       %f %f %f %f", m_data[RZ], m_data[UZ], m_data[DZ], m_data[KZ]);
    LogD(TAG, "       %f %f %f %f", m_data[TX], m_data[TY], m_data[TZ], m_data[KW]);
}

/** 
 * Returns a pointer to the data under this matrix 
 */
float *Matrix::getData() {
    return m_data;
}

float Matrix::get_determinant(){
    return determinant(m_data); 
}

/** Sets this matrix to identity */
void Matrix::set_identity() {
    set_identity(m_data);
}

/** Sets this matrix to identity */
void Matrix::set(Matrix *matrix) {
    memcpy(m_data, matrix->m_data, MATRIX_SIZE * sizeof(float));
}

// Relative transforms
void Matrix::translate(float x, float y, float z) {
    m_data[TX] += x;
    m_data[TY] += y;
    m_data[TZ] += z;
}

void Matrix::rotate(float x, float y, float z, float angle) {
    float *tmp = (float *) malloc(MATRIX_SIZE * sizeof(float));
    float *rot = (float *) malloc(MATRIX_SIZE * sizeof(float));
    rotation_matrix(rot, x, y, z, angle);
    multiply(m_data, rot, tmp); 
    
    memcpy(m_data, tmp, MATRIX_SIZE * sizeof(float));
    free(tmp);
    free(rot);
}

void Matrix::scale(float x, float y, float z) {
    // TODO 
}

// Absolute transforms
void Matrix::setPosition(float x, float y, float z) {
    m_data[TX] = x;
    m_data[TY] = y;
    m_data[TZ] = z;
}

/**
 * Sets the given matrix as a projection matrix 
 *  out : the matrix 
 *  fov : the field of view  (in radians)
 *  aspect_ratio : width / height
 *  near : the near plane
 *  far : the far plane
 */
void Matrix::setProjectionMatrix(float fov, float aspect_ratio, float near, float far) {
    
    // avoid divide by zero errors 
    if ((fov < 0) || (aspect_ratio ==0)){
        return;
    }
    
    // compute needed values 
    float invert_depth = far - near;
    
    // set all values 
    set_identity(m_data);
    m_data[UY] = 1.0f / tanf(0.5f * fov);
    m_data[RX] = m_data[UY] / aspect_ratio;
    m_data[DZ] = far * invert_depth;
    m_data[TZ] = -far * near * invert_depth;
    m_data[KZ] = 1.0f;
    m_data[KW] = 0.0f;
}

/**
 * Inverse a Matrix. 
 * 
 * Let's assume that our matrix is a standard, simple T * R * S matrix
 * (no shear, no complicated stuff...). 
 * 
 * Then the invert M is S⁻¹ * R⁻¹ * T⁻¹. 
 * 
 */
void Matrix::inverse() {
    float *rot, *scale, *trans; 
    scale = (float *) malloc(MATRIX_SIZE * sizeof(float));
    rot   = (float *) malloc(MATRIX_SIZE * sizeof(float));    
    trans = (float *) malloc(MATRIX_SIZE * sizeof(float));
    
    // extract scale 
    set_identity(scale);
    scale[RX] = (m_data[RX] * m_data[RX]) + 
                (m_data[RY] * m_data[RY]) +
                (m_data[RZ] * m_data[RZ]);
    scale[RX] = sqrt(scale[RX]);
    scale[UY] = (m_data[UX] * m_data[UX]) + 
                (m_data[UY] * m_data[UY]) +
                (m_data[UZ] * m_data[UZ]);
    scale[UY] = sqrt(scale[UY]);
    scale[DZ] = (m_data[DX] * m_data[DX]) + 
                (m_data[DY] * m_data[DY]) +
                (m_data[DZ] * m_data[DZ]);
    scale[DZ] = sqrt(scale[DZ]);
    
    // extract rotation (and inverse it at the same time)
    set_identity(rot);
    rot[RX] = m_data[RX] / scale[RX];
    rot[UX] = m_data[RY] / scale[RX];
    rot[DX] = m_data[RZ] / scale[RX];
    rot[RY] = m_data[UX] / scale[UY];
    rot[UY] = m_data[UY] / scale[UY];
    rot[DY] = m_data[UZ] / scale[UY];
    rot[RZ] = m_data[DX] / scale[DZ];
    rot[UZ] = m_data[DY] / scale[DZ];
    rot[DZ] = m_data[DZ] / scale[DZ];
    
    // extract translation (and inverse it at the same time)
    set_identity(trans);
    trans[TX] = m_data[TX];
    trans[TY] = m_data[TY];
    trans[TZ] = m_data[TZ];
    
    // inverse scale matrix
    scale[RX] = (1.0f / scale[RX]);
    scale[UY] = (1.0f / scale[UY]);
    scale[DZ] = (1.0f / scale[DZ]);
    
    // compute the inverse
    float *tmp = (float *) malloc(MATRIX_SIZE * sizeof(float));
    multiply(scale, rot, tmp);
    multiply(tmp, trans, m_data);
    
    // free everything
    free(scale);
    free(rot);
    free(trans);
    free(tmp);
}

void Matrix::preMultiply(Matrix *matrix) {

    float *tmp = (float *) malloc(MATRIX_SIZE * sizeof(float));
    multiply(m_data, matrix->m_data, tmp); 
    
    memcpy(m_data, tmp, MATRIX_SIZE * sizeof(float));
    free(tmp);
}

void Matrix::post_multiply(Matrix *matrix) {
    
    float *tmp = (float *) malloc(MATRIX_SIZE * sizeof(float));
    multiply(matrix->m_data, m_data, tmp); 
    
    memcpy(m_data, tmp, MATRIX_SIZE * sizeof(float));
    free(tmp);
}

/**
 * Utility to multiply two matrices : out = a * b
 */
void Matrix::multiply(Matrix *a, Matrix *b, Matrix *out){
    multiply(a->m_data, b->m_data, out->m_data);
}

/**
 * Utility used to create a rotation matrix stored in the out array, based on the 
 * input axis (x, y, z) and angle
 */
void Matrix::rotation_matrix(float *out, float x, float y, float z, float angle) {
    
    float c = cosf(angle);
    float s = sinf(angle);
    
    out[0] = (x * x * (1 - c)) + c; 
    out[1] = (x * y * (1 - c)) - (z * s); 
    out[2] = (x * z * (1 - c)) + (y * s); 
    out[3] = 0; 
    
    out[4] = (y * x * (1 - c)) + (z * s); 
    out[5] = (y * y * (1 - c)) + c; 
    out[6] = (y * z * (1 - c)) - (x * s); 
    out[7] = 0; 
    
    out[8] = (z * x * (1 - c)) - (y * s); 
    out[9] = (z * y * (1 - c)) + (x * s); 
    out[10] = (z * z * (1 - c)) + c; 
    out[11] = 0; 
    
    out[12] = 0; 
    out[13] = 0; 
    out[14] = 0; 
    out[15] = 1; 
    
}

/** 
 * Utility used to perform a multiplication from matrices float arrays
 */
void Matrix::multiply(float *a, float *b, float *out){
    
    out[0] = (a[0] * b[0]) + (a[1] * b[4]) + (a[2] * b[8]) + (a[3] * b[12]);
    out[1] = (a[0] * b[1]) + (a[1] * b[5]) + (a[2] * b[9]) + (a[3] * b[13]);
    out[2] = (a[0] * b[2]) + (a[1] * b[6]) + (a[2] * b[10]) + (a[3] * b[14]);
    out[3] = (a[0] * b[3]) + (a[1] * b[7]) + (a[2] * b[11]) + (a[3] * b[15]);
    
    out[4] = (a[4] * b[0]) + (a[5] * b[4]) + (a[6] * b[8]) + (a[7] * b[12]);
    out[5] = (a[4] * b[1]) + (a[5] * b[5]) + (a[6] * b[9]) + (a[7] * b[13]);
    out[6] = (a[4] * b[2]) + (a[5] * b[6]) + (a[6] * b[10]) + (a[7] * b[14]);
    out[7] = (a[4] * b[3]) + (a[5] * b[7]) + (a[6] * b[11]) + (a[7] * b[15]);
    
    out[8] = (a[8] * b[0]) + (a[9] * b[4]) + (a[10] * b[8]) + (a[11] * b[12]);
    out[9] = (a[8] * b[1]) + (a[9] * b[5]) + (a[10] * b[9]) + (a[11] * b[13]);
    out[10] = (a[8] * b[2]) + (a[9] * b[6]) + (a[10] * b[10]) + (a[11] * b[14]);
    out[11] = (a[8] * b[3]) + (a[9] * b[7]) + (a[10] * b[11]) + (a[11] * b[15]);
    
    out[12] = (a[12] * b[0]) + (a[13] * b[4]) + (a[14] * b[8]) + (a[15] * b[12]);
    out[13] = (a[12] * b[1]) + (a[13] * b[5]) + (a[14] * b[9]) + (a[15] * b[13]);
    out[14] = (a[12] * b[2]) + (a[13] * b[6]) + (a[14] * b[10]) + (a[15] * b[14]);
    out[15] = (a[12] * b[3]) + (a[13] * b[7]) + (a[14] * b[11]) + (a[15] * b[15]);
}

/**
 * Computes the determinant of a matrix (as float[16])
 */
float Matrix::determinant(float *matrix) {
}

void Matrix::set_identity(float *out){
    for (int i = 0; i < 16; ++i) {
        out[i] = ((i % IDENTITY_OFFSET) == 0) ? 1.0f : 0.0f;
    }
}

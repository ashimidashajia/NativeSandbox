/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

#define IDENTITY_OFFSET  5
#define MATRIX_SIZE     16

#define OFFSET_RIGHT    0
#define OFFSET_UP       4
#define OFFSET_DIR      8
#define OFFSET_POS     12

#define RX      0
#define RY      4
#define RZ      8
#define UX      1
#define UY      5
#define UZ      9
#define DX      2
#define DY      6
#define DZ     10
#define TX     12
#define TY     13
#define TZ     14
#define KX      3
#define KY      7
#define KZ     11
#define KW     15


/**
 * Describes a standard 3D transform Matrix 4x4, and everything to manipulate it
 */
class Matrix {

public:

    /** Constructor*/
    Matrix();

    /** Destructor */
    ~Matrix();
    
    /** 
     * Returns a pointer to the data under this matrix 
     */
    float *getData();
    
    void set(Matrix *matrix);
    void set_identity();
    float get_determinant();
    
    // Absolute transforms
    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    
    // Relative transforms
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z, float angle);
    void scale(float x, float y, float z);
    
    // common operations
    void inverse();
    void preMultiply(Matrix *matrix); // mat x this 
    void post_multiply(Matrix *matrix); // this x mat
    
    // camera utils
    void setProjectionMatrix(float fov, float aspect_ratio, float near, float far);
    
    void log();
    
    // static 
    static void multiply(Matrix *a, Matrix *b, Matrix *out);
    
private:
    static void set_identity(float *out);
    static void rotation_matrix(float *out, float x, float y, float z, float angle); 
    static void multiply(float *a, float *b, float *out);
    static float determinant(float *matrix);
    
    /** Data */
    float *m_data;

};


#endif

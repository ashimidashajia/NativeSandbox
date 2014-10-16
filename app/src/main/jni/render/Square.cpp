/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Square.h"
#include "../utils/Logs.h"

#define TAG "Square"

GLfloat SQUARE_VERTICES[12] = {
    -0.7f, -0.7f, 0.0f,
     0.7f, -0.7f, 0.0f,
    -0.7f,  0.7f, 0.0f,
     0.7f,  0.7f, 0.0f,
};

/** Constructor */
Square::Square() { 
}

/** Destructor */
Square::~Square() {
}

/**
 * Initializes the model
 */
void Square::init() {
    LogD(TAG, " ❯ init()");
    initShader(VS_DEFAULT, FS_DEFAULT);
    initGeometry(&SQUARE_VERTICES[0], 4, VTX_MASK_POSITION, NULL, 0, GL_TRIANGLE_STRIP); 
    
}

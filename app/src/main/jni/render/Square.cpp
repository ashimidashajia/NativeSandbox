/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Square.h"


GLfloat SQUARE_VERTICES[12] = {
    -0.7f, -0.7f,
     0.7f, -0.7f,
    -0.7f,  0.7f,
     0.7f,  0.7f,
};

/** Constructor */
Square::Square() {
}

/** Destructor */
Square::~Square() {
}

void Square::init() {
    
    initShader(VS_DEFAULT, FS_DEFAULT);
    initGeometry(&SQUARE_VERTICES[0], 12, VTX_MASK_POSITION, NULL, 0, GL_TRIANGLE_STRIP); 
    
}

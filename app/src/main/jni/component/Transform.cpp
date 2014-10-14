/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Transform.h"


/** Constructor */
Transform::Transform() {
    mMatrix  = ALLOCATE_MATRIX();
    setMatrixIdentity(mMatrix, 0);     
}

/** Destructor */
Transform::~Transform() {
    free(mMatrix); 
}

/**
 * Returns a unique value to identify the component's type 
 */
long long int Transform::getType() {
    return T_TRANSFORM;
}

/** 
 * Returns the matrix
 */
float *Transform::getMatrix(){
    return mMatrix;
}

/** 
 * Sets the orientation of the current transform. The right vector is inferred from the other 
 * two vectors to make sure the matrix is consistent
 */
void Transform::setOrientation(Vector *dir, Vector *up) {} // TODO 

/**
 * Rotates this transform on itself, arount the given axis, with the given angle 
 */
void Transform::rotate(Vector *axis, float angle) {} // TODO 

/**
 * Orbits around the given point along the given axis, with the given angle. 
 */
void Transform::orbit(Vector *point, Vector *axis, float angle) {} // TODO 

/**
 * Orbits around the given point along the given axis, with the given angle. Only the position 
 * is affected by this method
 */
void Transform::orbitAligned(Vector *point, Vector *axis, float angle) {} // TODO 

/** 
 * Sets the position of the transform 
 */
void Transform::setPosition(Vector *pos) {} // TODO 
void Transform::setPosition(float x, float y, float z) {} // TODO 

/** 
 * Translates this transform
 */
void Transform::translate(Vector *pos) {
    translateMatrix(mMatrix, 0, pos->x(), pos->y(), pos->z());
}
void Transform::translate(float x, float y, float z) {
    translateMatrix(mMatrix, 0, x, y, z);
}

/**
 * Sets the absolute scale of the transform
 */
void Transform::setScale(Vector *scale) {} // TODO 
void Transform::setScale(float, float, float) {} // TODO 
void Transform::setScale(float) {} // TODO 

/**
 * Scales this transform by the given amount. 
 */
void Transform::scale(Vector *scale) {} // TODO 
void Transform::scale(float, float, float) {} // TODO 
void Transform::scale(float) {} // TODO 

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Transform.h"


/** Constructor */
Transform::Transform() {
    mMatrix = new Matrix();
}

/** Destructor */
Transform::~Transform() {
    if (mMatrix){
        delete mMatrix; 
    }
}

/** 
 * Returns the matrix
 */
Matrix *Transform::getMatrix(){
    return mMatrix;
}

/** 
 * Returns the matrix as a float[16], which can be then sent to a shader as a parameter
 */
float *Transform::getMatrixData(){
    return mMatrix->getData();
}

/** 
 * Sets the orientation of the current transform. The right vector is inferred from the other 
 * two vectors to make sure the matrix is consistent
 */
void Transform::setOrientation(Vector *dir, Vector *up) {}

/**
 * Rotates this transform on itself, arount the given axis, with the given angle 
 */
void Transform::rotate(Vector *axis, float angle) {
    mMatrix->rotate(axis->x(), axis->y(), axis->z(), angle); 
}

/**
 * Orbits around the given point along the given axis, with the given angle. 
 */
void Transform::orbit(Vector *point, Vector *axis, float angle) {}

/**
 * Orbits around the given point along the given axis, with the given angle. Only the position 
 * is affected by this method
 */
void Transform::orbitAligned(Vector *point, Vector *axis, float angle) {}

/** 
 * Sets the position of the transform 
 */
void Transform::setPosition(Vector *pos) {
    mMatrix->setPosition(pos->x(), pos->y(), pos->z());
}
void Transform::setPosition(float x, float y, float z) {
    mMatrix->setPosition(x, y, z);
}

/** 
 * Translates this transform
 */
void Transform::translate(Vector *pos) {
    mMatrix->translate(pos->x(), pos->y(), pos->z());
}
void Transform::translate(float x, float y, float z) {
    mMatrix->translate(x, y, z);
}

/**
 * Sets the absolute scale of the transform
 */
void Transform::setScale(Vector *scale) {}
void Transform::setScale(float, float, float) {}
void Transform::setScale(float) {}

/**
 * Scales this transform by the given amount. 
 */
void Transform::scale(Vector *scale) {}
void Transform::scale(float, float, float) {}
void Transform::scale(float) {}

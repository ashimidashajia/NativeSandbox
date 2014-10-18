/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../behavior/Component.h"
#include "../math/Matrix.h"

/**
 * The transform class gives some easy features to manipulate a transform matrix, ie position, 
 * rotation and scale of an object in 3D space
 */
class Transform : public Component{

public:

    /** Constructor */
    Transform();

    /** Destructor */
    ~Transform();
    
    /**
     * Returns a unique value to identify the component's type 
     */
    long long int getType();
    
    /** 
     * Sets the orientation of the current transform. The right vector is inferred from the other 
     * two vectors to make sure the matrix is consistent
     */
    void setOrientation(Vector *dir, Vector *up); 
    
    /**
     * Rotates this transform on itself, arount the given axis, with the given angle 
     */
    void rotate(Vector *axis, float angle);
    void rotate(float x, float y, float z, float angle);
    
    /**
     * Orbits around the given point along the given axis, with the given angle. 
     */
    void orbit(Vector *point, Vector *axis, float angle);
    
    /**
     * Orbits around the given point along the given axis, with the given angle. Only the position 
     * is affected by this method
     */
    void orbitAligned(Vector *point, Vector *axis, float angle);
    
    /** 
     * Sets the position of the transform 
     */
    void setPosition(Vector *pos);
    void setPosition(float, float, float);
    
    /** 
     * Translates this transform
     */
    void translateLocal(Vector *pos);
    void translateLocal(float,float,float);
    
    /**
     * Sets the absolute scale of the transform
     */
    void setScale(Vector *scale);
    void setScale(float, float, float);
    void setScale(float); // homogeneous
    
    /**
     * Scales this transform by the given amount. 
     */
    void scale(Vector *scale);
    void scale(float, float, float);
    void scale(float); // homogeneous
    
// protected:

    /** 
     * Returns the matrix as a float[16], which can be then sent to a shader as a parameter
     */
    float *getMatrix();
    
private: 
    
    /** transform matrix of the virtual position of the camera */
    float *mMatrix; 
    
};

#endif

/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Model.h"
#include "../utils/Logs.h"

#define TAG "Model"

/** Constructor */
Model::Model() {
    mShader = new Shader();
    mGeometry = new Geometry();

    mTransform = NULL; 
}

/** Destructor */
Model::~Model() {
    if (mShader) {
        delete mShader;
    }

    if (mGeometry) {
        delete mGeometry;
    }
}


/**
 * Called when this component is attached to an object. The parent object is accesible in the 
 * mObject field from now on. 
 */
void Model::onAttached(){
    mTransform = dynamic_cast<Transform *>(mObject->getComponent(T_TRANSFORM)); 
}

/**
 * Initialises the shader.
 * Returns true if the initialization was succesfully.
 */
bool Model::initShader(const char *vsSource, const char *fsSource) {

    if (!mShader->init(vsSource, fsSource)) {
        LogW(TAG, "   • Error while compiling shader");
        delete mShader;
        mShader = NULL;
        return false;
    }

    return true;
}

/**
 * Initializes the geometry with the given Vertices array. 
 * Returns true if the initialization was succesfully. 
 */
bool Model::initGeometry(GLfloat *vertices, int vtxCount, unsigned short vtxMask, 
                            GLubyte *indices, int idxCount, GLenum mode) {
    
    if (!mGeometry->initVertices(vertices, vtxCount, vtxMask)) {
        LogW(TAG, "   • Can't init geometry");
        delete mGeometry;
        mGeometry = NULL;
        return false;
    }

    mGeometry->initIndices(indices, idxCount, mode);
    return true;
}

/** 
 * Renders the object
 */
void Model::render(Environment *env) {

    // Check that we have a shader
    if (mShader == NULL) {
        LogW(TAG, "   • can't draw a model with a NULL shader");
        return; 
    }
    
    // Check that we have a geometry
    if (mGeometry == NULL) {
        LogW(TAG, "   • can't draw a model with a NULL geometry");
        return; 
    }
    
    // set the shader active
    LogV(TAG, "   • Set shader active");
    mShader->setActive();
    
    // set the environment 
    LogV(TAG, "   • Set environment");
    env->setUniformValues(mShader);
    
    // set uniform values 
    if (mTransform != NULL) {
        LogV(TAG, "   • Set transform uniform values");
        glUniformMatrix4fv(mShader->getModelMatrixUniformHandle(), 1, false, mTransform->getMatrix());
    }

    // draw the geometry
    LogV(TAG, "   • Draw geometry");
    mGeometry->drawGeometry(mShader);

}

/**
 * Returns a unique value to identify the component's type 
 */
long long int Model::getType() {
    return T_SHAPE_3D;
}
